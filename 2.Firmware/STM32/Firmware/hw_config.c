/************************************************************************************
 * 文    件  ：hw_config.c
 * 描    述  ：GamePadV1.0 硬件驱动       
 * ST库版本  ：ST3.5.0
 * 作    者  ：TrackVR：LogZhan,JustFeng.
 * 修    订	 : 2017-1-17 Logzhan 创建Ver 0.0.1
               1) 删除部分Oculus的冗余代码，删除部分冗余头文件.
*************************************************************************************/
#include "sys.h"
#include "hw_config.h"
#include "usb_lib.h"
#include "usb_desc.h"
#include "usb_pwr.h"
#include "gpio.h"
#include <string.h>
#include "stm32f10x_exti.h"
#include "misc.h"
#include "platform_config.h"
#include "Time.h"

ErrorStatus HSEStartUpStatus;

#ifdef DK_HD
static uint16_t use_uuid_serial = 2;
#else /* DK_HD */
static uint16_t use_uuid_serial = 0;
#endif /* DK_HD */

/* Extern variables ----------------------------------------------------------*/
extern __IO uint8_t exit_stop_mode;

/************************************************************************
* 函数名 ：Set_System(void)
* 功能   ：配置STM32的相关基础性功能
* 作者   ：Laputa_logzhan
* 时间   ：2015/10/3
************************************************************************/
void Set_System(void)
{
	/*系统定时器初始化*/
	SysTick_Init();	
	/*调试接口设定*/
	Configure_Debug();
	/*开启APB1电源*/
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);	
	/*延时初始化*/	
	Delay_Init();		  
	/*开启外设时钟以及设置中断分组*/	
	NVIC_Configuration();   
}
/************************************************************************
* 函数名 ：Configure_Debug(void)
* 功能   ：Debug配置
* 作者   ：TrackVR：logzhan
* 时间   ：2015/10/3
************************************************************************/
void Configure_Debug(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
}


void Reset_Device(void)
{
    // if we have USB disconnect, automatically unplug and
    // reset the device
#ifdef USB_DISCONNECT_PIN
    // Power off the sensors first
    Sensor_Deinit();
    USB_Cable_Config(DISABLE);
    Delay_Ms(10);
    NVIC_SystemReset();
#endif /* USB_DISCONNECT_PIN */
}

/*******************************************************************************
* Function Name  : Set_USBClock
* Description    : Configures USB Clock input (48MHz).
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void Set_USBClock(void)
{
  /* Select USBCLK source */
#ifdef USE_F102
  RCC_USBCLKConfig(RCC_USBCLKSource_PLLCLK_Div1);
#else
  RCC_USBCLKConfig(RCC_USBCLKSource_PLLCLK_1Div5);
#endif /* USE_F102 */

  /* Enable the USB clock */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USB, ENABLE);
}

/*******************************************************************************
* Function Name  : Enter_LowPowerMode.
* Description    : Power-off system clocks and power while entering suspend mode.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void Enter_LowPowerMode(void)
{
  /* Set the device state to suspend */
  bDeviceState = SUSPENDED;
  exit_stop_mode = 0;
}

/*******************************************************************************
* Function Name  : Leave_LowPowerMode.
* Description    : Restores system clocks and power while exiting suspend mode.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void Leave_LowPowerMode(void)
{
  DEVICE_INFO *pInfo = &Device_Info;
  exit_stop_mode = 1;

  /* Set the device state to the correct state */
  if (pInfo->Current_Configuration != 0)
  {
    /* Device configured */
    bDeviceState = CONFIGURED;
  }
  else
  {
    bDeviceState = ATTACHED;
  }
}

void Enter_Stop(void)
{
    // Going into stop mode works, but the USB wakeup interrupt never fires.
    // Instead, just shut off the external resonator and PLL and go to
    // 8 MHz internal RC.  Gets us down to ~1.7 mA.
//    DBGMCU_Config(DBGMCU_SLEEP | DBGMCU_STANDBY | DBGMCU_STOP, ENABLE);
//    PWR_EnterSTOPMode(PWR_Regulator_ON, PWR_STOPEntry_WFI);

    RCC_HSICmd(ENABLE);

    /* Wait till HSI is ready */
    while (RCC_GetFlagStatus(RCC_FLAG_HSIRDY) == RESET) {}

    /* Select HSI as system clock source */
    RCC_SYSCLKConfig(RCC_SYSCLKSource_HSI);

    /* Disable PLL1 */
    RCC_PLLCmd(DISABLE);

    /* Disable HSE */
    RCC_HSEConfig(RCC_HSE_OFF);

    // Shut off core clocks
    __WFI();
}

// Restart clocks
void Wake_From_Stop(void)
{
    /* Wait till HSE is ready */
    HSEStartUpStatus = RCC_WaitForHSEStartUp();

    /* Enable HSE */
    RCC_HSEConfig(RCC_HSE_ON);

    /* Wait till HSE is ready */
    while (RCC_GetFlagStatus(RCC_FLAG_HSERDY) == RESET) {}

    /* Enable PLL1 */
    RCC_PLLCmd(ENABLE);

    /* Wait till PLL1 is ready */
    while (RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET) {}

    /* Select PLL as system clock source */
    RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);

    /* Wait till PLL is used as system clock source */
    while (RCC_GetSYSCLKSource() != RCC_CFGR_SWS_PLL) {}
}

