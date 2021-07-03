/******************** (C) COPYRIGHT 2020 GEEKIMU *******************************
* File Name          : spi.h
* Current Version    : V2.0  & ST 3.5.0
* Author             : zhanli 719901725@qq.com & JustFeng.
* Date of Issued     : 2019.5.22 zhanli : Create
* Comments           : SPI配置和驱动  
********************************************************************************/
#ifndef __SPI_H_
#define __SPI_H_	
#include "stm32f10x.h"

#define SPI_SPEED_2                 0
#define SPI_SPEED_8                 1
#define SPI_SPEED_16                2
#define SPI_SPEED_256               3

/**----------------------------------------------------------------------
* Function    : MEMS_SPI_Init
* Description : 初始化陀螺仪和磁力计的SPI接口
* Author      : zhanli&719901725@qq.com
* Date        : 2019/5/04 zhanli
*---------------------------------------------------------------------**/
void MEMS_SPI_Init(void);

/**----------------------------------------------------------------------
* Function    : SPI2_ReadWriteByte
* Description : 读写SPI2的数据,主要是读写MPU6500 + LIS3MDL的数据
* Author      : zhanli&719901725@qq.com
* Date        : 2015/2/13 zhanli
*---------------------------------------------------------------------**/
uint8_t SPI2_ReadWriteByte(uint8_t TxData);

#endif
