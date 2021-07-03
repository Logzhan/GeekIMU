/******************** (C) COPYRIGHT 2020 GEEKIMU *******************************
* File Name          : gpio.c
* Current Version    : V2.0  & ST 3.5.0
* Author             : zhanli 719901725@qq.com & JustFeng.
* Date of Issued     : 2017.1.11 zhanli : Create
* Comments           : USB feature reports
********************************************************************************/
#include "feature_config.h"
#include <stdlib.h>
#include <string.h>
#include "platform_config.h"
#include "usb_core.h"
#include "usb_init.h"
#include "calibrate.h"
//#include "eeprom.h"
#include "gpio.h"
#include "sys.h"
#include "stmflash.h"

enum {
    FEATURE_CONFIG = 2,
    FEATURE_CALIBRATE = 3,
    FEATURE_RANGE = 4,
    FEATURE_REGISTER = 5,
    FEATURE_DFU = 6,
    FEATURE_GPIO = 7,
    FEATURE_KEEP_ALIVE = 8,
    FEATURE_DISPLAY_INFO = 9,
    FEATURE_SERIAL = 10,
	  FEATURE_OFFSET = 11	
};

// Report ID and Command ID
#define FEATURE_HEADER_SIZE 3

#define FEATURE_CONFIG_SIZE (FEATURE_HEADER_SIZE+4)
#define FEATURE_CALIBRATE_SIZE (FEATURE_HEADER_SIZE+CALIBRATION_SIZE)
#define FEATURE_RANGE_SIZE (FEATURE_HEADER_SIZE+5)
#define FEATURE_REGISTER_SIZE (FEATURE_HEADER_SIZE+3)
#define FEATURE_DFU_SIZE (FEATURE_HEADER_SIZE+1)
#define FEATURE_GPIO_SIZE (FEATURE_HEADER_SIZE+2)
#define FEATURE_KEEP_ALIVE_SIZE (FEATURE_HEADER_SIZE+2)
#define FEATURE_DISPLAY_INFO_SIZE (FEATURE_HEADER_SIZE+53)
#define FEATURE_SERIAL_SIZE (FEATURE_HEADER_SIZE+12)
#define FEATURE_OFFSET_SIZE (FEATURE_HEADER_SIZE+49)
#define FLASH_DFU_FLASH  0X0800FF48 		  //模拟EEPROM的用于DFU地址

#define FEATURE_OFFSET_SET_GYRO 1
#define FEATURE_OFFSET_SET_ACC	2
#define FEATURE_OFFSET_SET_MAG  3
#define FEATURE_OFFSET_SET_LED  4
#define FEATURE_OFFSET_GET_GYRO 0x11
#define FEATURE_OFFSET_GET_ACC	0x12
#define FEATURE_OFFSET_GET_MAG  0x13

feature_config_s global_config = {0};
bool global_config_set = 0;
feature_calibrate_s global_calibrate = {0};
bool global_calibrate_set = 0;
feature_range_s global_range = {0};
bool global_range_set = 0;
feature_register_s global_reg = {0};
bool global_reg_set = 0;
feature_dfu_s global_dfu = {0};
bool global_dfu_set = 0;
feature_gpio_s global_gpio = {0};
feature_keep_alive_s global_keep_alive = {0};
bool global_keep_alive_set = 0;
feature_display_info_s global_display_info = {0};
feature_serial_s global_serial = {0};
bool global_offset_set = 0;
feature_offset_s global_offset = {0};

//enum LED_COLOR global_LED_color;
// Most recent command ID globally
static uint16_t feature_config_command_id = 0;
u8   DM_USB_Command = 0;
bool got_command = 0;

// For the largest buffer we need
uint8_t feature_get_buf[FEATURE_CALIBRATE_SIZE];
uint8_t feature_set_buf[FEATURE_CALIBRATE_SIZE];

