/*******************************************************************************
  * @file                   ENCODE.h
  * @Author:                MQjehovah                 mail:MQjehovah@hotmail.com
  * @version                1.0.0
  * @date                   2017.5.26
  * @brief                  
  ******************************************************************************
  * @attention
*******************************************************************************/
#ifndef _ENCODE_H
#define _ENCODE_H
/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_conf.h"
#include "GPIO.h"
/* Definition ----------------------------------------------------------------*/
#define ENCODE_LINEA_GPIO			PA0
#define ENCODE_LINEB_GPIO			PA1

#define  ENCODE_LINEB_READ			GPIO_ReadPin(&ENCODE_LINEB_GPIO)


extern s16 Encoder;
/* Exported Functions --------------------------------------------------------*/
void ENCODE_TIM_Init(void);
void ENCODE_EXTI_Init(void);
s16 ENCODE_TIM_Read(void);
s16 ENCODE_EXTI_Read(void);
/*********************************END OF FILE**********************************/
#endif
