/******************** (C) COPYRIGHT 2020 GEEKIMU *******************************
* File Name          : platform_common.h
* Current Version    : V2.0  & ST 3.5.0
* Author             : zhanli 719901725@qq.com & JustFeng.
* Date of Issued     : 2017.1.16 zhanli : Create
* Comments           : GEEKIMU 平台配置
********************************************************************************/
#ifndef _PLATFORM_COMMON_
#define _PLATFORM_COMMON_

#if defined(STM32L1XX_MD) || defined(STM32L1XX_HD)|| defined(STM32L1XX_MD_PLUS)
 #include "stm32l1xx.h"
#elif defined (STM32F10X_LD) || defined (STM32F10X_MD) || defined (STM32F10X_HD) || defined (STM32F10X_XL) || defined (STM32F10X_CL)
 #include "stm32f10x.h"
#endif

#endif /* _PLATFORM_COMMON_ */
