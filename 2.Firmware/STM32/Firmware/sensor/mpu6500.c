/******************** (C) COPYRIGHT 2020 GEEKIMU *******************************
* File Name          : MPU6500.c
* Current Version    : V2.0  & ST 3.5.0
* Author             : zhanli 719901725@qq.com & JustFeng.
* Date of Issued     : 2019.5.26 zhanli : Create
* Comments           : MPU6500驱动        
********************************************************************************/
#include "stm32f10x_spi.h"
#include "mpu6500_register_map.h"
#include "MPU6500.h"
#include "sys.h"
#include "delay.h"
#include "spi.h"
#include "calibrate.h"

/* 定义SPI总线连接的GPIO端口 ------------------------------------------------------ */
#define mpu6500_CS          GPIO_Pin_4
#define mpu6500_CS_G        GPIOA

#define mpu6500_DRDY        GPIO_Pin_8
#define mpu6500_DRDY_G      GPIOB

#define mpu6500_CS_L        PAout(4) = 0
#define mpu6500_CS_H        PAout(4) = 1

#define GYRO_SCALE          2000.0f / 32768 
#define ACCEL_SCALE         4.0f    / 32768
#define M_PI                3.14159265358979323846f

MPU_Data mMPU_Data;

extern Calibrate_Info mCali_Info; 

/**----------------------------------------------------------------------
* Function    : MPU6500_IO_Init
* Description : 初始化MPU6500的IO口
* Author      : zhanli&719901725@qq.com
* Date        : 2019/5/26 zhanli
*---------------------------------------------------------------------**/
void MPU6500_IO_Init(void) 
{
	GPIO_InitTypeDef  GPIO_InitStructure;

	MEMS_SPI_Init();  

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	            /* 使能PA端口时钟			     */
																									
	GPIO_InitStructure.GPIO_Pin   = mpu6500_CS;				            /* MPU6500 CS端口配置 			 */
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP; 		            /* 推挽输出						 */
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		            /* IO口速度为50MHz				 */
	GPIO_Init(mpu6500_CS_G, &GPIO_InitStructure);					    /* 根据设定参数初始化端口   	 */

	GPIO_SetBits(mpu6500_CS_G, mpu6500_CS);                             /* 先默认设置不片选              */

	GPIO_InitStructure.GPIO_Pin   = mpu6500_DRDY;				        /* MPU6500 DRDY 端口配置	     */
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP; 		            /* 推挽输出						 */
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		            /* IO口速度为50MHz				 */
	GPIO_Init(mpu6500_CS_G, &GPIO_InitStructure);					    /* 根据设定参数初始化端口   	 */

}

/**----------------------------------------------------------------------
* Function    : MPU6500_Init
* Description : 初始化MPU6500配置参数以及自检
* Author      : zhanli&719901725@qq.com
* Date        : 2019/5/26 zhanli
*---------------------------------------------------------------------**/
uint8_t MPU6500_Init(void)
{ 
	uint8_t res = 0xff;

	MPU6500_IO_Init();                                                /* 初始化MPU6500对应IO口     	*/
	Delay_Ms(100);                                                    /* 保证100ms延迟让传感器稳定  */
	MPU6500_Write_Byte(PWR_MGMT_1, DEVICE_RESET);	                  /* 重置设备状态               */
	Delay_Ms(10);
	res = MPU6500_Read_Byte(WHO_AM_I);                                /* 读取设备ID                 */

	Delay_Ms(100);                                                    /* 保证100ms延迟让传感器稳定  */ 
	MPU6500_Write_Byte(SIGNAL_PATH_RESET, TEMP_RESET |                /* 重置信号通道               */
										  GYRO_RESET | 
										  ACCEL_RESET);
	Delay_Ms(100);                                                    /* 手册：page 42 延时 100ms   */
	MPU6500_Write_Byte(USER_CTRL, I2C_IF_DIS);                        /* 关闭MPU6500 IIC            */
	Delay_Ms(10);
	MPU6500_Write_Byte(PWR_MGMT_1, CLKSEL_GYRO_Y);                    /* 参考DK2                    */
	Delay_Ms(10);
	MPU6500_Write_Byte(INV_CONFIG, DLPF_CFG_256);                     /* 陀螺仪低通滤波250Hz        */  
	Delay_Ms(10);
	MPU6500_Write_Byte(ACCEL_CONFIG2, ACCEL_FCHOICE_B);               /* 加速度计采样频率4khz       */
	Delay_Ms(10);
	MPU6500_Write_Byte(GYRO_CONFIG, FS_SEL_2000);                     /* 敏感度2000deg/s            */
	Delay_Ms(10);
	MPU6500_Write_Byte(ACCEL_CONFIG, AFS_SEL_4);                      /* 加速度计检测范围±4G        */
	Delay_Ms(10);
	MPU6500_Write_Byte(INT_PIN_CFG, INT_RD_CLEAR);                    /* 清除中断                   */

	// Turn on data ready interrupts
	// mpu6500_Write_Byte(INT_ENABLE, DATA_RDY_EN);
	return res;
}

