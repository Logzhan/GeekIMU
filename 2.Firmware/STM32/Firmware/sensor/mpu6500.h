/******************** (C) COPYRIGHT 2020 GEEKIMU *******************************
* File Name          : MPU6500.h
* Current Version    : V2.0  & ST 3.5.0
* Author             : zhanli 719901725@qq.com & JustFeng.
* Date of Issued     : 2019.5.26 zhanli : Create
* Comments           : MPU6500驱动        
********************************************************************************/
#ifndef __MPU6500_H
#define __MPU6500_H

#include "stm32f10x.h"

typedef struct {
	int16_t Gyro[3];
	int16_t Accel[3];
	int16_t Temp;
}MPU_RawData;

typedef struct {
	float Gyro[3];
	float Accel[3];
	float Mag[3];
	float Temp;
}MPU_Data;

uint8_t MPU6500_Init(void);

/**----------------------------------------------------------------------
* Function    : MPU6500_Get_Rawdata
* Description : 读取MPU6500原始数据，这里按照逐字节读取方式，以后可以优化为
				DMA直接读取提高速度
* Author      : zhanli&719901725@qq.com
* Date        : 2019/5/26 zhanli
*---------------------------------------------------------------------**/
void MPU6500_Get_Rawdata(s16 *ax,s16 *ay,s16 *az,
	                     s16 *gx,s16 *gy,s16 *gz,
                         s16 *temp);

/**----------------------------------------------------------------------
* Function    : MPU6500_GetData
* Description : 读取MPU6500数据,这里读取的数据是转换过的
* Author      : zhanli&719901725@qq.com
* Date        : 2019/5/26 zhanli
*---------------------------------------------------------------------**/
void MPU6500_GetData(MPU_Data *mMPU_Data);
	
/**----------------------------------------------------------------------
* Function    : MPU6500_Write_Byte
* Description : MPU6500写一字节
* Author      : zhanli&719901725@qq.com
* Date        : 2019/5/26 zhanli
*---------------------------------------------------------------------**/
uint8_t MPU6500_Write_Byte(uint8_t reg,uint8_t data);	 

/**----------------------------------------------------------------------
* Function    : MPU6500_Read_Byte
* Description : MPU6500读一字节
* Author      : zhanli&719901725@qq.com
* Date        : 2019/5/26 zhanli
*---------------------------------------------------------------------**/
uint8_t MPU6500_Read_Byte(uint8_t reg);

#endif

