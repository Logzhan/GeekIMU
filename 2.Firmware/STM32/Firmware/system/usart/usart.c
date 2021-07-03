/******************** (C) COPYRIGHT 2020 GEEKIMU *******************************
* File Name          : usart.c
* Current Version    : V2.0  & ST 3.5.0
* Author             : zhanli 719901725@qq.com & JustFeng.
* Date of Issued     : 2019.5.26 zhanli : Create
* Comments           : STM32 串口驱动     
********************************************************************************/
#include "sys.h"
#include "usart.h"	  
#include "stm32f10x_gpio.h"
#include "stm32f10x_usart.h"
#include "stm32f10x_rcc.h"

#if 1

#pragma import(__use_no_semihosting)             
//标准库需要的支持函数                 
struct __FILE { 
	int handle; 
}; 

FILE __stdout;       
//定义_sys_exit()以避免使用半主机模式    
_sys_exit(int x) 
{ 
	x = x; 
} 
//重定义fputc函数 
int fputc(int ch, FILE *f)
{      
	while((USART1->SR&0X40)==0);//循环发送,直到发送完毕   
    USART1->DR = (u8) ch;      
	return ch;
}
#endif 

#if EN_USART1_RX                    //如果使能了接收
//注意,读取USARTx->SR能避免莫名其妙的错误   	
u8 USART_RX_BUF[USART_REC_LEN];     //接收缓冲,最大USART_REC_LEN个字节.
//接收状态
//bit15，	接收完成标志
//bit14，	接收到0x0d
//bit13~0，	接收到的有效字节数目

u16 USART_RX_STA = 0;       //接收状态标记	  

/**----------------------------------------------------------------------
* Function    : uart_init
* Description : STM32 串口1初始化函数
* Input       : bound : 波特率
* Author      : zhanli&719901725@qq.com
* Date        : 2019/5/26 zhanli
*---------------------------------------------------------------------**/
void uart_init(u32 bound){
	
	//GPIO端口设置
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	
	// 使能USART1，GPIOA时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA, ENABLE);
	// 复位串口1
	USART_DeInit(USART1);  
	
	// USART1_TX PA.9 配置推挽输出
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	// 复用推挽输出
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	
	GPIO_Init(GPIOA, &GPIO_InitStructure); 

	// USART1_RX PA.10 配置浮空输入
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &GPIO_InitStructure);  

	// USART 初始化,一般设置为9600;
	USART_InitStructure.USART_BaudRate = bound;
	// 字长为8位数据格式
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	// 一个停止位
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	// 无奇偶校验位
	USART_InitStructure.USART_Parity = USART_Parity_No;
	// 无硬件数据流控制
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式

	// 初始化串口
	USART_Init(USART1, &USART_InitStructure); 
	// 开启中断
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	// 使能串口 
	USART_Cmd(USART1, ENABLE);                   

}

/**----------------------------------------------------------------------
* Function    : USART1_IRQHandler
* Description : 串口1中断服务程序
* Author      : zhanli&719901725@qq.com
* Date        : 2019/5/26 zhanli
*---------------------------------------------------------------------**/
void USART1_IRQHandler(void)
{
	u8 Res;
	//接收中断(接收到的数据必须是0x0d 0x0a结尾)
	if(USART_GetITStatus(USART1, USART_IT_RXNE) == RESET)
		return;

	// 读取接收到的数据
	Res = USART_ReceiveData(USART1);	
	
	// 接收完成
	if((USART_RX_STA & 0x8000) != 0)
		return;
	
	//接收到了0x0d
	if(USART_RX_STA & 0x4000)
	{
		if(Res!=0x0a)USART_RX_STA=0;//接收错误,重新开始
		else USART_RX_STA|=0x8000;	//接收完成了 
	}else //还没收到0X0D
	{	
		if(Res==0x0d)USART_RX_STA|=0x4000;
		else{
			USART_RX_BUF[USART_RX_STA&0X3FFF]=Res ;
			USART_RX_STA++;
			// 接收数据错误,重新开始接收	
			if(USART_RX_STA>(USART_REC_LEN-1))USART_RX_STA=0;  
		}		 
	}
} 

#endif	

