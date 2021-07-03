/**
  ******************************************************************************
  * @file    hw_config.h
  * @author  MCD Application Team
  * @version V3.4.0
  * @date    29-June-2012
  * @brief   Hardware Configuration & Setup
  ******************************************************************************
  */


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __HW_CONFIG_H
#define __HW_CONFIG_H

/* Includes ------------------------------------------------------------------*/
#include "platform_config.h"
#include "usb_type.h"
#include <stdbool.h>


void Configure_Debug(void);

void Set_System(void);

void Sensor_Init(void);


void Configure_Debug(void);
void Set_System(void);
void Reset_Device(void);
void Set_USBClock(void);
void Enter_LowPowerMode(void);
void Leave_LowPowerMode(void);
void Enter_Stop(void);
void Wake_From_Stop(void);
void Sensor_Sleep(void);
void Sensor_Deinit(void);
void USB_Interrupts_Config(void);
void Enable_EXTInterrupts(void);

void USB_Cable_Config (FunctionalState NewState);
void Set_Stored_Serial(char *SerialString);
void Set_Use_Serial(void);
void Get_SerialNum(char *SerialString, bool UseUnicode);



#endif  /*__HW_CONFIG_H*/

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
