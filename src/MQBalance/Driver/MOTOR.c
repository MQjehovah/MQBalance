/*******************************************************************************
  * @file                   MOTOR.c
  * @Author:                MQjehovah                 mail:MQjehovah@hotmail.com
  * @version                1.0.1
  * @date                   2017.5.9
  * @brief                  添加电机数组，批量控制
  ******************************************************************************
  * @attention
*******************************************************************************/
/* Includes ------------------------------------------------------------------*/
#include "MOTOR.h"
#include "stdio.h"
/* Definition ----------------------------------------------------------------*/
MOTOR_DEV MOTOR_L;
MOTOR_DEV MOTOR_R;
/* Functions -----------------------------------------------------------------*/
/*******************************************************************************
  * @brief  电机GPIO配置
  * @param  None
  * @retval None
  * @Note   方向IO的初始化以及驱动PWM的配置
*******************************************************************************/
void MOTOR_GPIO_Config()
{
	//方向控制引脚配置
	GPIO_Config(&MOTOR_L_DIR1_GPIO, GPIO_Mode_Out_PP);
	GPIO_Config(&MOTOR_L_DIR2_GPIO, GPIO_Mode_Out_PP);
	GPIO_Config(&MOTOR_R_DIR1_GPIO, GPIO_Mode_Out_PP);
	GPIO_Config(&MOTOR_R_DIR2_GPIO, GPIO_Mode_Out_PP);
	//脉冲输出引脚配置
	GPIO_Config(&MOTOR_L_PWM_GPIO, GPIO_Mode_AF_PP);
	GPIO_Config(&MOTOR_R_PWM_GPIO, GPIO_Mode_AF_PP);
}
void MOTOR_PWM_Config()
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;

	TIM_TimeBaseStructure.TIM_Period = 7199;			//设置在下一个更新事件装入活动的自动重装载寄存器周期的值
	TIM_TimeBaseStructure.TIM_Prescaler =0;				//设置用来作为TIMx时钟频率除数的预分频值  不分频
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;		//设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;	//TIM向上计数模式
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);		//根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位

	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;	//选择定时器模式:TIM脉冲宽度调制模式1
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;	//比较输出使能
	TIM_OCInitStructure.TIM_Pulse = 0;								//设置待装入捕获比较寄存器的脉冲值
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;		//输出极性:TIM输出比较极性高
	TIM_OC1Init(TIM2, &TIM_OCInitStructure);			//根据TIM_OCInitStruct中指定的参数初始化外设TIMx
	TIM_OC2Init(TIM2, &TIM_OCInitStructure);			//根据TIM_OCInitStruct中指定的参数初始化外设TIMx

	TIM_CtrlPWMOutputs(TIM2,ENABLE);					//MOE 主输出使能
	TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Enable);	//CH1预装载使能
	TIM_OC2PreloadConfig(TIM2, TIM_OCPreload_Enable);	//CH4预装载使能
	TIM_ARRPreloadConfig(TIM2, ENABLE);					//使能TIMx在ARR上的预装载寄存器
	TIM_Cmd(TIM2, ENABLE);  //使能TIM1
 
} 
/*******************************************************************************
  * @brief  电机初始化
  * @param  None
  * @retval None
  * @Note   方向IO的初始化以及驱动PWM的配置
*******************************************************************************/
void MOTOR_init()
{
    MOTOR_GPIO_Config();
	MOTOR_PWM_Config();
	MOTOR_L_SetPWM(0);
	MOTOR_R_SetPWM(0);
}
/*******************************************************************************
  * @brief  左轮 电机PWM占空比设置
  * @param  None
  * @retval None
  * @Note   None
*******************************************************************************/
void MOTOR_L_SetPWM(u16 duty)
{
    TIM_SetCompare1(TIM2,duty);
}
/*******************************************************************************
  * @brief  右轮电机PWM占空比设置
  * @param  None
  * @retval None
  * @Note   None
*******************************************************************************/
void MOTOR_R_SetPWM(u16 duty)
{
    TIM_SetCompare2(TIM2,duty);
}
/*******************************************************************************
  * @brief  电机运动控制
  * @param  None
  * @retval None
  * @Note   None
*******************************************************************************/
void MOTOR_Move(MOTOR_DEV * motor, u8 dir, u16 speed)
{
    motor->dir = dir;
    motor->target_speed = speed;
}
/*******************************************************************************
  * @brief  电机停止
  * @param  None
  * @retval None
  * @Note   None
*******************************************************************************/
void MOTOR_Stop(u8 id)
{
	;
}
/*******************************************************************************
  * @brief  电机速度设置
  * @param  None
  * @retval None
  * @Note   None
*******************************************************************************/
void MOTOR_Set_Speed(u8 id, u16 speed)
{
	;
}

/*******************************************************************************
  * @brief  电机方向设置
  * @param  None
  * @retval None
  * @Note   None
*******************************************************************************/
void Motor_Set_Dir(u8 dir)
{
    if(dir)
	{
		GPIO_WritePin(&MOTOR_L_DIR1_GPIO,LOW);
		GPIO_WritePin(&MOTOR_L_DIR2_GPIO,HIGH);
		GPIO_WritePin(&MOTOR_R_DIR1_GPIO,LOW);
		GPIO_WritePin(&MOTOR_R_DIR2_GPIO,HIGH);
	}
    else
	{
		GPIO_WritePin(&MOTOR_L_DIR1_GPIO,HIGH);
		GPIO_WritePin(&MOTOR_L_DIR2_GPIO,LOW);
		GPIO_WritePin(&MOTOR_R_DIR1_GPIO,HIGH);
		GPIO_WritePin(&MOTOR_R_DIR2_GPIO,LOW);
	}
}
/*********************************END OF FILE**********************************/
