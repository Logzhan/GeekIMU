/******************** (C) COPYRIGHT 2020 GEEKIMU *******************************
* File Name          : led.c
* Current Version    : V2.0  & ST 3.5.0
* Author             : zhanli 719901725@qq.com & JustFeng.
* Date of Issued     : 2017.1.16 zhanli : Create
* Comments           : GEEK LED驱动 
********************************************************************************/
#include "sys.h"
#include "led.h"

#define LED_PERIPH_CLK   RCC_APB2Periph_GPIOB             // LED使能端口时钟
#define LED_GPIO_TYPE    GPIOB                            // LED使能端口类型
#define LED_PIN          GPIO_Pin_7                       // LED使能端口PB7

/**----------------------------------------------------------------------
* Function    : LED_Init_GPIO(void)
* Description : LED 灯IO口初始化
* Author      : zhanli&719901725@qq.com
* Date        : 2015/2/13 zhanli
*---------------------------------------------------------------------**/
void LED_Init_GPIO(void)
{
	 GPIO_InitTypeDef  GPIO_InitStructure;	 
	 
	 RCC_APB2PeriphClockCmd(LED_PERIPH_CLK, ENABLE);	           /* 使能LED端口时钟			*/
																								
	 GPIO_InitStructure.GPIO_Pin   = LED_PIN;				       /* LED0端口配置				*/
	 GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP; 		       /* 推挽输出					*/
	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		       /* IO口速度为50MHz			*/
	 GPIO_Init(LED_GPIO_TYPE, &GPIO_InitStructure);				   /* 根据设定参数初始化LED		*/
}
 
/**----------------------------------------------------------------------
* Function    : LED_Off
* Description : LED 灯关闭
* Author      : zhanli&719901725@qq.com
* Date        : 2015/2/13 zhanli
*---------------------------------------------------------------------**/
void LED_Off(void){
	GPIO_ResetBits(LED_GPIO_TYPE, LED_PIN); 
}

/**----------------------------------------------------------------------
* Function    : LED_Off
* Description : LED 灯打开
* Author      : zhanli&719901725@qq.com
* Date        : 2015/2/13 zhanli
*---------------------------------------------------------------------**/
void LED_On(void){
	GPIO_SetBits(LED_GPIO_TYPE, LED_PIN); 
}
