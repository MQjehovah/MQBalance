/*******************************************************************************
  * @file                   delay.h
  * @Author:                MQjehovah                 mail:MQjehovah@hotmail.com
  * @version                1.0.01
  * @date                   2017.5.15
  * @brief                  
  ******************************************************************************
  * @attention
*******************************************************************************/
#ifndef __DELAY_H
#define __DELAY_H 	
/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_conf.h"
/* Definition ----------------------------------------------------------------*/

/* Exported Functions --------------------------------------------------------*/
void simple_delay_us(u16 us);
void simple_delay_ms(u16 ms);
void SysTick_init(void);
void delay_ms(u32 nTime);
void SysTick_BindHandle(void (*pCB)(void));
void SysTick_ClearBind(void);
#endif
/*********************************END OF FILE**********************************/
