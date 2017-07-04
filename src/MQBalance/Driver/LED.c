/*******************************************************************************
  * @file                   LED.c
  * @Author:                MQjehovah                 mail:MQjehovah@hotmail.com
  * @version                1.0.0
  * @date                   2016.3.17
  * @brief
  ******************************************************************************
  * @attention
*******************************************************************************/
/* Includes ------------------------------------------------------------------*/
#include "LED.h"
/* Definition ----------------------------------------------------------------*/
LED_DEV LED[LED_NUM] = {{&LED1_GPIO, 0}, {&LED2_GPIO, 0}};
/* Functions -----------------------------------------------------------------*/
/*******************************************************************************
  * @brief  LED端口配置
  * @param  None
  * @retval None
  * @Note   None
*******************************************************************************/
void LED_GPIO_Config()
{
    for(u8 i = 0; i < LED_NUM; i++)
    {
        GPIO_Config(LED[i].gpio, GPIO_Mode_Out_PP);
    }
}
/*******************************************************************************
  * @brief  LED初始化
  * @param  None
  * @retval None
  * @Note   None
*******************************************************************************/
void LED_init()
{
    LED_GPIO_Config();
}
/*******************************************************************************
  * @brief  点亮LED
  * @param  None
  * @retval None
  * @Note   None
*******************************************************************************/
void LED_ON(u8 id)
{
    if(id < LED_NUM)
        GPIO_WritePin(LED[id].gpio, HIGH);
}
/*******************************************************************************
  * @brief  关闭LED
  * @param  None
  * @retval None
  * @Note   None
*******************************************************************************/
void LED_OFF(u8 id)
{
    if(id < LED_NUM)
        GPIO_WritePin(LED[id].gpio, LOW);
}
/*******************************************************************************
  * @brief  LED闪烁
  * @param  None
  * @retval None
  * @Note   None
*******************************************************************************/
void LED_Flash(u8 id, u16 time, u8 count)
{
    for(u8 i = 0; i < count; i++)
    {
        LED_ON(id);
        simple_delay_ms(time);
        LED_OFF(id);
        simple_delay_ms(time);
    }
}
/*******************************************************************************
  * @brief  设置LED状态
  * @param  None
  * @retval None
  * @Note   None
*******************************************************************************/
void LED_SetState(u8 id, LED_STA state)
{
    if(state == ON)
        GPIO_WritePin(LED[id].gpio, HIGH);
    else
        GPIO_WritePin(LED[id].gpio, LOW);
}
/*******************************************************************************
  * @brief  获取LED状态
  * @param  None
  * @retval None
  * @Note   None
*******************************************************************************/
LED_STA LED_GetState(u8 id)
{
    if(GPIO_ReadPin(LED[id].gpio) == HIGH)
        return ON;
    else
        return OFF;
}

#ifdef OS
/*******************************************************************************
  * @brief  LED闪烁
  * @param  None
  * @retval None
  * @Note   None
*******************************************************************************/
void led_flash_os(unsigned char num, int time, int times)
{
    int i = 0;
    for(i = 0; i < times; i++)
    {
        LED_ON(num);
        OSTimeDlyHMSM(0, 0, 1, 0);
        LED_OFF(num);
        OSTimeDlyHMSM(0, 0, 1, 0);
    }
}
#endif
/*********************************END OF FILE**********************************/
