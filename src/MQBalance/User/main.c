/*******************************************************************************
  * @file                   main.c
  * @Author:                MQjehovah                 mail:MQjehovah@hotmail.com
  * @version                1.0.0
  * @date                   2017.5.9
  * @brief                  
  ******************************************************************************
  * @attention
*******************************************************************************/
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "math.h"
#include "stdio.h"
#include "LED.h"
#include "MPU6050.h"
/* Definition ----------------------------------------------------------------*/
/* Functions -----------------------------------------------------------------*/
short Gyro_X,Gyro_Y,Gyro_Z;
short Accel_X,Accel_Y,Accel_Z;

float angle,angle_Accel,angle_Gyro; 	
short Balance_GyroY,Balance_GyroZ;
float GetAngel()
{
	if(MPU_GetAccelX(&Accel_X) && MPU_GetAccelZ(&Accel_Z) && MPU_GetGyroY(&Gyro_Y) && MPU_GetGyroZ(&Gyro_Z))
	{
		Balance_GyroY = Gyro_Y;							//更新平衡角速度
		angle_Accel = atan2(Accel_X, Accel_Z) * 57.3f;	//计算倾角
		angle_Gyro = Gyro_Y / 7510.0f;					//陀螺仪量程转换
		angle = 0.05 * angle_Accel + 0.95 * (angle + angle_Gyro * 0.005);
		Balance_GyroZ = Gyro_Z;											//更新转向角速度
		//Acceleration_Z = Accel_Z;										//更新Z轴加速度计
	}
	return angle;													//更新平衡倾角
}
/*******************************************************************************
  * @brief  时钟配置            
  * @param  None 
  * @retval None              
  * @Note   None              
*******************************************************************************/
void RCC_Config()
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO | RCC_APB2Periph_USART1 , ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2| RCC_APB1Periph_TIM3 | RCC_APB1Periph_TIM4, ENABLE); 
}
/*******************************************************************************
  * @brief  中断优先级配置            
  * @param  None              
  * @retval None              
  * @Note   None              
*******************************************************************************/
void NVIC_Config(void)//配置中断优先级    
{    
	NVIC_InitTypeDef NVIC_InitStructure;    
//      
//  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);    
//  NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;    
//  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;    
//  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;    
//  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;    
//  NVIC_Init(&NVIC_InitStructure);   

	NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;			//使能按键所在的外部中断通道
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//抢占优先级2， 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;					//子优先级1
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
  	NVIC_Init(&NVIC_InitStructure); 	
}    

void Tick_CallBack()
{
	static u16 TickCnt;
	TickCnt++;
	if(TickCnt>50)
	{
		TickCnt=0;
		
		printf("%f\r\n",GetAngel());
		
		
	}
}
/*******************************************************************************
  * @brief  主函数             
  * @param  None              
  * @retval None              
  * @Note   None              
*******************************************************************************/
int main(void)
{
	RCC_Config();
	NVIC_Config();
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);//关闭jtag，保留swd。
	SysTick_init();
	
	LED_init();
	LED_Flash(0,500,2);
	USART_Config(USART1,9600);
	USART_SendStr(USART1,"USART Init OK\n");
	

	while(!MPUInit())
	{
		USART_SendStr(USART1,"MPU6050 failed\n");
		simple_delay_ms(500);
	}
	USART_SendStr(USART1,"MPU6050 Init OK\n");
	
	SysTick_BindHandle(Tick_CallBack);
	while(1)
	{
		simple_delay_ms(500);
		//USART_SendStr(USART1,"MQBalance test\n");
	}
}
/*********************************END OF FILE**********************************/