/******************************************************
*函    数：  feature_config_pack_config
*功    能：  
*修改时间：  2015-5-14
*输    入：  无
*******************************************************/
static void feature_config_pack_config(void)
{
    feature_get_buf[0] = FEATURE_CONFIG;
    *(uint16_t *)(feature_get_buf+1) = global_config.command_id;
    feature_get_buf[3] = global_config.use_raw |			   /*传感器原始数据在于内部调试才使用 config.use_raw*/
                         (global_config.calibrate << 1) |
                         (global_config.use_calibration << 2) |
                         (global_config.autocalibration << 3) |
                         (global_config.motion_keep_alive << 4) |
                         (global_config.command_keep_alive << 5) |
                         (global_config.use_ovr_coordinates << 6);
    feature_get_buf[4] = global_config.interval;
    // For now, just hard code to 1000 Hz.  This is for forwards compatibility
    // with future trackers with different sample rates.
    *(uint16_t *)(feature_get_buf+5) = global_config.sample_rate = 1000;
}

/******************************************************
*函    数：  feature_config_pack_range
*功    能：  Oculus SDK会请求传感器数据范围
			       通过这个函数打包数据这个函数会在USB处理中
             心中被调用
*修改时间：  2015-5-11
*******************************************************/
static void feature_config_pack_range(void)
{
    feature_get_buf[0] = FEATURE_RANGE;	        /*report ID = 4 */   
    *(uint16_t *)(feature_get_buf+1) = global_range.command_id;

    feature_get_buf[3] = 2;						          /* 默认加速度计的范围为+—2G，参考手册  */

    *(uint16_t *)(feature_get_buf+4) = 2000;              /* 陀螺仪的范围是+-2000deg/s，参考手册 */
    *(uint16_t *)(feature_get_buf+6) = 1300;	          /* 地磁计的范围为+-1300，参考手册      */
}
/*******************************************************
**提供上位机寄存器信息
********************************************************/
static void feature_config_pack_register(void)
{
    feature_get_buf[0] = FEATURE_REGISTER;
    *(uint16_t *)(feature_get_buf+1) = global_reg.command_id;
    feature_get_buf[3] = global_reg.device;
    feature_get_buf[4] = global_reg.reg;
    feature_get_buf[5] = global_reg.payload;
}
/******************************************************
*函    数：  *feature_config_getreport
*功    能：  Oculus SDK 会发送请求，从这里返回数据给
			 Oculus SDK
*修改时间：  2015-3-29
*输    入：  无
*******************************************************/
uint8_t *feature_config_getreport(uint16_t length)
{
    // 根据报告ID选择
    switch (pInformation->USBwValue0)
	{
		// 配置特性
        case FEATURE_CONFIG:
            // On the first callback, we supply the length
            if (!length) {
                pInformation->Ctrl_Info.Usb_wLength = FEATURE_CONFIG_SIZE;
            } else {
                // On the second we return the filled buffer
                feature_config_pack_config();
                return feature_get_buf;
            }
            break;
		// 校准特性
        case FEATURE_CALIBRATE:
//            if (!length) {
//                pInformation->Ctrl_Info.Usb_wLength = FEATURE_CALIBRATE_SIZE;
//            } 
//			else {
//                feature_get_buf[0] = FEATURE_CALIBRATE;
//                *(uint16_t *)(feature_get_buf+1) = global_calibrate.command_id;
//				/*读取校准信息*/
//                calibrate_get(feature_get_buf+3);
//                // Calibrate is above 64 bytes, so we get called again with offset
//                return feature_get_buf + pInformation->Ctrl_Info.Usb_wOffset;
//            }
//            break;
		// 范围特性
        case FEATURE_RANGE:
            if (!length)
						{
                pInformation->Ctrl_Info.Usb_wLength = FEATURE_RANGE_SIZE;
            } 
						else
						{
                feature_config_pack_range();    /*打包范围特性*/
                return feature_get_buf;
            }
            break;
		/********************************************************
		FEATURE_REGISTER 这个类型是用来配置传感器的寄存器使用的, 
		Laputa 使用的是MPU9150，所以这个功能是无效的
		 ********************************************************/
        case FEATURE_REGISTER:
            if (!length) {
                pInformation->Ctrl_Info.Usb_wLength = FEATURE_REGISTER_SIZE;
            } else {
                feature_config_pack_register();	  /*打包寄存器信息*/
                return feature_get_buf;
            }
            break;

        case FEATURE_DFU:
            if (!length) {
                pInformation->Ctrl_Info.Usb_wLength = FEATURE_DFU_SIZE;
            } else {
                feature_get_buf[0] = FEATURE_DFU;
                *(uint16_t *)(feature_get_buf+1) = global_dfu.command_id;
                feature_get_buf[3] = global_dfu.use_dfu;
                return feature_get_buf;
            }
            break;

        case FEATURE_GPIO:
					
            if (!length) 
						{
                pInformation->Ctrl_Info.Usb_wLength = FEATURE_GPIO_SIZE;
            } else 
						{
                feature_get_buf[0] = FEATURE_GPIO;
                *(uint16_t *)(feature_get_buf+1) = global_gpio.command_id;
                feature_get_buf[3] = global_gpio.direction;
                //feature_get_buf[4] = global_gpio.value = gpio_get_value();
                return feature_get_buf;
            }
            break;

        case FEATURE_KEEP_ALIVE:
            if (!length) 
						{
                pInformation->Ctrl_Info.Usb_wLength = FEATURE_KEEP_ALIVE_SIZE;
            } else 
						{
                feature_get_buf[0] = FEATURE_KEEP_ALIVE;
                *(uint16_t *)(feature_get_buf+1) = global_keep_alive.command_id;
                *(uint16_t *)(feature_get_buf+3) = global_keep_alive.keep_alive;
                return feature_get_buf;
            }
            break;
	    /*获取显示设备的信息*/
        case FEATURE_DISPLAY_INFO:
            if (!length) {
                pInformation->Ctrl_Info.Usb_wLength = FEATURE_DISPLAY_INFO_SIZE;
            } else {
                feature_get_buf[0] = FEATURE_DISPLAY_INFO;
                *(uint16_t *)(feature_get_buf+1) = global_display_info.command_id;
                // fill the actual parameters
                return feature_get_buf;
            }
            break;
		/*获取设备的序列号信息*/
        case FEATURE_SERIAL:		 /*Oculus Utility请求Sensor Serial信息*/
            if (!length) {
                pInformation->Ctrl_Info.Usb_wLength = FEATURE_SERIAL_SIZE;
            } else {
                feature_get_buf[0] = FEATURE_SERIAL;
                *(uint16_t *)(feature_get_buf+1) = global_serial.command_id;
                //Get_SerialNum((char *)(feature_get_buf+3), 0);	 /*读取Sensor Serial*/ 
							GetChipId((uint8_t *)(feature_get_buf+3));
                return feature_get_buf;
            }
            break;
        case FEATURE_OFFSET:		 //OFFSET
            if (!length) {
                pInformation->Ctrl_Info.Usb_wLength = FEATURE_OFFSET_SIZE;
            } else {
                feature_get_buf[0] = FEATURE_OFFSET;
                *(uint16_t *)(feature_get_buf+1) = global_offset.command_id;
							//global_offset.dev=*(uint8_t*)(feature_get_buf+3);
							feature_get_buf[3] = global_offset.dev;
							switch (global_offset.dev)
							{
								case FEATURE_OFFSET_GET_GYRO: 
									Get_Gyro_Offset((float*)(feature_get_buf+4));
									break;
								case FEATURE_OFFSET_GET_ACC: 
									Get_Acc_Offset((float*)(feature_get_buf+4));
									break;
								case FEATURE_OFFSET_GET_MAG:
									Get_Mag_Offset((float*)(feature_get_buf+4));
									break;								
							}	
              return feature_get_buf;
            }
            break;
        default:
            break;
    }
    return NULL;
}

