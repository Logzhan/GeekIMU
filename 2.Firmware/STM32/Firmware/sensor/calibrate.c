/******************** (C) COPYRIGHT 2020 GEEKIMU *******************************
* File Name          : calibrate.c
* Current Version    : V2.0  & ST 3.5.0
* Author             : zhanli 719901725@qq.com & JustFeng.
* Date of Issued     : 2015.10.3 zhanli : Create
* Comments           : 从MCU的flash中加载校准数据   
********************************************************************************/
#include <string.h>
#include <stdint.h>
#include <math.h>
#include <stdlib.h>
#include <delay.h>
#include <sys.h>
#include "calibrate.h"
#include "stm32f10x_tim.h"
#include "stm32f10x_flash.h"
#include "stmflash.h"
#include "mpu6500.h"

#define FLASH_Gyro_OFFSET_ADDR    0x0800FF00 		      // 模拟EEPROM的起始地址
#define FLASH_ACC_OFFSET_ADDR     0x0800FF08 		      // 模拟EEPROM的起始地址
#define FLASH_MAG_OFFSET_ADDR     0x0800FF10 		      // 模拟EEPROM的起始地址

Calibrate_Info mCali_Info;                        		  // 传感器校准数据

float Gyr_Offset[3]={0,0,0};
float Acc_Offset[3]={0,0,0};
float Mag_Offset[6]={0,0,0,1,1,1};
uint16_t Buffer[24]={0};

/**----------------------------------------------------------------------
* Function    : Calibrate_Init(void)
* Description : 初始化追踪器的所有校准数据
* Author      : zhanli&719901725@qq.com & JustFeng.
* Date        : 2015/2/13 zhanli
*---------------------------------------------------------------------**/
void Calibrate_Init(void)
{
	// 初始化陀螺仪零偏数据    
	Init_Gyro_Offset(&mCali_Info);                                                
	Load_Acc_Offset();
	Load_Mag_Offset();
}

/**----------------------------------------------------------------------
* Function    : Init_Gyro_Offset(void)
* Description : 初始化陀螺仪零偏值,从EEROM中读取陀螺仪零偏值
* Author      : zhanli&719901725@qq.com & JustFeng.
* Date        : 2015/10/3 zhanli
*---------------------------------------------------------------------**/
void Init_Gyro_Offset(Calibrate_Info *mCali_Info)
{
	int i = 0;
	float* fv[3] = {NULL};
	                        
	STMFLASH_Read(FLASH_SAVE_ADDR,Buffer,7);                                     /* 从指定地址读取陀螺仪零偏数据 */
	 
	if(Buffer[0]==0xffff)                                                        /* 如果校准数据为空             */
	{ 	
		for(i = 0; i < 3; i++)mCali_Info -> Gyr_Offset[i] = 0;
		
		Store_Gyro_Offset(mCali_Info);                                           /* 存储陀螺仪校准信息           */
		
	}else                                                                        /* 如果存在校准数据             */
	{                                                                            /* 应用零偏数据                 */
		fv[0] = (float*)&Buffer[1];
		fv[1] = (float*)&Buffer[3];
		fv[2] = (float*)&Buffer[5];
			
		for(i = 0; i < 3; i++)mCali_Info -> Gyr_Offset[i] = *fv[i];
	}
}

/**----------------------------------------------------------------------
* Function    : Compute_Gyro_Offset(void)
* Description : 在静止时候读取MPU6050的陀螺仪数值，计算陀螺仪的零偏
* Author      : zhanli&719901725@qq.com & JustFeng.
* Date        : 2015/10/3 zhanli
*---------------------------------------------------------------------**/
void Compute_Gyro_Offset(void)
{
  	unsigned short int i;
  	double gyro_x=0, gyro_y=0, gyro_z=0;
  	int count = 0;
	signed short int accel[3],gyro[3],temperature;

  	for(i = 0;i < 2000; i++){
		MPU6500_Get_Rawdata(&accel[0],&accel[1],&accel[2],
							&gyro[0], &gyro[1], &gyro[2], 
		                    &temperature);
			
		// 进行原始数据的校准
		gyro_x += gyro[0];
		gyro_y += gyro[1];
		gyro_z += gyro[2];
		count++;
  	}
  	mCali_Info.Gyr_Offset[0] = (float)(gyro_x / count);
  	mCali_Info.Gyr_Offset[1] = (float)(gyro_y / count);
  	mCali_Info.Gyr_Offset[2] = (float)(gyro_z / count);
		
	Store_Gyro_Offset(&mCali_Info);
}

