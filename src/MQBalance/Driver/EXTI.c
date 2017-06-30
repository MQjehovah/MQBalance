/*******************************************************************************
  * @file                   EXTI.c
  * @Author:                MQjehovah                 mail:MQjehovah@hotmail.com
  * @version                1.0.0
  * @date                   2017.5.22
  * @brief                  
  ******************************************************************************
  * @attention
*******************************************************************************/
/* Includes ------------------------------------------------------------------*/
#include "EXTI.h"

/* Definition ----------------------------------------------------------------*/

/* Functions -----------------------------------------------------------------*/
/*******************************************************************************
  * @brief  EXTI端口配置       
  * @param  None              
  * @retval None              
  * @Note   None              
*******************************************************************************/
void EXTI_GPIO_Config()
{
	GPIO_Config(&PA0,GPIO_Mode_IN_FLOATING);
}
/*******************************************************************************
  * @brief  EXTI初始化    
  * @param  None              
  * @retval None              
  * @Note   None              
*******************************************************************************/
void EXTI_Config()
{
	EXTI_GPIO_Config();
	EXTI_InitTypeDef EXTI_InitStructure;
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource3);
	EXTI_InitStructure.EXTI_Line= EXTI_Line3; 	//选择中断线路2 3 5
    EXTI_InitStructure.EXTI_Mode= EXTI_Mode_Interrupt;					 //设置为中断请求，非事件请求
    EXTI_InitStructure.EXTI_Trigger= EXTI_Trigger_Rising; 		//设置中断触发方式为上升沿触发
    EXTI_InitStructure.EXTI_LineCmd=ENABLE;								//外部中断使能
    EXTI_Init(&EXTI_InitStructure);
}
/*******************************************************************************
  * @brief  EXTI中断函数       
  * @param  None              
  * @retval None              
  * @Note   None              
*******************************************************************************/
void EXTI1_IRQHandler(void)
{
    if (EXTI_GetITStatus(EXTI_Line1) != RESET)
    {
        EXTI_ClearITPendingBit(EXTI_Line1); //清除标志
        //...
		
    }
}
/*********************************END OF FILE**********************************/
