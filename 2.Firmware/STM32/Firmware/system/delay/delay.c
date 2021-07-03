/******************** (C) COPYRIGHT 2020 GEEKIMU *******************************
* File Name          : delay.c
* Current Version    : V2.0  & ST 3.5.0
* Author             : zhanli 719901725@qq.com & JustFeng.
* Date of Issued     : 2015.5.15 zhanli : Create
* Comments           : STM32系列延时函数   
********************************************************************************/
#include <stdint.h>
#include "delay.h"
#include "misc.h"

static uint8_t  fac_us  = 0;                       // us延时倍乘数
static uint16_t fac_ms  = 0; 

/**----------------------------------------------------------------------
* Function    : Delay_Init
* Description : 初始化延时函数（不支持ucos）
* Author      : zhanli&719901725@qq.com
* Date        : 2015/2/13 zhanli
*---------------------------------------------------------------------**/
void Delay_Init(void)	 
{
	// 选择外部时钟  HCLK/8
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);	
	// 为系统时钟的1/8  	
	fac_us = SystemCoreClock / 8000000;	     
	// 非ucos下,代表每个ms需要的systick时钟数 	
	fac_ms = (uint16_t)fac_us * 1000;                                    
}

/**----------------------------------------------------------------------
* Function    : Delay_DeInit
* Author      : zhanli&719901725@qq.com
* Description : 重新初始化延时函数（不支持ucos）
* Date        : 2015/2/13 zhanli
*---------------------------------------------------------------------**/
void Delay_DeInit(void){
    SysTick->CTRL = 0;
}

/**----------------------------------------------------------------------
* Function    : Delay_Ms(uint32_t ms)
* Description : 延时n毫秒，对于延时的取值不能大于1864.SysTick->LOAD为
                24位寄存器,所以,最大延时为:
                nms <= 0xffffff * 8 * 1000 / SYSCLK; SYSCLK单位为Hz,nms单
                位为ms.对应72M条件下最大延时,nms<=1864nms。
* Author      : zhanli&719901725@qq.com
* Date        : 2015/2/13 zhanli
*---------------------------------------------------------------------**/
void Delay_Ms(uint32_t ms)
{	 		  	  
	uint32_t temp;		   
	SysTick->LOAD =(u32)ms*fac_ms;                 //时间加载(SysTick->LOAD为24bit)
	SysTick->VAL  = 0x00;                          //清空计数器
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;       //开始倒数  
	do
	{
		temp=SysTick->CTRL;
	}
	while(temp&0x01&&!(temp&(1<<16)));             //等待时间到达   
	SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;       //关闭计数器
	SysTick->VAL =0X00;                            //清空计数器	  	    
} 
	
/**----------------------------------------------------------------------
* Function    : Delay_Us(uint32_t nus)
* Description : 延时n微秒，对于延时的取值不能大于1864us
* Author      : zhanli&719901725@qq.com
* Date        : 2015/2/13 zhanli
*---------------------------------------------------------------------**/    								   
void Delay_Us(uint32_t nus)
{		
	uint32_t temp;	    	 
	SysTick->LOAD=nus*fac_us;                      //时间加载	  		 
	SysTick->VAL=0x00;                             //清空计数器
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;       //开始倒数	 
	do{
		temp=SysTick->CTRL;
	}
	while(temp&0x01&&!(temp&(1<<16)));             //等待时间到达   
	SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;       //关闭计数器
	SysTick->VAL =0x00;                            //清空计数器	 
}
