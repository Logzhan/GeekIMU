/******************** (C) COPYRIGHT 2020 GEEKIMU *******************************
* File Name          : gpio.c
* Current Version    : V2.0  & ST 3.5.0
* Author             : zhanli 719901725@qq.com & JustFeng.
* Date of Issued     : 2017.1.11 zhanli : Create
* Comments           : STM32 GPIO相关功能   
********************************************************************************/
#include "gpio.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "sys.h"
#include "led.h"

#define USB_ENABLE_PERIPH_CLK   RCC_APB2Periph_GPIOA             // USB使能端口时钟
#define USB_ENABLE_GPIO_TYPE    GPIOA                            // USB使能端口类型
#define USB_ENABLE_PIN         	GPIO_Pin_2                       // USB使能端口PA2

/**----------------------------------------------------------------------
* Function    : Init_USB_Enable_GPIO
* Description : USB使能控制IO初始化
* Author      : zhanli&719901725@qq.com & JustFeng.
* Date        : 2015/2/13 zhanli
*---------------------------------------------------------------------**/
void Init_USB_Enable_GPIO()
{
	GPIO_InitTypeDef  GPIO_InitStructure;	

	RCC_APB2PeriphClockCmd(USB_ENABLE_PERIPH_CLK, ENABLE);	       /* 使能PB端口时钟					*/
																									
	GPIO_InitStructure.GPIO_Pin = USB_ENABLE_PIN;				   /* LED0-->PB.9 端口配置				*/
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		       /* 推挽输出							*/
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		       /* IO口速度为50MHz					*/
	GPIO_Init(USB_ENABLE_GPIO_TYPE, &GPIO_InitStructure);		   /* 根据设定参数初始化GPIOB.9			*/
	
	// USB上拉使能，默认USB开启
	GPIO_SetBits(USB_ENABLE_GPIO_TYPE, USB_ENABLE_PIN); 
}
/**----------------------------------------------------------------------
* Function    : GPIO_Configuration
* Description : 在Set_System()被调用，用于配置各种IO口
* Author      : zhanli&719901725@qq.com & JustFeng.
* Date        : 2015/9/17 zhanli 
*---------------------------------------------------------------------**/
void GPIO_Configuration(void)
{
	// USB使能端口初始化
	Init_USB_Enable_GPIO();
	// LED初始化
	LED_Init_GPIO();		
}






