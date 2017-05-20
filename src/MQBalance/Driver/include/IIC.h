/*******************************************************************************
  * @file                   IIC.h
  * @Author:                MQjehovah                 mail:MQjehovah@hotmail.com
  * @version                1.0.3
  * @date                   2017.4.14
  * @brief                  
  ******************************************************************************
  * @attention
*******************************************************************************/
#ifndef  _IIC_H
#define  _IIC_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_conf.h"
#include "GPIO.h"
#include "delay.h"
/* Definition ----------------------------------------------------------------*/
#define  I2C_Direction_Transmitter      ((uint8_t)0x00)	//写
#define  I2C_Direction_Receiver         ((uint8_t)0x01)	//读

#define IIC_SCL_GPIO    PB0
#define IIC_SDA_GPIO    PB1


//IO操作函数	 
#define IIC_SCL_H       GPIO_WritePin(&IIC_SCL_GPIO,HIGH)	           //GPIOA->BSRR = SCCB_SIC_BIT;  对端口A特定位的设置	,这里设置高
#define IIC_SCL_L       GPIO_WritePin(&IIC_SCL_GPIO,LOW)              //GPIOA->BRR =  SCCB_SIC_BIT;  这里设置低

#define IIC_SDA_H       GPIO_WritePin(&IIC_SDA_GPIO,HIGH)   	         //GPIOA->BSRR = SCCB_SID_BIT;  
#define IIC_SDA_L       GPIO_WritePin(&IIC_SDA_GPIO,LOW)              //GPIOA->BRR =  SCCB_SID_BIT;

#define IIC_SDA_READ    GPIO_ReadPin(&IIC_SDA_GPIO)                   //GPIOB->IDR&0x04 输入SDA  GPIOB->IDR&0x40    

// 对于STM32平台可用下列宏定义完成SDA的输入与输出配置
// 其他平台请自行实现IIC_SDA_GPIO_INPUT和IIC_SDA_GPIO_OUTPUT两个函数
// 寄存器设置SDA引脚输入输出模式
//#define IIC_SDA_IN  {GPIOA->CRL&=0XFF0FFFFF;GPIOA->CRL|=0X00800000;}
//#define IIC_SDA_OUT {GPIOA->CRL&=0XFF0FFFFF;GPIOA->CRL|=0X00300000;}
#define IIC_SDA_IN      IIC_SDA_GPIO_INPUT()
#define IIC_SDA_OUT     IIC_SDA_GPIO_OUTPUT()
// IIC通信中延时
#define IIC_PAUSE       4
/* Exported Functions --------------------------------------------------------*/
void IIC_Init(void);        //初始化IIC的IO口	
void IIC_Start(void);
void IIC_Stop(void);
u8 IIC_Wait_Ack(void);
void IIC_Ack(void);
void IIC_NAck(void);
u8 IIC_Read_Byte(void);
void IIC_Send_Byte(u8 txd);
u8 IIC_ReadOneByte(u8 addr, u8 reg, u8* data);
u8 IIC_WriteOneByte(u8 addr, u8 reg, u8 data);
u8 IIC_Read_Buffer(u8 addr, u8 reg, u8 len, u8* buf);
u8 IIC_Write_Buffer(u8 addr, u8 reg, u8 len, u8* data);
u16 IIC_GetErrorCounter(void);
void IIC_SDA_GPIO_OUTPUT(void);
void IIC_SDA_GPIO_INPUT(void);
#endif
/*********************************END OF FILE**********************************/
