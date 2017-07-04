/*******************************************************************************
  * @file                   MOTOR.h
  * @Author:                MQjehovah                 mail:MQjehovah@hotmail.com
  * @version                1.0.1
  * @date                   2017.5.9
  * @brief                  
  ******************************************************************************
  * @attention
*******************************************************************************/
#ifndef _MOTOR_H
#define _MOTOR_H
/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_conf.h"
#include "TIMER.h"
#include "GPIO.h"
/* Definition ----------------------------------------------------------------*/
#define MOTOR_L_PWM_GPIO		PA0
#define MOTOR_L_DIR1_GPIO		PB4
#define MOTOR_L_DIR2_GPIO		PB5

#define MOTOR_R_PWM_GPIO		PA1
#define MOTOR_R_DIR1_GPIO		PB6
#define MOTOR_R_DIR2_GPIO		PB7

typedef struct
{
	u8 dir;
	u16 pwm;
	u16 cur_speed;
	u16 target_speed;
}MOTOR_DEV;

extern MOTOR_DEV MOTOR_L;
extern MOTOR_DEV MOTOR_R;
/* Exported Functions --------------------------------------------------------*/
void MOTOR_init(void);
void MOTOR_Move(MOTOR_DEV * motor, u8 dir, u16 speed);
void MOTOR_Stop(u8 id);
void MOTOR_Set_Speed(u8 id,u16 speed);
void MOTOR_L_SetPWM(u16 duty);
void MOTOR_R_SetPWM(u16 duty);
/*********************************END OF FILE**********************************/
#endif
