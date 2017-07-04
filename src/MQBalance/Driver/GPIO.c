/*******************************************************************************
  * @file                   GPIO.c
  * @Author:                MQjehovah                 mail:MQjehovah@hotmail.com
  * @version                1.0.1
  * @date                   2017.5.16
  * @brief                  
  ******************************************************************************
  * @attention
*******************************************************************************/
/* Includes ------------------------------------------------------------------*/
#include "GPIO.h"
/* Definition ----------------------------------------------------------------*/
GPIO_DEV PA0 = {GPIOA,GPIO_Pin_0};
GPIO_DEV PA1 = {GPIOA,GPIO_Pin_1};
GPIO_DEV PA2 = {GPIOA,GPIO_Pin_2};
GPIO_DEV PA3 = {GPIOA,GPIO_Pin_3};
GPIO_DEV PA4 = {GPIOA,GPIO_Pin_4};
GPIO_DEV PA5 = {GPIOA,GPIO_Pin_5};
GPIO_DEV PA6 = {GPIOA,GPIO_Pin_6};
GPIO_DEV PA7 = {GPIOA,GPIO_Pin_7};
GPIO_DEV PA8 = {GPIOA,GPIO_Pin_8};
GPIO_DEV PA9 = {GPIOA,GPIO_Pin_9};
GPIO_DEV PA10 = {GPIOA,GPIO_Pin_10};
GPIO_DEV PA11 = {GPIOA,GPIO_Pin_11};
GPIO_DEV PA12 = {GPIOA,GPIO_Pin_12};
GPIO_DEV PA13 = {GPIOA,GPIO_Pin_13};
GPIO_DEV PA14 = {GPIOA,GPIO_Pin_14};
GPIO_DEV PA15 = {GPIOA,GPIO_Pin_15};


GPIO_DEV PB0 = {GPIOB,GPIO_Pin_0};
GPIO_DEV PB1 = {GPIOB,GPIO_Pin_1};
GPIO_DEV PB2 = {GPIOB,GPIO_Pin_2};
GPIO_DEV PB3 = {GPIOB,GPIO_Pin_3};
GPIO_DEV PB4 = {GPIOB,GPIO_Pin_4};
GPIO_DEV PB5 = {GPIOB,GPIO_Pin_5};
GPIO_DEV PB6 = {GPIOB,GPIO_Pin_6};
GPIO_DEV PB7 = {GPIOB,GPIO_Pin_7};
GPIO_DEV PB8 = {GPIOB,GPIO_Pin_8};
GPIO_DEV PB9 = {GPIOB,GPIO_Pin_9};
GPIO_DEV PB10 = {GPIOB,GPIO_Pin_10};
GPIO_DEV PB11 = {GPIOB,GPIO_Pin_11};
GPIO_DEV PB12 = {GPIOB,GPIO_Pin_12};
GPIO_DEV PB13 = {GPIOB,GPIO_Pin_13};
GPIO_DEV PB14 = {GPIOB,GPIO_Pin_14};
GPIO_DEV PB15 = {GPIOB,GPIO_Pin_15};

GPIO_DEV PC13 = {GPIOC,GPIO_Pin_13};
GPIO_DEV PC14 = {GPIOC,GPIO_Pin_14};

GPIO_DEV PD13 = {GPIOD,GPIO_Pin_13};

//GPIO_DEV PIN_MAP[10];

/* Functions -----------------------------------------------------------------*/
/*******************************************************************************
  * @brief  GPIO端口配置       
  * @param  None              
  * @retval None              
  * @Note   None              
*******************************************************************************/
void GPIO_Config(GPIO_DEV *dev,GPIOMode_TypeDef mode)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	GPIO_InitStructure.GPIO_Pin = dev->PIN ;
	GPIO_InitStructure.GPIO_Mode = mode;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(dev->PORT,&GPIO_InitStructure);
}

/*******************************************************************************
  * @brief  GPIO端口电平设置       
  * @param  None              
  * @retval None              
  * @Note   None              
*******************************************************************************/
void GPIO_WritePin(GPIO_DEV *dev,GPIO_STA state)
{
	if(state == HIGH)
		GPIO_SetBits(dev->PORT,dev->PIN);
	else
		GPIO_ResetBits(dev->PORT,dev->PIN);
}

/*******************************************************************************
  * @brief  读取GPIO端口电平      
  * @param  None              
  * @retval None              
  * @Note   None              
*******************************************************************************/
GPIO_STA GPIO_ReadPin(GPIO_DEV *dev)
{
	if(GPIO_ReadInputDataBit(dev->PORT,dev->PIN))//读取单个输入端口的数据
		return HIGH;
	else
		return LOW;
}
/*********************************END OF FILE**********************************/
