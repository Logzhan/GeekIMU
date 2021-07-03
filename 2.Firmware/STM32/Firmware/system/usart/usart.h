/******************** (C) COPYRIGHT 2020 GEEKIMU *******************************
* File Name          : usart.h
* Current Version    : V2.0  & ST 3.5.0
* Author             : zhanli 719901725@qq.com & JustFeng.
* Date of Issued     : 2019.5.26 zhanli : Create
* Comments           : STM32 串口驱动     
********************************************************************************/
#ifndef _USART_H_
#define _USART_H_

#include "stdio.h"	
#include "sys.h" 
	
#define USART_REC_LEN  			200  	          //定义最大接收字节数 200
#define EN_USART1_RX 			1		          //使能（1）/禁止（0）串口1接收
										          
extern u8  USART_RX_BUF[USART_REC_LEN];           //接收缓冲,最大USART_REC_LEN个字节.末字节为换行符 
extern u16 USART_RX_STA;         		          //接收状态标记	

/**----------------------------------------------------------------------
* Function    : uart_init
* Description : STM32 串口1初始化函数
* Input       : bound : 波特率
* Author      : zhanli&719901725@qq.com
* Date        : 2019/5/26 zhanli
*---------------------------------------------------------------------**/
void uart_init(u32 bound);

#endif


