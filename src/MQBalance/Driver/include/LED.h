/*******************************************************************************
  * @file                   LED.h
  * @Author:                MQjehovah                 mail:MQjehovah@hotmail.com
  * @version                1.0.2
  * @date                   2016.3.17
  * @brief                  
  ******************************************************************************
  * @attention
*******************************************************************************/
#ifndef  _LED_H
#define  _LED_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_conf.h"
#include "delay.h"
#include "GPIO.h"
/* Definition ----------------------------------------------------------------*/
#define LED_NUM        2

#define LED1_GPIO     PC13
#define LED2_GPIO     PA12
typedef enum 
{
	OFF,
	ON,
}LED_STA;

typedef struct
{
	GPIO_DEV *gpio;
	u8 state;
}LED_DEV;



/* Exported Functions --------------------------------------------------------*/
void LED_init(void);
void LED_GPIO_Config(void);
void LED_ON(u8 id);
void LED_OFF(u8 id);
void LED_Flash(u8 id,u16 time,u8 count);
void LED_SetState(u8 id, LED_STA state);
LED_STA LED_GetState(u8 id);
#endif
/*********************************END OF FILE**********************************/
