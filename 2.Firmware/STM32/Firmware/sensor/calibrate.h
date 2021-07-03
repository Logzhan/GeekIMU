/******************** (C) COPYRIGHT 2020 GEEKIMU *******************************
* File Name          : calibrate.c
* Current Version    : V2.0  & ST 3.5.0
* Author             : zhanli 719901725@qq.com & JustFeng.
* Date of Issued     : 2015.10.3 zhanli : Create
* Comments           : 从MCU的flash中加载校准数据   
********************************************************************************/

#ifndef _CALIBRATE_H_
#define _CALIBRATE_H_

#include <stdint.h>
#include <stdbool.h>

#define CALIBRATION_SIZE (8+8+8*3+8*3+sizeof(uint16_t))

typedef struct calibrate_struct 
{
    float temperature;
    float Gyr_Offset[3];
    float acc_offset[3];
    // scale and cross axis sensitivity
	// 坐标轴缩放矩阵
    float gyro_scale[3][3];
    float acc_scale[3][3];
}calibrate_s, *calibrate_p;

typedef struct{
	float temp;
	float Gyr_Offset[3];
	float Acc_Offset[3];
	float Mag_Offset[3];
	float Mag_Scale[3][3];
}Calibrate_Info;

/**----------------------------------------------------------------------
* Function    : Calibrate_Init(void)
* Description : 初始化追踪器的所有校准数据
* Author      : zhanli&719901725@qq.com & JustFeng.
* Date        : 2015/2/13 zhanli
*---------------------------------------------------------------------**/	
void Calibrate_Init(void);

/**----------------------------------------------------------------------
* Function    : Init_Gyro_Offset(void)
* Description : 初始化陀螺仪零偏值,从EEROM中读取陀螺仪零偏值
* Author      : zhanli&719901725@qq.com & JustFeng.
* Date        : 2015/10/3 zhanli
*---------------------------------------------------------------------**/
void Init_Gyro_Offset(Calibrate_Info *mCali_Info);

/**----------------------------------------------------------------------
* Function    : Compute_Gyro_Offset(void)
* Description : 在静止时候读取MPU6050的陀螺仪数值，计算陀螺仪的零偏
* Author      : zhanli&719901725@qq.com & JustFeng.
* Date        : 2015/10/3 zhanli
*---------------------------------------------------------------------**/
void Compute_Gyro_Offset(void);

/**----------------------------------------------------------------------
* Function    : Store_Gyro_Offset(void)
* Description : 把误差参数存到eeprom中
* Author      : zhanli&719901725@qq.com & JustFeng.
* Date        : 2015/10/3 zhanli
*---------------------------------------------------------------------**/	
void Store_Gyro_Offset(Calibrate_Info *mCali_Info);

/**----------------------------------------------------------------------
* Function    : void Clean_Gyro_Offset(void)
* Description : 从EEPROM中擦除陀螺仪零偏数据
* Author      : JustFeng.
* Date        : 2015/10/3 zhanli
*---------------------------------------------------------------------**/
void Clean_Gyro_Offset(void);

/**----------------------------------------------------------------------
* Function    : Get_Acc_Offset(float* acc) 
* Description : 从STM32的EEROM中读取加速计零偏数据
* Author      : JustFeng.
* Date        : 2016/12/4 JustFeng
*---------------------------------------------------------------------**/
void Get_Gyro_Offset(float* gyro);

/**----------------------------------------------------------------------
* Function    : Save_Acc_Offset(float*)
* Description : 从STM32的EEROM中读取加速计零偏数据
* Author      : JustFeng.
* Date        : 2016/12/2 JustFeng
*---------------------------------------------------------------------**/
void Save_Gyro_Offset(float* Gyr_Offset);

/**----------------------------------------------------------------------
* Function    : Reset_Acc_Offset(void)
* Description : 从EEPROM中擦除加速计校准参数
* Author      : JustFeng.
* Date        : 2016/12/2 JustFeng
*---------------------------------------------------------------------**/
void Reset_Gyro_Offset(void);

/**----------------------------------------------------------------------
* Function    : Load_Acc_Offset() 
* Description : 从STM32的EEROM中读取加速计零偏值
* Author      : JustFeng.
* Date        : 2016/12/2 JustFeng
*---------------------------------------------------------------------**/
void Load_Gyro_Offset(void);

/**----------------------------------------------------------------------
* Function    : Reset_Acc_Offset(void)
* Description : 从EEPROM中擦除加速计校准参数
* Author      : JustFeng.
* Date        : 2016/12/2 JustFeng
*---------------------------------------------------------------------**/
void Load_Acc_Offset(void);

/**----------------------------------------------------------------------
* Function    : Get_Acc_Offset(float* acc) 
* Description : 从STM32的EEROM中读取加速计零偏数据
* Author      : JustFeng.
* Date        : 2016/12/4 JustFeng
*---------------------------------------------------------------------**/
void Get_Acc_Offset(float* acc);

/**----------------------------------------------------------------------
* Function    : Save_Acc_Offset(float*)
* Description : 从STM32的EEROM中读取加速计零偏数据
* Author      : JustFeng.
* Date        : 2016/12/2 JustFeng
*---------------------------------------------------------------------**/
void Save_Acc_Offset(float* acc_offset);

/**----------------------------------------------------------------------
* Function    : Reset_Acc_Offset(void)
* Description : 从EEPROM中擦除加速计校准参数
* Author      : JustFeng.
* Date        : 2016/12/2 JustFeng
*---------------------------------------------------------------------**/
void Reset_Acc_Offset(void);

/**----------------------------------------------------------------------
* Function    : Load_Mag_Offset() 
* Description : 从STM32的EEROM中读取磁力计校准参数
* Author      : JustFeng.
* Date        : 2016/12/2 JustFeng
*---------------------------------------------------------------------**/
void Load_Mag_Offset(void);

/**----------------------------------------------------------------------
* Function    : Get_Mag_Offset
* Description : 从STM32的EEROM中读取磁力计校准参数
* Author      : JustFeng.
* Date        : 2016/12/2 JustFeng
*---------------------------------------------------------------------**/
void Get_Mag_Offset(float* mag);

/**----------------------------------------------------------------------
* Function    : Save_Mag_Offset
* Description : 从STM32的EEROM中保存磁力计校准参数
* Author      : JustFeng.
* Date        : 2016/12/2 JustFeng
*---------------------------------------------------------------------**/
void Save_Mag_Offset(float* mag_offset);

/**----------------------------------------------------------------------
* Function    : Reset_Mag_Offset
* Description : 从EEPROM中擦除磁力计校准参数
* Author      : JustFeng.
* Date        : 2016/12/2 JustFeng
*---------------------------------------------------------------------**/
void Reset_Mag_Offset(void);

#endif /* _CALIBRATE_H_ */
