#ifndef __STMFLASH_H__
#define __STMFLASH_H__
#include "sys.h"  

//�û������Լ�����Ҫ����
#define STM32_FLASH_SIZE 64 	 		      //��ѡSTM32��FLASH������С(��λΪK)
#define STM32_FLASH_WREN 1              //ʹ��FLASHд��(0��������;1��ʹ��)

/*STM32 FLASH����ʼ��ַ*/
#define STM32_FLASH_BASE 0x08000000 	  

/*Laputa�洢��������ƫ�ĵ�ַ*/
#define FLASH_SAVE_ADDR  0X0800FF00 		   
 
/****************************************STM32 EEPROM��д�⺯��****************************************/
u16  STMFLASH_ReadHalfWord(u32 faddr);		                            //��������  
void STMFLASH_WriteLenByte(u32 WriteAddr,u32 DataToWrite,u16 Len);	//ָ����ַ��ʼд��ָ�����ȵ�����
u32  STMFLASH_ReadLenByte(u32 ReadAddr,u16 Len);						          //ָ����ַ��ʼ��ȡָ����������
void STMFLASH_Write(u32 WriteAddr,u16 *pBuffer,u16 NumToWrite);		  //��ָ����ַ��ʼд��ָ�����ȵ�����
void STMFLASH_Read(u32 ReadAddr,u16 *pBuffer,u16 NumToRead);   		  //��ָ����ַ��ʼ����ָ�����ȵ�����



#endif
