/**----------------------------------------------------------------------
* Function    : Store_Gyro_Offset(void)
* Description : 把误差参数存到eeprom中
* Author      : zhanli&719901725@qq.com & JustFeng.
* Date        : 2015/10/3 zhanli
*---------------------------------------------------------------------**/
void Store_Gyro_Offset(Calibrate_Info *mCali_Info)
{
	int i = 0;
	float* fv = (float*)&Buffer[1];	

	Buffer[0] = 0x1111;         
	// 设置Buffer0为0x1111,表示存在陀螺仪零偏数据
	for(i = 0; i < 3; i++){
		fv[i] = mCali_Info -> Gyr_Offset[i];
	}
	/*存储陀螺仪零偏数据到EEPROM中*/	    
	STMFLASH_Write(FLASH_SAVE_ADDR,Buffer,7);
}

/**----------------------------------------------------------------------
* Function    : Get_Gyro_Offset(float* gyro)
* Description : 从flash中读取陀螺仪零偏数据
* Author      : JustFeng.
* Date        : 2015/10/3 zhanli
*---------------------------------------------------------------------**/
void Get_Gyro_Offset(float* gyro)
{
	float* fv;
	/*从指定地址读取陀螺仪零偏数据*/
	STMFLASH_Read(FLASH_Gyro_OFFSET_ADDR,Buffer,7);

	/*应用零偏数据*/
	fv = (float*)(Buffer+1);			
	gyro[0] = fv[0];
	gyro[1] = fv[1];
	gyro[2] = fv[2];

}
/**----------------------------------------------------------------------
* Function    : void Clean_Gyro_Offset(void)
* Description : 从EEPROM中擦除陀螺仪零偏数据
* Author      : JustFeng.
* Date        : 2015/10/3 zhanli
*---------------------------------------------------------------------**/
void Clean_Gyro_Offset(void)
{
	uint8_t i = 0;
	for(i = 0;i < 7;i++)
		Buffer[i]=0xffff;
	// 将清除后的数据写入EEPROM中
	STMFLASH_Write(FLASH_SAVE_ADDR,Buffer,7);
}

/**----------------------------------------------------------------------
* Function    : Save_Gyro_Offset(void)
* Description : 保存陀螺仪的零偏
* Author      : JustFeng.
* Date        : 2016/12/2 JustFeng
*---------------------------------------------------------------------**/
void Save_Gyro_Offset(float* Gyr_Offset)
{
	float* fv = (float*)(Buffer + 1);	
	fv[0] = Gyr_Offset[0];
	fv[1] = Gyr_Offset[1];
	fv[2] = Gyr_Offset[2];
	// 存储陀螺仪零偏数据到EEPROM中    
	STMFLASH_Write(FLASH_Gyro_OFFSET_ADDR,Buffer,7);
}

/**----------------------------------------------------------------------
* Function    : Reset_Gyro_Offset(void)
* Description : 重置陀螺仪的零偏
* Author      : JustFeng.
* Date        : 2016/12/2 JustFeng
*---------------------------------------------------------------------**/
void Reset_Gyro_Offset(void)
{
	float gyro_offset_default[]={0,0,0};
	Save_Gyro_Offset(gyro_offset_default);
}

/**----------------------------------------------------------------------
* Function    : Load_Acc_Offset() 
* Description : 从STM32的EEROM中读取加速计零偏值
* Author      : JustFeng.
* Date        : 2016/12/2 JustFeng
*---------------------------------------------------------------------**/
void Load_Acc_Offset()
{
	Get_Acc_Offset(Acc_Offset);
}

/**----------------------------------------------------------------------
* Function    : Get_Acc_Offset(float* acc) 
* Description : 从STM32的EEROM中读取加速计零偏数据
* Author      : JustFeng.
* Date        : 2016/12/4 JustFeng
*---------------------------------------------------------------------**/
void Get_Acc_Offset(float* acc)
{
	float* fv;
	/*从指定地址读取加速计零偏数据*/
	STMFLASH_Read(FLASH_ACC_OFFSET_ADDR,Buffer,6);

	/*应用零偏数据*/
	fv = (float*)Buffer;

	acc[0] = fv[0];
	acc[1] = fv[1];
	acc[2] = fv[2];
}

