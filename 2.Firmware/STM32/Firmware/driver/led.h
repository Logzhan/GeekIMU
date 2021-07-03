/******************** (C) COPYRIGHT 2020 GEEKIMU *******************************
* File Name          : led.h
* Current Version    : V2.0  & ST 3.5.0
* Author             : zhanli 719901725@qq.com & JustFeng.
* Date of Issued     : 2017.1.16 zhanli : Create
* Comments           : GEEK LED驱动 
********************************************************************************/
#ifndef _LED_H_
#define _LED_H_	 
#include "sys.h"

/**----------------------------------------------------------------------
* Function    : LED_Init_GPIO(void)
* Description : LED 灯IO口初始化
* Author      : zhanli&719901725@qq.com
* Date        : 2015/2/13 zhanli
*---------------------------------------------------------------------**/
void LED_Init_GPIO(void);

/**----------------------------------------------------------------------
* Function    : LED_Off
* Description : LED 灯关闭
* Author      : zhanli&719901725@qq.com
* Date        : 2015/2/13 zhanli
*---------------------------------------------------------------------**/
void LED_Off(void);

/**----------------------------------------------------------------------
* Function    : LED_Off
* Description : LED 灯打开
* Author      : zhanli&719901725@qq.com
* Date        : 2015/2/13 zhanli
*---------------------------------------------------------------------**/
void LED_On(void);
				    
#endif