uint8_t *feature_config_setreport(uint16_t length)
{
    // Switch based on ReportID
    switch (pInformation->USBwValue0) 
	{
        case FEATURE_CONFIG:
            // On the first callback, we supply the length
            if (!length) 
			{
                pInformation->Ctrl_Info.Usb_wLength = FEATURE_CONFIG_SIZE;
            } else 
			{
                // On the second, we return the buffer to fill
                return feature_set_buf;
            }
            break;

        case FEATURE_CALIBRATE:
            if (!length) 
			{
                pInformation->Ctrl_Info.Usb_wLength = FEATURE_CALIBRATE_SIZE;
            } else {
                // Calibrate is above 64 bytes, so we get called again with offset
                return feature_set_buf + pInformation->Ctrl_Info.Usb_wOffset;
            }
            break;

        case FEATURE_RANGE:
            if (!length) 
			{
                pInformation->Ctrl_Info.Usb_wLength = FEATURE_RANGE_SIZE;
            } else {
                return feature_set_buf;
            }
            break;

        case FEATURE_REGISTER:
            if (!length) {
                pInformation->Ctrl_Info.Usb_wLength = FEATURE_REGISTER_SIZE;
            } else {
                return feature_set_buf;
            }
            break;

        case FEATURE_DFU:
            if (!length) {
                pInformation->Ctrl_Info.Usb_wLength = FEATURE_DFU_SIZE;
            } else {
                return feature_set_buf;
            }
            break;

        case FEATURE_GPIO:
            if (!length) {
                pInformation->Ctrl_Info.Usb_wLength = FEATURE_GPIO_SIZE;
            } else {
                return feature_set_buf;
            }
            break;

        case FEATURE_KEEP_ALIVE:
            if (!length) {
                pInformation->Ctrl_Info.Usb_wLength = FEATURE_KEEP_ALIVE_SIZE;
            } else {
                return feature_set_buf;
            }
            break;

        case FEATURE_DISPLAY_INFO:
            if (!length) {
                pInformation->Ctrl_Info.Usb_wLength = FEATURE_DISPLAY_INFO_SIZE;
            } else {
                return feature_set_buf;
            }
            break;

        case FEATURE_SERIAL:
            if (!length) {
                pInformation->Ctrl_Info.Usb_wLength = FEATURE_SERIAL_SIZE;
            } else {
                return feature_set_buf;
            }
            break;
        case FEATURE_OFFSET:
            if (!length) {
                pInformation->Ctrl_Info.Usb_wLength = FEATURE_OFFSET_SIZE;
            } else {
                return feature_set_buf;
            }
            break;
        default:
            break;
    }

    return NULL;
}
/*命令下位机完成某些事情*/
void feature_config_parse_report(void)
{
    // Get the latest set command ID regardless of report type
    unsigned short int DFU_State = 0x1111;
	  unsigned short int DFU_State_Read = 0xffff;
    feature_config_command_id = *(uint16_t *)(feature_set_buf+1);
    got_command = 1;

    switch (feature_set_buf[0]) 
		{
        case FEATURE_CONFIG:
            global_config.command_id = *(uint16_t *)(feature_set_buf+1);
            global_config.use_raw = feature_set_buf[3] & 1;
            global_config.calibrate = feature_set_buf[3] & (1 << 1);
            global_config.use_calibration = feature_set_buf[3] & (1 << 2);
            global_config.autocalibration = feature_set_buf[3] & (1 << 3);
            global_config.motion_keep_alive = feature_set_buf[3] & (1 << 4);
            global_config.command_keep_alive = feature_set_buf[3] & (1 << 5);
            global_config.use_ovr_coordinates = feature_set_buf[3] & (1 << 6);
            global_config.interval = feature_set_buf[4];

			/* 采样时间现在强制为1000Hz	 Sample rate is forced to 1000 for now	*/
            global_config.sample_rate = 1000; // *(uint16_t *)(feature_set_buf+5);
            global_config_set = 1;
            break;

        case FEATURE_CALIBRATE:
            // update the last command in on any feature report
            global_calibrate.command_id = *(uint16_t *)(feature_set_buf+1);
            // pass the payload of calibration data
            memcpy(global_calibrate.payload, feature_set_buf+FEATURE_HEADER_SIZE, CALIBRATION_SIZE);
            global_calibrate_set = 1;
            break;

        case FEATURE_RANGE:			   /*从这里上位机设置下位机的传感器范围*/
            global_range.command_id  =   *(uint16_t *)(feature_set_buf+1);
            global_range.accel_range =   4;
            global_range.gyro_range  =   500;
            global_range.mag_range 	 =   1300;
            global_range_set = 1;
            break;

        case FEATURE_REGISTER:			/*直接修改下位机传感器的寄存器，目前Laputa 不支持*/
            global_reg.command_id = *(uint16_t *)(feature_set_buf+1);
            global_reg.device = feature_set_buf[3];
            global_reg.reg = feature_set_buf[4];
            global_reg.payload = feature_set_buf[5];
            global_reg_set = 1;
            break;

        case FEATURE_DFU:				/*这是Oculus 在线升级的一个功能*/
            global_dfu.command_id = *(uint16_t *)(feature_set_buf+1);
            global_dfu.use_dfu = (feature_set_buf[3] == 1);
            global_dfu_set = 1;
            break;
		/*这个地方，上位机可以设置下位机的GPIO特性，以后Laputa 可以用上位机设置下位机的
		  各种功能*/
        case FEATURE_GPIO:						
            global_gpio.command_id = *(uint16_t *)(feature_set_buf+1);
            global_gpio.direction = feature_set_buf[3];
            //gpio_set_direction(global_gpio.direction);   /*屏蔽了和GPIO相关的功能，除了Oculus无法控制*/
           // gpio_set_value(feature_set_buf[4]);
            break;
		// 我们用通信协议中的KeepAlive用作为我们的自己的通信部分
        case FEATURE_KEEP_ALIVE:                        
			DM_USB_Command  =  feature_set_buf[4];
			if(DM_USB_Command == 0x26)
			{
				TIM_ITConfig(TIM3,TIM_IT_Update,DISABLE);
				Compute_Gyro_Offset();
				TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);
			}
			if(DM_USB_Command == 0x25)
			{
				 /*在指定地址写入标志位,用于判断是否进入DFU模?
				  *在收到DFU命令后，这里向指定地址写入0x1111，设置DFU的标志位，
				  *开机的时候，DFU程序检测到0x1111,就停留在DFU模式，这里注意，不论是否在何种模式下，检测到0x1111后
				   需要立即擦出该标志位
				  */ 
				 STMFLASH_Write(FLASH_DFU_FLASH,&DFU_State,1);  //2个字节 = 半个字
				 STMFLASH_Read(FLASH_DFU_FLASH,&DFU_State_Read,1);  //2个字节 = 半个字
				 if(DFU_State_Read == 0x1111)NVIC_SystemReset();
			}
            break;

        case FEATURE_DISPLAY_INFO:
            global_display_info.command_id = *(uint16_t *)(feature_set_buf+1);
			/*把显示信息存到EEROM中，目前Laputa 不支持该功能*/
            break;

        case FEATURE_SERIAL:
            global_serial.command_id = *(uint16_t *)(feature_set_buf+1);
            Set_Stored_Serial((char *)feature_set_buf+3);	 /*把SerialNum 存到EEROM中，目前是不支持的*/
            break;
		
		case FEATURE_OFFSET:
			global_offset.command_id=*(uint16_t *)(feature_set_buf+1);
			global_offset.dev=*(uint8_t *)(feature_set_buf+3);
	
			switch(global_offset.dev)
			{	
				case FEATURE_OFFSET_SET_GYRO: 
					Save_Gyro_Offset((float*)(feature_set_buf+4));
					//Load_Gyro_Offset();
					break;
				case FEATURE_OFFSET_SET_ACC: 
					//Save_Acc_Offset((float*)(feature_set_buf+4));
					//Load_Acc_Offset();
					break;
				case FEATURE_OFFSET_SET_MAG:
					Save_Mag_Offset((float*)(feature_set_buf+4));
					Load_Mag_Offset();
					break;
				case FEATURE_OFFSET_SET_LED:
					//global_LED_color=(enum LED_COLOR)feature_set_buf[4];
					break;
					//case FEATURE_OFFSET_GET_GYRO :  
					//case FEATURE_OFFSET_GET_ACC	:   							
					//case FEATURE_OFFSET_GET_MAG  :   
					//global_offset.dev=global_offset.dev&0x0F;
					//break;
			}
			break;
        default:
            break;
    }
}

