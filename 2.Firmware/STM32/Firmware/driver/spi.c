/******************** (C) COPYRIGHT 2020 GEEKIMU *******************************
* File Name          : spi.c
* Current Version    : V2.0  & ST 3.5.0
* Author             : zhanli 719901725@qq.com & JustFeng.
* Date of Issued     : 2019.5.22 zhanli : Create
* Comments           : SPI配置和驱动  
********************************************************************************/
#include "stm32f10x_spi.h"
#include "spi.h"
#include "sys.h"

/**----------------------------------------------------------------------
* Function    : MEMS_SPI_Init
* Description : 初始化陀螺仪和磁力计的SPI接口
* Author      : zhanli&719901725@qq.com
* Date        : 2019/5/04 zhanli
*---------------------------------------------------------------------**/
void MEMS_SPI_Init()
{
	SPI_InitTypeDef  SPI_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;

	/* 开启GPIOB的时钟以及 SPI2的时钟         */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE );
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);

	/* 配置SPI的SCK，MISO，MOSI               */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	GPIO_SetBits(GPIOB,GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);
	
    SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;        // 设置SPI单向或者双向的数据模式:SPI设置为双线双向全双工
    SPI_InitStructure.SPI_Mode = SPI_Mode_Master;                             // 设置SPI工作模式:设置为主SPI
    SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;                         // 设置SPI的数据大小:SPI发送接收8位帧结构 
    SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;                               // 选择了串行时钟的稳态:时钟悬空高电平
    SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;                              // 数据捕获于第一个时钟沿
    SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;                                 // NSS信号由硬件（NSS管脚）还是软件（使用SSI位）管理:内部NSS信号有SSI位控制
    //SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_32;     // 采用的DK2的参数
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_8;        // 采用的9250参数
    SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;                        // 指定数据传输从MSB位还是LSB位开始:数据传输从MSB位开始
    SPI_InitStructure.SPI_CRCPolynomial = 7;                                  // CRC值计算的多项式
    SPI_Init(SPI2, &SPI_InitStructure);                                       // 根据SPI_InitStruct中指定的参数初始化外设SPIx寄存器
    SPI_Cmd(SPI2, ENABLE);                                                    // 使能SPI外设
	  
}
/**----------------------------------------------------------------------
* Function    : SPI2_ReadWriteByte
* Description : 读写SPI2的数据,主要是读写MPU6500 + LIS3MDL的数据
* Author      : zhanli&719901725@qq.com
* Date        : 2015/2/13 zhanli
*---------------------------------------------------------------------**/
uint8_t SPI2_ReadWriteByte(uint8_t TxData)
{		
	uint8_t retry = 0;				 	
	while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET) {
		retry++;
		if(retry>200)return 0;
	}			  
	SPI_I2S_SendData(SPI2, TxData);
	retry = 0;
	while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET) {
		retry++;
		if(retry>200)return 0;
	}	  						    
	return SPI_I2S_ReceiveData(SPI2); 		    
}
