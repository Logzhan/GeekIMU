# GEEKIMUv2
GEEKIMU 是一个非常精致小巧的imu模块，采用Oculus相同的陀螺仪和磁力计。其中陀螺仪采用MPU6500，而磁力计则采用LIS3MDL。传感器的数据输出采用USB-HID协议。由于MPU6500和LIS3MDL都支持磁力计，所以可以在极短的时间内完成IMU数据的采样。本项目旨在为对IMU感
兴趣的人提供一些帮助，减少重复写驱动的麻烦。

![](3.Docs\Image\1.jpg)
### 规格
陀螺仪   ：MPU6500
磁力计   ：LIS3MDL
通信方式：USB-HID
解算频率：最高1000Hz

