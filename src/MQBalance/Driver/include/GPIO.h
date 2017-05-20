/*******************************************************************************
  * @file                   GPIO.h
  * @Author:                MQjehovah                 mail:MQjehovah@hotmail.com
  * @version                1.0.1
  * @date                   2017.5.16
  * @brief                  
  ******************************************************************************
  * @attention
*******************************************************************************/
#ifndef  _GPIO_H
#define  _GPIO_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_conf.h"
/* Definition ----------------------------------------------------------------*/
typedef enum
{
	LOW,
	HIGH,
}GPIO_STA;


typedef struct
{
	GPIO_TypeDef * PORT;
	uint16_t PIN;
}GPIO_DEV;

extern GPIO_DEV PA0;//PA0-WKUP/USART2_CTS/ADC_IN0/TIM2_CH1_ETR
extern GPIO_DEV PA1;//PA1/USART2_RTS/ADC_IN1/TIM2_CH2
extern GPIO_DEV PA2;//PA2/USART2_TX/ADC_IN2/TIM2_CH3
extern GPIO_DEV PA3;//PA3/USART2_RX/ADC_IN3/TIM2_CH4
extern GPIO_DEV PA4;//PA4/SPI1_NSS/USART2_CK/ADC_IN4
extern GPIO_DEV PA5;//PA5/SPI1_SCK/ADC_IN5 
extern GPIO_DEV PA6;//PA6/SPI1_MISO/ADC_IN6/TIM3_CH1
extern GPIO_DEV PA7;//PA7/SPI1_MOSI/ADC_IN7/TIM3_CH2
extern GPIO_DEV PA8;//PA8/USART1_CK/TIM1_CH1/MCO
extern GPIO_DEV PA9;//PA9/USART1_TX/TIM1_CH2
extern GPIO_DEV PA10;//PA10/USART1_RX/TIM1_CH3
extern GPIO_DEV PA11;//PA11/USART1_CTS/CANRX/USBDM/TIM1_CH4
extern GPIO_DEV PA12;//PA12/USART1_RTS/CANTX/USBDP/TIM1_ETR
extern GPIO_DEV PA13;//PA13/JTMS/SWDIO
extern GPIO_DEV PA14;//PA14/JTCK/SWCLK
extern GPIO_DEV PA15;//PA15/JTDI

extern GPIO_DEV PB0;//PB0/ADC_IN8/TIM3_CH3
extern GPIO_DEV PB1;//PB1/ADC_IN9/TIM3_CH4  
extern GPIO_DEV PB2;//PB2/BOOT1 
extern GPIO_DEV PB3;//PB3/JTDO/TRACESWO
extern GPIO_DEV PB4;//PB4/JNTRST
extern GPIO_DEV PB5;//PB5/I2C1_SMBAl  
extern GPIO_DEV PB6;//PB6/I2C1_SCL/ TIM4_CH1
extern GPIO_DEV PB7;//PB7/I2C1_SDA/ TIM4_CH2
extern GPIO_DEV PB8;//PB8/TIM4_CH3 
extern GPIO_DEV PB9;//PB9/TIM4_CH4 
extern GPIO_DEV PB10;//PB10/I2C2_SCL/USART3_TX
extern GPIO_DEV PB11;//PB11/I2C2_SDA/USART3_RX
extern GPIO_DEV PB12;//PB12/SPI2_NSS/I2C2_SMBAl/USART3_CK/TIM1_BKIN
extern GPIO_DEV PB13;//PB13/SPI2_SCK/USART3_CTS/TIM1_CH1N
extern GPIO_DEV PB14;//PB14/SPI2_MISO/USART3_RTS/TIM1_CH2N
extern GPIO_DEV PB15;//PB15/SPI2_MOSITIM1_CH3N

extern GPIO_DEV PC13;//
extern GPIO_DEV PC14;//
/* Exported Functions --------------------------------------------------------*/
void GPIO_Config(GPIO_DEV *dev,GPIOMode_TypeDef mode);
void GPIO_WritePin(GPIO_DEV *dev,GPIO_STA state);
GPIO_STA GPIO_ReadPin(GPIO_DEV *dev);
#endif
/*********************************END OF FILE**********************************/
