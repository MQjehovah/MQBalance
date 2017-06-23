/*******************************************************************************
  * @file                   delay.c
  * @Author:                MQjehovah                 mail:MQjehovah@hotmail.com
  * @version                1.0.1
  * @date                   2017.5.15
  * @brief                  添加sysTick延时
  ******************************************************************************
  * @attention
*******************************************************************************/
/* Includes ------------------------------------------------------------------*/
#include "delay.h"
#include "stdio.h"
/* Definition ----------------------------------------------------------------*/
u16 TimeTick;
u32 sys_Time;
void (*SysTick_CB)(void);
/* Functions -----------------------------------------------------------------*/
/*******************************************************************************
  * @brief  初始化时钟             
  * @param  None              
  * @retval None              
  * @Note   72000000/（1000*72000）              
*******************************************************************************/
void SysTick_init()
{
	if(SysTick_Config(SystemCoreClock / 1000)) //系统滴答时钟100us
	while(1);
}
/*******************************************************************************
  * @brief  绑定滴答时钟事件         
  * @param  None              
  * @retval None              
  * @Note   None           
*******************************************************************************/
void SysTick_BindHandle(void (*pCB)(void))
{
	SysTick_CB = pCB;
}
/*******************************************************************************
  * @brief  清除滴答时钟事件绑定            
  * @param  None              
  * @retval None              
  * @Note   None          
*******************************************************************************/
void SysTick_ClearBind()
{
	SysTick_CB = NULL;
}
/*******************************************************************************
  * @brief  精确ms延时             
  * @param  None              
  * @retval None              
  * @Note   None              
*******************************************************************************/
void delay_ms(u32 nTime)
{
	u32 start = sys_Time;
	while(sys_Time - start < nTime);
}

/*******************************************************************************
  * @brief  时钟中断             
  * @param  None              
  * @retval None              
  * @Note   None              
*******************************************************************************/
void SysTick_Handler(void)
{
	sys_Time++;//系统计时
	if(SysTick_CB != NULL)
	{
		(*SysTick_CB)();
	}
	
}
/*******************************************************************************
  * @brief  粗略微秒级延时             
  * @param  None              
  * @retval None              
  * @Note   None              
*******************************************************************************/
void simple_delay_us(u16 us)
{
	u16 i,k;
	for(i=0;i<us;i++)
		for(k=0;k<10;k++);
}
/*******************************************************************************
  * @brief  粗略毫秒级延时             
  * @param  None              
  * @retval None              
  * @Note   None              
*******************************************************************************/
void simple_delay_ms(u16 ms)
{
	u16 i,k;
	for(i=0;i<ms;i++)
		for(k=0;k<10000;k++);
}

/*********************************END OF FILE**********************************/