bool feature_config_got_command(bool peek)
{
    bool ret = got_command;

    if (!peek)
        got_command = 0;

    return ret;
}

uint16_t feature_config_latest_command_id(void)
{
    return feature_config_command_id;
}

void feature_config_set(feature_config_p config)
{
    memcpy(&global_config, config, sizeof(feature_config_s));
}

void feature_keep_alive_set(feature_keep_alive_p keep_alive)
{
    memcpy(&global_keep_alive, keep_alive, sizeof(feature_keep_alive_s));
}

bool feature_config_get(feature_config_p config)
{
    // TODO: protect this
    // Only mark as changed if we got a new packet and the contents differ from the last
    if (global_config_set && memcmp(config, &global_config, sizeof(feature_config_s))) {
        global_config_set = 0;
        memcpy(config, &global_config, sizeof(feature_config_s));
        return 1;
    }

    return 0;
}

bool feature_calibrate_get(feature_calibrate_p calibrate)
{
    // TODO: protect this
    if (global_calibrate_set &&  memcmp(calibrate, &global_calibrate, sizeof(feature_calibrate_s))) {
        global_calibrate_set = 0;
        memcpy(calibrate, &global_calibrate, sizeof(feature_calibrate_s));
        return 1;
    }

    return 0;
}

bool feature_range_get(feature_range_p range)
{
    // TODO: protect this
    if (global_range_set && memcmp(range, &global_range, sizeof(feature_range_s))) {
        global_range_set = 0;
        memcpy(range, &global_range, sizeof(feature_range_s));
        return 1;
    }

    return 0;
}