/**----------------------------------------------------------------------
* Function    : Save_Acc_Offset(float*)
* Description : 从STM32的EEROM中读取加速计零偏数据
* Author      : JustFeng.
* Date        : 2016/12/2 JustFeng
*---------------------------------------------------------------------**/
void Save_Acc_Offset(float* acc_offset)
{
	float* fv = (float*)Buffer;	
	fv[0] =  acc_offset[0];
	fv[1] =  acc_offset[1];
	fv[2] =  acc_offset[2];
	
    /*存储陀螺仪零偏数据到EEPROM中*/	    
	STMFLASH_Write(FLASH_ACC_OFFSET_ADDR,Buffer,6);
}

/**----------------------------------------------------------------------
* Function    : Reset_Acc_Offset(void)
* Description : 从EEPROM中擦除加速计校准参数
* Author      : JustFeng.
* Date        : 2016/12/2 JustFeng
*---------------------------------------------------------------------**/
void Reset_Acc_Offset(void)
{
	float acc_offset_default[]={0,0,0};
	Save_Acc_Offset(acc_offset_default);
}

/**----------------------------------------------------------------------
* Function    : Load_Mag_Offset() 
* Description : 从STM32的EEROM中读取磁力计校准参数
* Author      : JustFeng.
* Date        : 2016/12/2 JustFeng
*---------------------------------------------------------------------**/
void Load_Mag_Offset()
{
	Get_Mag_Offset(Mag_Offset);
}

/**----------------------------------------------------------------------
* Function    : Get_Mag_Offset
* Description : 从STM32的EEROM中读取磁力计校准参数
* Author      : JustFeng.
* Date        : 2016/12/2 JustFeng
*---------------------------------------------------------------------**/
void Get_Mag_Offset(float* mag)
{
	int i = 0, count = 0;
	float* fv;
	/*从指定地址读取磁力计校准数据*/
	STMFLASH_Read(FLASH_MAG_OFFSET_ADDR,Buffer,24);

	for(i = 0; i < 24; i++){
		if(Buffer[i] == 0xff)count++;
	}
 
	if(count == 24){
		for(i = 0; i < 3; i++){
			mCali_Info.Mag_Offset[i] = 0;
			mCali_Info.Mag_Scale[i][i] = 1;
			mag[i] = 0;
			mag[i + 3] = 1;
		}
	}else{
		/*应用零偏数据*/
		fv = (float*)Buffer;

	  for(i = 0; i < 6; i++)mag[i] = fv[i];
	
		for(i = 0; i < 3; i++){
			mCali_Info.Mag_Offset[i] = fv[i];
			mCali_Info.Mag_Scale[i][i] = fv[i + 3];
		}	
	}
}
/**----------------------------------------------------------------------
* Function    : Save_Mag_Offset
* Description : 从STM32的EEROM中保存磁力计校准参数
* Author      : JustFeng.
* Date        : 2016/12/2 JustFeng
*---------------------------------------------------------------------**/
void Save_Mag_Offset(float* mag_offset)
{
	int i = 0;
	float* fv = (float*)Buffer;	
	fv[0] =  mag_offset[0];
	fv[1] =  mag_offset[1];
	fv[2] =  mag_offset[2];
	fv[3] =  mag_offset[3];
	fv[4] =  mag_offset[4];
	fv[5] =  mag_offset[5];
	// 存储磁力计校准数据到EEPROM中    
	STMFLASH_Write(FLASH_MAG_OFFSET_ADDR,Buffer,24);
	
	for(i = 0; i < 3; i++){
		mCali_Info.Mag_Offset[i] = fv[i];
		mCali_Info.Mag_Scale[i][i] = fv[i + 3];
	}
}
/**----------------------------------------------------------------------
* Function    : Reset_Mag_Offset
* Description : 从EEPROM中擦除磁力计校准参数
* Author      : JustFeng.
* Date        : 2016/12/2 JustFeng
*---------------------------------------------------------------------**/
void Reset_Mag_Offset(void)
{
	float mag_offset_default[]={0,0,0,1,1,1};
	Save_Mag_Offset(mag_offset_default);
}

