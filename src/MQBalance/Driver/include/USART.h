/*******************************************************************************
  * @file                   USART.h
  * @Author:                MQjehovah                 mail:MQjehovah@hotmail.com
  * @version                1.0.0
  * @date                   2016.3.18
  * @brief                  
  ******************************************************************************
  * @attention
*******************************************************************************/
#ifndef _USART_DRIVER_H
#define _USART_DRIVER_H
/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_conf.h"
#include "GPIO.h"
 #include<string.h> 
 #include<stdio.h> 
/* Definition ----------------------------------------------------------------*/

/* Exported Functions --------------------------------------------------------*/
void USART_GPIO_Config(USART_TypeDef *USARTx);
void USART_Config(USART_TypeDef *USARTx,u16 Buand);
void USART_485_Config(USART_TypeDef *USARTx,u16 Buand,GPIO_DEV *ENPIN);
void USART_SendChar(USART_TypeDef *USARTx,char Data);
void USART_485_SendChar(USART_TypeDef *USARTx,char Data);
void USART_SendStr(USART_TypeDef *USARTx,char* senddata);
void USART_485_SendStr(USART_TypeDef *USARTx,char* senddata);
/*********************************END OF FILE**********************************/
#endif
