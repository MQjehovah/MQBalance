/*******************************************************************************
  * @file                   TIMER.h
  * @Author:                MQjehovah                 mail:MQjehovah@hotmail.com
  * @version                1.0.0
  * @date                   2017.5.9
  * @brief                  
  ******************************************************************************
  * @attention
*******************************************************************************/
#ifndef _TIMER_H
#define _TIMER_H
/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_conf.h"
#include "GPIO.h"
#include "USART.h"

#include "stdio.h"
/* Definition ----------------------------------------------------------------*/
typedef enum
{
	TIM_MODE_PWM,
	TIM_MODE_CAP
}CHANNEL_MODE;
typedef enum
{
	TIM_CH1,
	TIM_CH2,
	TIM_CH3,
	TIM_CH4,
}CHANNEL_ID;

typedef struct
{
	CHANNEL_MODE   mode;
	GPIO_DEV *     gpio;
	TIM_TypeDef *  timer;
	CHANNEL_ID     id;
}TIM_CHANNEL;

typedef struct
{
	TIM_TypeDef * timer;
	TIM_CHANNEL *channel1;
	TIM_CHANNEL *channel2;
	TIM_CHANNEL *channel3;
	TIM_CHANNEL *channel4;
}TIM_DEV;

typedef struct
{
	TIM_TypeDef * timer;
	u8 timer_channel;
}PWM_DEV;

#define TIM2_CH1_GPIO   PA0
#define TIM2_CH2_GPIO   PA1
#define TIM2_CH3_GPIO   PA2
#define TIM2_CH4_GPIO   PA3

#define TIM3_CH1_GPIO   PA6
#define TIM3_CH2_GPIO   PA7
#define TIM3_CH3_GPIO   PB0
#define TIM3_CH4_GPIO   PB1

#define TIM4_CH1_GPIO   PB6
#define TIM4_CH2_GPIO   PB7
#define TIM4_CH3_GPIO   PB8
#define TIM4_CH4_GPIO   PB9


//extern float speed;
/* Exported Functions --------------------------------------------------------*/
void TIM_init(TIM_DEV dev, u16 freq);
void TIM_Config(TIM_DEV dev);
void PWM_Config(TIM_TypeDef * TIMx, u16 CCR1,u16 CCR2,u16 CCR3,u16 CCR4);
void PWM_SetDuty(TIM_CHANNEL channel, u16 duty);
/*********************************END OF FILE**********************************/
#endif
