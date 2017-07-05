/*******************************************************************************
  * @file                   protocol.h
  * @Author:                MQjehovah                 mail:MQjehovah@hotmail.com
  * @version                1.0.0
  * @date                   2017.5.25
  * @brief                  
  ******************************************************************************
  * @attention 
*******************************************************************************/
#ifndef  _PROTOCOL_H
#define  _PROTOCOL_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_conf.h"
#include "pid.h"
/* Definition ----------------------------------------------------------------*/
typedef enum  
{ 
	IDLE,
	HEADREADY,
	RECING
}RecState;

extern u8 sendData[];
/* Exported Functions --------------------------------------------------------*/
void Parser(u8 data);
void Process(u8 data[]);
void SetData(int num);
void DataUpload(void);

void short2Byte(short num,u8 bytes[], int offset);
short Byte2Short(u8 bytes[], int offset);
short Byte2float(u8 bytes[], int offset);
#endif
/*********************************END OF FILE**********************************/
