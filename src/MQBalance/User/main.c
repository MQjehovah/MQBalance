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
#include "stdio.h"
#include "LED.h"
#include "MPU6050.h"
#include "MOTOR.h"
#include "protocol.h"
/* Definition ----------------------------------------------------------------*/
/* Functions -----------------------------------------------------------------*/
/*******************************************************************************
  * @brief  时钟配置            
  * @param  None 
  * @retval None              
  * @Note   None              
*******************************************************************************/
void RCC_Config()
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOD, ENABLE);
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

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);    
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;    
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;    
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;    
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;    
	NVIC_Init(&NVIC_InitStructure);   

//	NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;				//使能按键所在的外部中断通道
// 	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//抢占优先级2， 
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;			//子优先级1
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;					//使能外部中断通道
//	NVIC_Init(&NVIC_InitStructure); 	
}    

void Tick_CallBack()
{
	static u16 TickCnt;
	TickCnt++;
	if(TickCnt>1000)
	{
		TickCnt=0;
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
	SystemInit();
	RCC_Config();
	NVIC_Config();
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);//关闭jtag，保留swd。
	LED_init();
	LED_Flash(0,500,2);
	USART_Config(USART1,9600);
	USART_SendStr(USART1,"USART Init OK\n");
	MOTOR_init();
	while(!MPUInit())
	{
		USART_SendStr(USART1,"MPU6050 failed\n");
		simple_delay_ms(500);
	}
	USART_SendStr(USART1,"MPU6050 Init OK\n");
	//SysTick_init();
	//SysTick_BindHandle(Tick_CallBack);
	while(1)
	{
		simple_delay_ms(10);
//		printf("Gyro_Y:%d  ",Gyro_Y);
//		printf("angle_Accel:%f  ",angle_Accel);
//		Motor_Set_Dir(0);
//		MOTOR_L_SetPWM(4500);
//		MOTOR_R_SetPWM(4500);
		SetData((int)(angle));
		DataUpload();
		//printf("%f\r\n",angle);
	}
}
/*********************************END OF FILE**********************************/
