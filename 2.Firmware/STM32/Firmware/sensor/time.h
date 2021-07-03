/******************** (C) COPYRIGHT 2020 GEEKIMU *******************************
* File Name          : time.h
* Current Version    : V2.0
* Author             : zhanli 719901725@qq.com
* Date of Issued     : 2015.10.3
* Comments           : TrackVR 体感手柄 定时器配置
********************************************************************************/
#ifndef _TIME_H_
#define _TIME_H_

#include "stm32f10x.h"

/**----------------------------------------------------------------------
* Function    : TIM3_Int_Init(u16 arr,u16 psc)
* Description : 1ms定时器，用于1000hz的传感器数据发送
* Author      : zhanli&719901725@qq.com
* Date        : 2021/6/22 zhanli
*---------------------------------------------------------------------**/
void TIM3_Int_Init(uint16_t arr,uint16_t psc);

/**----------------------------------------------------------------------
* Function    : SysTick_Init
* Description : 主要是初始化定时器4
* Author      : zhanli&719901725@qq.com
* Date        : 2015/10/4 zhanli
*---------------------------------------------------------------------**/
void SysTick_Init(void);

/**----------------------------------------------------------------------
* Function    : Get_NowTime(void)
* Description : 用于AHRS算法解算计算采样时间(传感器0),返回当前systick计数
                器值,32位
* Author      : zhanli&719901725@qq.com
* Date        : 2017/1/15 zhanli
*---------------------------------------------------------------------**/
float Get_NowTime(void);

#endif

