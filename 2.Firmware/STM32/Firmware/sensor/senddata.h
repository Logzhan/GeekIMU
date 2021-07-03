/******************** (C) COPYRIGHT 2020 GEEKIMU *******************************
* File Name          : senddata.h
* Current Version    : V2.0  & ST 3.5.0
* Author             : zhanli 719901725@qq.com & JustFeng.
* Date of Issued     : 2015.2.22 zhanli : Create
* Comments           : IMU数据打包和发送头文件   
********************************************************************************/
#ifndef _SENDDATA__H_
#define _SENDDATA__H_
#include <stdint.h>

#define DATA_PACKET_SIZE             62
#define SAMPLE_SIZE                  16
#define SAMPLE_START                 8

/**----------------------------------------------------------------------
* Function    : Data_Packet_Sensor
* Description : 按照Oculus手册所要求的发包格式对IMU数据进行打包
* Author      : zhanli&719901725@qq.com
* Date        : 2015/2/13 zhanli
*---------------------------------------------------------------------**/
void Data_Packet_Sensor(uint8_t *buf, int32_t x, int32_t y, int32_t z);

/**----------------------------------------------------------------------
* Function    : Data_Unpack_Sensor
* Description : 按照Oculus手册所要求的发包格式对IMU数据进行解包
* Author      : zhanli&719901725@qq.com
* Date        : 2015/2/13 zhanli
*---------------------------------------------------------------------**/
void Data_Unpack_Sensor(const uint8_t *buf, int32_t *x, int32_t *y, int32_t *z);

/**----------------------------------------------------------------------
* Function    : SensorData_Packet
* Description : 九轴传感器数据打包
* Author      : zhanli&719901725@qq.com
* Date        : 2015/2/13 zhanli
*---------------------------------------------------------------------**/
void SensorData_Packet(float ax,float ay,float az,float gx,float gy,float gz, 
		float mx,float my,float mz,float temp,float timestamp);

/**----------------------------------------------------------------------
* Function    : Get_Sensor_Data
* Description : 获取加速度、角速度、磁力计数据
* Author      : zhanli&719901725@qq.com
* Date        : 2015/2/13 zhanli
*---------------------------------------------------------------------**/
void Get_Sensor_Data(void);

#endif
