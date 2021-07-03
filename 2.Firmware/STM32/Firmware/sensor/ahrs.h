#ifndef _AHRS_H_
#define _AHRS_H_

float invSqrt(float x); 

void AHRSupdate(float gx, float gy, float gz, float ax, float ay, float az, float mx, float my, float mz, char useMag,char UseTimer);

#endif
