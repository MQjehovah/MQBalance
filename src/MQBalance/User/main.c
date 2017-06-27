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
//  NVIC_InitTypeDef NVIC_InitStructure;    
//      
//  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);    
//  NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;    
//  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;    
//  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;    
//  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;    
//  NVIC_Init(&NVIC_InitStructure);    
}    

void Tick_CallBack()
{
	static u16 TickCnt;
	TickCnt++;
	if(TickCnt>5)
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
	RCC_Config();
	NVIC_Config();
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);//关闭jtag，保留swd。
	SysTick_init();
	SysTick_BindHandle(Tick_CallBack);
	LED_init();
	LED_Flash(0,500,2);
	USART_Config(USART1,9600);
	USART_SendStr(USART1,"USART Init\n");
	
	while(!MPUInit())
	{
		USART_SendStr(USART1,"MPU6050 failed\n");
		simple_delay_ms(500);
	}
	//USART_SendStr(USART1,"Init OK\n");
	while(1)
	{
		simple_delay_ms(500);
		//USART_SendStr(USART1,"MQBalance test\n");
	}
}
/*********************************END OF FILE**********************************/