/**----------------------------------------------------------------------
* Function    : MPU6500_Get_Rawdata
* Description : 读取MPU6500原始数据，这里按照逐字节读取方式，以后可以优化为
				DMA直接读取提高速度
* Author      : zhanli&719901725@qq.com
* Date        : 2019/5/26 zhanli
*---------------------------------------------------------------------**/
void MPU6500_Get_Rawdata(s16 *ax,s16 *ay,s16 *az,s16 *gx,s16 *gy,s16 *gz,s16 *temp){
	
	unsigned char Buff[6];                                          
	
	// 读取加速度计数据
	Buff[0] = MPU6500_Read_Byte(ACCEL_XOUT_L);    
	Buff[1] = MPU6500_Read_Byte(ACCEL_XOUT_H);
	*ax =	(Buff[1] << 8 ) | Buff[0];    

	Buff[2] = MPU6500_Read_Byte(ACCEL_YOUT_L); 
	Buff[3] = MPU6500_Read_Byte(ACCEL_YOUT_H);
	*ay =	(Buff[3] << 8 ) | Buff[2];  	  

	Buff[4] = MPU6500_Read_Byte(ACCEL_ZOUT_L); 
	Buff[5] = MPU6500_Read_Byte(ACCEL_ZOUT_H);
	*az =	(Buff[5] << 8 ) | Buff[4]; 	

	// 读取温度数据
	Buff[0] = MPU6500_Read_Byte(TEMP_OUT_L); 
	Buff[1] = MPU6500_Read_Byte(TEMP_OUT_H);
	*temp =	(Buff[1] << 8 ) | Buff[0];    

	// 读取陀螺仪数据
	Buff[0] = MPU6500_Read_Byte(GYRO_XOUT_L); 
	Buff[1] = MPU6500_Read_Byte(GYRO_XOUT_H);
	*gx =	(Buff[1] << 8 ) | Buff[0];           

	Buff[2] = MPU6500_Read_Byte(GYRO_YOUT_L);
	Buff[3] = MPU6500_Read_Byte(GYRO_YOUT_H);
	*gy =	(Buff[3] << 8 ) | Buff[2];

	Buff[4] = MPU6500_Read_Byte(GYRO_ZOUT_L);
	Buff[5] = MPU6500_Read_Byte(GYRO_ZOUT_H);
	*gz =	(Buff[5] << 8 ) | Buff[4];
}

/**----------------------------------------------------------------------
* Function    : MPU6500_GetData
* Description : 读取MPU6500数据,这里读取的数据是转换过的
* Author      : zhanli&719901725@qq.com
* Date        : 2019/5/26 zhanli
*---------------------------------------------------------------------**/
void MPU6500_GetData(MPU_Data *mMPU_Data){
	
	int i = 0;
	MPU_RawData mRawData;

	MPU6500_Get_Rawdata(&mRawData.Accel[0],&mRawData.Accel[1], &mRawData.Accel[2],
					    &mRawData.Gyro[0], &mRawData.Gyro[1],  &mRawData.Gyro[2],
					    &mRawData.Temp);

	for(i = 0; i < 3; i++)mMPU_Data->Accel[i] = (float)((mRawData.Accel[i]) * ACCEL_SCALE);

	for(i = 0; i < 3; i++)mMPU_Data->Gyro[i]  = (float)(M_PI * (mRawData.Gyro[i] - mCali_Info.Gyr_Offset[i]) * GYRO_SCALE / 180.0f);

	mMPU_Data -> Temp = 10000 * (int32_t)(mRawData.Temp) / 33387 + 2100;
}

/**----------------------------------------------------------------------
* Function    : MPU6500_Write_Byte
* Description : MPU6500写一字节
* Author      : zhanli&719901725@qq.com
* Date        : 2019/5/26 zhanli
*---------------------------------------------------------------------**/
uint8_t MPU6500_Write_Byte(uint8_t reg,uint8_t data) 				 
{ 
	mpu6500_CS_L;
	SPI2_ReadWriteByte(reg);          
	SPI2_ReadWriteByte(data);
	mpu6500_CS_H;
	return 0;
}

/**----------------------------------------------------------------------
* Function    : MPU6500_Read_Byte
* Description : MPU6500读一字节
* Author      : zhanli&719901725@qq.com
* Date        : 2019/5/26 zhanli
*---------------------------------------------------------------------**/
uint8_t MPU6500_Read_Byte(uint8_t reg)
{
	uint8_t tmp=0;
	mpu6500_CS_L;
	SPI2_ReadWriteByte(reg|0x80);   
	tmp = SPI2_ReadWriteByte(0xff);
	mpu6500_CS_H;
	return tmp;
}


