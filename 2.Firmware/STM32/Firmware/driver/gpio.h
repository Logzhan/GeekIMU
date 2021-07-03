/******************** (C) COPYRIGHT 2020 GEEKIMU *******************************
* File Name          : gpio.h
* Current Version    : V2.0  & ST 3.5.0
* Author             : zhanli 719901725@qq.com & JustFeng.
* Date of Issued     : 2017.1.11 zhanli : Create
* Comments           : STM32 GPIO相关功能   
********************************************************************************/

#ifndef _GPIO_H_
#define _GPIO_H_

/**----------------------------------------------------------------------
* Function    : Init_USB_Enable_GPIO
* Description : USB使能控制IO初始化
* Author      : zhanli&719901725@qq.com & JustFeng.
* Date        : 2015/2/13 zhanli
*---------------------------------------------------------------------**/
void Init_USB_Enable_GPIO(void);

/**----------------------------------------------------------------------
* Function    : GPIO_Configuration
* Description : 在Set_System()被调用，用于配置各种IO口
* Author      : zhanli&719901725@qq.com & JustFeng.
* Date        : 2015/9/17 zhanli 
*---------------------------------------------------------------------**/
void GPIO_Configuration(void);


#endif /* _GPIO_H_ */
