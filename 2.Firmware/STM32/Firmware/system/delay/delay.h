/******************** (C) COPYRIGHT 2020 GEEKIMU *******************************
* File Name          : delay.h
* Current Version    : V2.0  & ST 3.5.0
* Author             : zhanli 719901725@qq.com & JustFeng.
* Date of Issued     : 2015.5.15 zhanli : Create
* Comments           : STM32系列延时函数   
********************************************************************************/

#ifndef _DELAY_H_
#define _DELAY_H_

#include <stdint.h>

/**----------------------------------------------------------------------
* Function    : Delay_Init
* Author      : zhanli&719901725@qq.com
* Description : 初始化延时函数（不支持ucos）
* Date        : 2015/2/13 zhanli
*---------------------------------------------------------------------**/	
void Delay_Init(void);

/**----------------------------------------------------------------------
* Function    : Delay_DeInit
* Author      : zhanli&719901725@qq.com
* Description : 重新初始化延时函数（不支持ucos）
* Date        : 2015/2/13 zhanli
*---------------------------------------------------------------------**/
void Delay_DeInit(void);

/**----------------------------------------------------------------------
* Function    : Delay_Ms(uint32_t ms)
* Description : 延时n毫秒，对于延时的取值不能大于1864.SysTick->LOAD为
                24位寄存器,所以,最大延时为:
                nms <= 0xffffff * 8 * 1000 / SYSCLK; SYSCLK单位为Hz,nms单
                位为ms.对应72M条件下最大延时,nms<=1864nms。
* Author      : zhanli&719901725@qq.com
* Date        : 2015/2/13 zhanli
*---------------------------------------------------------------------**/
void Delay_Ms(uint32_t ms);

/**----------------------------------------------------------------------
* Function    : Delay_Us(uint32_t nus)
* Description : 延时n微秒，对于延时的取值不能大于1864us
* Author      : zhanli&719901725@qq.com
* Date        : 2015/2/13 zhanli
*---------------------------------------------------------------------**/  
void Delay_Us(uint32_t nus);

#endif /* _DELAY_H_ */
