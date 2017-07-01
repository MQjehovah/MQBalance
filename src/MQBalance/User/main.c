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
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);    
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;    
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;    
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;    
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;    
	NVIC_Init(&NVIC_InitStructure);   

//	NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;			//使能按键所在的外部中断通道
//  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//抢占优先级2， 
//  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;					//子优先级1
//  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
//  	NVIC_Init(&NVIC_InitStructure); 	
}    
u16 temp=0;
float at;
void Tick_CallBack()
{
	static u16 TickCnt;
	TickCnt++;
	if(TickCnt>1000)
	{
		TickCnt=0;
		printf("1s\r\n");
		//GetAngel();
	}
}
void TIM_Co()
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;

    TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
	TIM_TimeBaseStructure.TIM_Period = 4999; //设定计数器自动重装值
    TIM_TimeBaseStructure.TIM_Prescaler = 35; // 预分频器
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;//选择时钟分频：不分频
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;////TIM向上计数
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
	TIM_ClearFlag(TIM2, TIM_FLAG_Update);//清除TIM的更新标志位
    TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
    TIM_Cmd(TIM2, ENABLE);
}

int Gyro_X,Gyro_Y,Gyro_Z;
int Accel_X,Accel_Y,Accel_Z;

float angle,angle_Accel,angle_Gyro; 	

float GetAngel()
{
	Accel_X = MPU_GetAccelX();
	Accel_Z = MPU_GetAccelZ();
	Gyro_Y = MPU_GetGyroY();
	Gyro_Z = MPU_GetGyroZ();

	angle_Accel = atan2(Accel_X, Accel_Z) * 57.3f;	//计算倾角
	angle_Gyro += (Gyro_Y / 16.4f) * 0.005;
	angle = 0.1 * angle_Accel + 0.9 * angle_Gyro;
	//Balance_GyroY = Gyro_Y;							//更新平衡角速度
	//Balance_GyroZ = Gyro_Z;							//更新转向角速度
	//Acceleration_Z = Accel_Z;						//更新Z轴加速度计
	return angle;									//更新平衡倾角
}

int cnt;
void TIM2_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM2,TIM_IT_Update) != RESET)	//发生了捕获中断   定时器计数没有溢出  
	{  
		cnt++;
		if(cnt>200)
		{
			printf("1s");
			cnt=0;
		}
		GetAngel();
		TIM_ClearFlag(TIM2, TIM_FLAG_Update);//清除TIM的更新标志位
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
	//SysTick_init();
	
	//LED_init();
	//LED_Flash(0,500,2);
	USART_Config(USART1,9600);
	USART_SendStr(USART1,"USART Init OK\n");
	
	while(!MPUInit())
	{
		USART_SendStr(USART1,"MPU6050 failed\n");
		simple_delay_ms(500);
	}
	USART_SendStr(USART1,"MPU6050 Init OK\n");
	TIM_Co();
	//SysTick_BindHandle(Tick_CallBack);
	while(1)
	{
		simple_delay_ms(10);
//		printf("Gyro_Y:%d  ",Gyro_Y);
//		printf("angle_Accel:%f  ",angle_Accel);
//		printf("angle_Gyro:%f  ",angle_Gyro);
//		printf("%f\r\n",angle);
		//USART_SendStr(USART1,"MQBalance test\n");
		
	}
}
/*********************************END OF FILE**********************************/