void Sensor_Sleep(void){

}

void Sensor_Deinit(void){
}

/*******************************************************************************
* Function Name  : USB_Interrupts_Config.
* Description    : 配置USB的中断
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void USB_Interrupts_Config(void)
{
	EXTI_InitTypeDef EXTI_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	/* Configure the EXTI line 18 connected internally to the USB IP */
	EXTI_ClearITPendingBit(EXTI_Line18);
	EXTI_InitStructure.EXTI_Line = EXTI_Line18; // USB resume from suspend mode
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);
	
	/* 2 bit for pre-emption priority, 2 bits for subpriority */
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	/* Enable the USB interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = USB_LP_CAN1_RX0_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	/* Enable the USB Wake-up interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = USBWakeUp_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_Init(&NVIC_InitStructure);
}

/*******************************************************************************
* Function Name  : USB_Cable_Config.
* Description    : Software Connection/Disconnection of USB Cable.
* Input          : NewState: new state.
* Output         : None.
* Return         : None
*******************************************************************************/
void USB_Cable_Config (FunctionalState NewState)
{
#ifdef USB_DISCONNECT_PIN
  GPIO_InitTypeDef GPIO_InitStructure;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Pin = USB_DISCONNECT_PIN;

  if (NewState == DISABLE)
  {
    // Go high-Z to disconnect the usb pullup resistor
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(USB_DISCONNECT, &GPIO_InitStructure);
  }
  else
  {
    // pull up the pullup resistor
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIO_DISCONNECT, ENABLE);
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(USB_DISCONNECT, &GPIO_InitStructure);
    GPIO_SetBits(USB_DISCONNECT, USB_DISCONNECT_PIN);
  }
#endif /* USB_DISCONNECT_PIN */
}

/************************************************************************
* 函数名 ：  Enable_EXTInterrupts(void)
* 说明   ：  使能外部中断
* 时间   ：  2017/1/16
* 作者   ：  TrackVR：logzhan
************************************************************************/
void Enable_EXTInterrupts(void){
}

static void IntToBase32(uint32_t value, char *buf, uint8_t len, bool unicode)
{
    uint8_t mult = unicode ? 2 : 1;
	uint8_t i;
    for (i = 0; i < len; i++) {
        // Select 5 bits
        uint8_t bits = value & 0x1F;

        if (bits < 0xA) {
            buf[i*mult] = bits + '0';
        } else {
            buf[i*mult] = bits + 'A' - 10;
        }
        if (unicode) buf[i*mult + 1] = 0;
        value = value >> 5;
    }
}


void Set_Stored_Serial(char *SerialString){
    Set_Use_Serial();
}

// Legacy serial number check
static bool Get_Use_Serial(void)
{
    uint16_t serial_set = 0;
	if (use_uuid_serial)
        return 1;

    //EE_ReadVariable(EE_SERIAL_SET, &serial_set);

    if (serial_set) {
        use_uuid_serial = serial_set;
        return 1;
    }

    return 0;
}

// Legacy method for setting the serial number
void Set_Use_Serial(void)
{
    Get_Use_Serial();

    // Set the serial if it has been set by the legacy UUID method
    if (use_uuid_serial < 2) {
        //FLASH_Unlock();
        //EE_WriteVariable(EE_SERIAL_SET, 2);
        //FLASH_Lock();
        use_uuid_serial = 2;
    }
}

/*******************************************************************************
* Function Name  : Get_SerialNum.
* Description    : Create the serial number string descriptor.
                   创建一个序列号字符串描述符，这个将会在Oculus Utility 中显示
* 修正           ：2015-5-14：精简了原Oculus的代码，同时解决之前不能在Oculus
                   Utility 中显示序列号的问题 --- Laputa Zhan
*******************************************************************************/
void Get_SerialNum(char *SerialString, bool UseUnicode)
{
	/*从一个假的序列号开始，因此所有的设备看起来都是一样的*/
	uint32_t Device_Serial0 = 0xAAAAAAAA, Device_Serial1 = 0xAAAAAAAA;
	uint32_t serial0 = *(__IO uint32_t*)(0x1FFFF7E8);
	uint32_t serial1 = *(__IO uint32_t*)(0x1FFFF7EC);
	uint32_t serial2 = *(__IO uint32_t*)(0x1FFFF7F0);

	Device_Serial0 = serial2 ^ ((serial2 & 0xC000) >> 2);
	Device_Serial1 = serial1 ^ serial0;
	Device_Serial1 = Device_Serial1 ^ ((Device_Serial1 & 0xC000) >> 2);

	IntToBase32(Device_Serial0, &SerialString[0], 6, 0);
	IntToBase32(Device_Serial1, &SerialString[6], 6, 0);    
}
