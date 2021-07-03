/******************** (C) COPYRIGHT 2020 GEEKIMU *******************************
* File Name          : LIS3MDL.h
* Current Version    : V2.0  & ST 3.5.0
* Author             : zhanli 719901725@qq.com & JustFeng.
* Date of Issued     : 2019.5.26 zhanli : Create
* Comments           : LIS3MDL 磁力计驱动        
********************************************************************************/
#ifndef _LIS3MDL_H_
#define _LIS3MDL_H_

#include "stm32f10x.h"
#include "calibrate.h"

typedef struct{
	int16_t Mag[3];
}LIS3MDL_Data;

/**----------------------------------------------------------------------
* Function    : LIS3MDL_IO_Init
* Description : 初始化LIS3MDL(磁力计)的IO口
* Author      : zhanli&719901725@qq.com
* Date        : 2019/5/26 zhanli
*---------------------------------------------------------------------**/
void LIS3MDL_IO_Init(void);

/**----------------------------------------------------------------------
* Function    : LIS3MDL_Init
* Description : LIS3MDL(磁力计)初始化配置
* Author      : zhanli&719901725@qq.com
* Date        : 2019/5/26 zhanli
*---------------------------------------------------------------------**/
void LIS3MDL_Init(void);

/**----------------------------------------------------------------------
* Function    : LIS3MDL_GetData
* Description : LIS3MDL(磁力计)获取磁力计数据
* Author      : zhanli&719901725@qq.com
* Date        : 2019/5/26 zhanli
*---------------------------------------------------------------------**/
void LIS3MDL_GetData(float *mx,float *my,float *mz);

/**----------------------------------------------------------------------
* Function    : Magnet_Calibrate
* Description : 给定磁力计参数校准磁力计
* Author      : zhanli&719901725@qq.com
* Date        : 2019/5/26 zhanli
*---------------------------------------------------------------------**/
void Magnet_Calibrate(float *mx, float *my, float *mz, Calibrate_Info mCali_Info);

/**----------------------------------------------------------------------
* Function    : LIS3MDL_Write_Byte
* Description : MPU6500写一字节
* Author      : zhanli&719901725@qq.com
* Date        : 2019/5/26 zhanli
*---------------------------------------------------------------------**/
uint8_t LIS3MDL_Write_Byte(uint8_t reg,uint8_t data);

/**----------------------------------------------------------------------
* Function    : LIS3MDL_Read_Byte
* Description : MPU6500读一字节
* Author      : zhanli&719901725@qq.com
* Date        : 2019/5/26 zhanli
*---------------------------------------------------------------------**/
uint8_t LIS3MDL_Read_Byte(uint8_t reg);

#endif
