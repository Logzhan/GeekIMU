#include "sys.h"
#include "stm32f10x_rcc.h"
#include "misc.h"

void NVIC_Configuration(void)
{
	// 开启外设的时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB, ENABLE);	
	//设置NVIC中断分组2:2位抢占优先级，2位响应优先级
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	   
}
