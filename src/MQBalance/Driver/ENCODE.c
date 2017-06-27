/*******************************************************************************
  * @file                   ENCODE.c
  * @Author:                MQjehovah                 mail:MQjehovah@hotmail.com
  * @version                1.0.0
  * @date                   2017.5.26
  * @brief
  ******************************************************************************
  * @attention
*******************************************************************************/
/* Includes ------------------------------------------------------------------*/
#include "ENCODE.h"
/* Definition ----------------------------------------------------------------*/
s16 Encoder;
s16 EncodeCnt;
/* Functions -----------------------------------------------------------------*/
/*******************************************************************************
  * @brief  编码器端口配置
  * @param  None
  * @retval None
  * @Note   None
*******************************************************************************/
void ENCODE_GPIO_Config(void)
{
    GPIO_Config(&ENCODE_LINEA_GPIO, GPIO_Mode_IN_FLOATING);
    GPIO_Config(&ENCODE_LINEB_GPIO, GPIO_Mode_IN_FLOATING);
}
/*******************************************************************************
  * @brief  把定时器初始化为编码器接口模式
  * @param  None
  * @retval None
  * @Note   None
*******************************************************************************/
void ENCODE_TIM_Init(void)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    TIM_ICInitTypeDef TIM_ICInitStructure;

    ENCODE_GPIO_Config();

    TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
    TIM_TimeBaseStructure.TIM_Prescaler = 0x0; // 预分频器
    TIM_TimeBaseStructure.TIM_Period = 65535; //设定计数器自动重装值
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;//选择时钟分频：不分频
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;////TIM向上计数
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

    TIM_EncoderInterfaceConfig(TIM2, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);//使用编码器模式3
    TIM_ICStructInit(&TIM_ICInitStructure);
    TIM_ICInitStructure.TIM_ICFilter = 10;
    TIM_ICInit(TIM2, &TIM_ICInitStructure);
    TIM_ClearFlag(TIM2, TIM_FLAG_Update);//清除TIM的更新标志位
    TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
    TIM_SetCounter(TIM2, 0);    //Reset counter
    TIM_Cmd(TIM2, ENABLE);
}

void TIM2_IRQHandler(void)
{
    if(TIM2->SR & 0X0001) //溢出中断
    {
    }
    TIM2->SR &= ~(1 << 0); //清除中断标志位
}
/*******************************************************************************
  * @brief  单位时间读取编码器计数
  * @param  定时器
  * @retval 速度值
  * @Note   None
*******************************************************************************/
s16 ENCODE_TIM_Read(void)
{
    Encoder = (short)TIM2 -> CNT;
    TIM2 -> CNT = 0;
    return Encoder;
}

void ENCODE_EXTI_Init(void)
{
    EXTI_InitTypeDef EXTI_InitStructure;

    ENCODE_GPIO_Config();

    GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource0);	//GPIOA.0	  中断线配置
    EXTI_InitStructure.EXTI_Line = EXTI_Line0;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);		//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器
}
void EXTI0_IRQHandler(void)
{
//	Enconder_In();
    if(ENCODE_LINEB_READ == 0)
    {
        EncodeCnt--;
    }
    else
    {
        EncodeCnt++;
    }
    EXTI_ClearITPendingBit(EXTI_Line0);  //清除EXTI0线路挂起位
}

s16 ENCODE_EXTI_Read(void)
{
    Encoder = EncodeCnt;
    EncodeCnt = 0;
    return Encoder;
}
/*********************************END OF FILE**********************************/
