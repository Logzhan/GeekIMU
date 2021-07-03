/******************** (C) COPYRIGHT 2020 GEEKIMU *******************************
* File Name          : time.c
* Current Version    : V2.0
* Author             : zhanli 719901725@qq.com
* Date of Issued     : 2015.10.3
* Comments           : TrackVR 体感手柄 定时器配置
********************************************************************************/
#include "time.h"
#include "stm32f10x_tim.h"
#include "stm32f10x_rcc.h"
#include "misc.h"

/**----------------------------------------------------------------------
* Function    : TIM3_Int_Init(uint16_t arr,uint16_t psc)
* Description : 1ms定时器，用于1000hz的传感器数据发送
* Author      : zhanli&719901725@qq.com
* Date        : 2021/6/22 zhanli
*---------------------------------------------------------------------**/
void TIM3_Int_Init(uint16_t arr,uint16_t psc)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	/* 使能定时器3                                                            */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); 
	
	/* 设置在下一个更新事件装入活动的自动重装载寄存器周期的值计数到5000为500ms*/
	TIM_TimeBaseStructure.TIM_Period = arr; 
	   
	/* 设置用来作为TIMx时钟频率除数的预分频值  10Khz的计数频率                */ 
	TIM_TimeBaseStructure.TIM_Prescaler = psc;  
	
	/* 设置时钟分割:TDTS = Tck_tim                                            */
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; 
	/* TIM向上计数模式                                                        */
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	/* 根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位         */
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); 
	
	TIM_ITConfig(TIM3, TIM_IT_Update ,ENABLE);
	
	/* 配置定时器3的优先级                                                    */
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn; 
	/* 先占优先级0级                                                          */
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	/* 从优先级3级                                                            */
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3; 
	/* IRQ通道被使能                                                          */
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	/* 根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器                    */
	NVIC_Init(&NVIC_InitStructure); 
	
	TIM_Cmd(TIM3, ENABLE);  
							 
}
/**----------------------------------------------------------------------
* Function    : SysTick_Init
* Description : 主要是初始化定时器4
* Author      : zhanli&719901725@qq.com
* Date        : 2015/10/4 zhanli
*---------------------------------------------------------------------**/
void SysTick_Init(void)
{
	/* ** 初始化定时器4，用于陀螺仪姿态解算  ***/
	
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	
	/*时钟使能*/
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE); 
	
	/*设置在下一个更新事件装入活动的自动重装载寄存器周期的值计数到5000为500ms*/
	TIM_TimeBaseStructure.TIM_Period = 0xffff; 
	
	/*设置用来作为TIMx时钟频率除数的预分频值  10Khz的计数频率*/
	TIM_TimeBaseStructure.TIM_Prescaler =71; 
	
	/*设置时钟分割:TDTS = Tck_tim*/	
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; 
	
	/*TIM向上计数模式*/
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  
	
	/*根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位*/
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); 
	
	TIM_Cmd(TIM4, ENABLE);
	
	/* 初始化定时器2                                                           */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); 
	
	/* 设置在下一个更新事件装入活动的自动重装载寄存器周期的值计数到5000为500ms */
	TIM_TimeBaseStructure.TIM_Period = 0xffff; 
	
	/* 设置用来作为TIMx时钟频率除数的预分频值  10Khz的计数频率                 */
	TIM_TimeBaseStructure.TIM_Prescaler =71; 
	
	/* 设置时钟分割:TDTS = Tck_tim                                             */	
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; 
	
	/* TIM向上计数模式                                                         */
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  
	
	/* 根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位          */
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); 
	
	TIM_Cmd(TIM2, ENABLE);
}

/**----------------------------------------------------------------------
* Function    : Get_NowTime(void)
* Description : 用于AHRS算法解算计算采样时间(传感器0),返回当前systick计数
                器值,32位
* Author      : zhanli&719901725@qq.com
* Date        : 2017/1/15 zhanli
*---------------------------------------------------------------------**/
float Get_NowTime(void)  
{
	float temp = 0.0f;
	static uint32_t now = 0;                                       /* 采样周期计数 单位 us				*/
 	now = TIM4->CNT;                                               /* 读高16位时间	                    */
  	TIM4->CNT = 0;		                                           /* 重新计时							*/
	temp = (float)now / 2000000.0f;                                /* 换算成ms，再除以2得(1/2 *T)       */
	return temp;
}