bool feature_register_get(feature_register_p reg)
{
    // TODO: protect this
    // A register could be set twice intentionally here, so don't condition on
    // the contents differing
    if (global_reg_set) {
        global_reg_set = 0;
        memcpy(reg, &global_reg, sizeof(feature_register_s));
        return 1;
    }

    return 0;
}

bool feature_dfu_get(feature_dfu_p dfu)
{
    // TODO: protect this
    if (global_dfu_set && memcmp(dfu, &global_dfu, sizeof(feature_dfu_s))) 
		{
        global_dfu_set = 0;
        memcpy(dfu, &global_dfu, sizeof(feature_dfu_s));
        return 1;
    }
    return 0;
}

bool feature_keep_alive_get(feature_keep_alive_p keep_alive)
{
    // TODO: protect this
    // This report is lightweight, so just let it through if it is the same
    if (global_keep_alive_set) 
		{
        global_keep_alive_set = 0;
        memcpy(keep_alive, &global_keep_alive, sizeof(feature_keep_alive_s));
        return 1;
    }
    return 0;
}


void GetChipId(uint8_t *temp)
{ 
    u32 temp0,temp1,temp2;
    temp0=*(__IO u32*)(0x1FFFF7E8);    
    temp1=*(__IO u32*)(0x1FFFF7EC);
    temp2=*(__IO u32*)(0x1FFFF7F0);
    temp[0] = (u8)(temp0 & 0x000000FF);
    temp[1] = (u8)((temp0 & 0x0000FF00)>>8);
    temp[2] = (u8)((temp0 & 0x00FF0000)>>16);
    temp[3] = (u8)((temp0 & 0xFF000000)>>24);
    temp[4] = (u8)(temp1 & 0x000000FF);
    temp[5] = (u8)((temp1 & 0x0000FF00)>>8);
    temp[6] = (u8)((temp1 & 0x00FF0000)>>16);
    temp[7] = (u8)((temp1 & 0xFF000000)>>24);
    temp[8] = (u8)(temp2 & 0x000000FF);
    temp[9] = (u8)((temp2 & 0x0000FF00)>>8);
    temp[10] = (u8)((temp2 & 0x00FF0000)>>16);
    temp[11] = (u8)((temp2 & 0xFF000000)>>24);
}
