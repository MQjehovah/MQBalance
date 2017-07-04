/*******************************************************************************
  * @file                   MPU6050.c                                               
  * @Author:                MQjehovah                 mail:MQjehovah@hotmail.com
  * @version                1.0.1                                               
  * @date                   2017.4.21                                           
  * @brief                                                                      
  ******************************************************************************
  * @attention                                                                  
*******************************************************************************/
/* Includes ------------------------------------------------------------------*/
#include "MPU6050.h"
#include "USART.h"
#include "EXTI.h"
#include "math.h"
#include "pid.h"
/* Definition ----------------------------------------------------------------*/
/*******************************************************************************
  * @brief  MPU6050Init   
  * @param  None   
  * @retval None   
  * @Note   0：失败
			1：成功
*******************************************************************************/
u8 MPUInit(void)
{
	u8 id = 0;
	IIC_Init();
	simple_delay_ms(10);
	//通信验证
	if(IIC_ReadOneByte(MPU_ADDR,MPU6050_RA_WHO_AM_I,&id))
	{
		id &= 0x7e;//除去最高位最低位
		id>>= 1;
		if(id != 0x34) 
		{
			printf("error id %02X\r\n",id);
			return 0;	//获取到的芯片ID错误
		}
	}
	else
	{
		printf("IIC error\r\n");
		return 0;	//IIC读取错误
	}
	//设置中断
	//EXTI_Config();
    //初始化成功，设置参数
    IIC_WriteOneByte(MPU_ADDR, MPU6050_RA_PWR_MGMT_1, 0x02);			// 退出睡眠模式，设取样时钟为陀螺Y轴。
    IIC_WriteOneByte(MPU_ADDR, MPU6050_RA_SMPLRT_DIV, 2);			// 取样时钟4分频，1k/4，取样率为25Hz。
    IIC_WriteOneByte(MPU_ADDR, MPU6050_RA_CONFIG, 0x06);				// 低通滤波，截止频率100Hz左右。
    IIC_WriteOneByte(MPU_ADDR, MPU6050_RA_GYRO_CONFIG, 0x18);			// 陀螺量程，2000dps
    IIC_WriteOneByte(MPU_ADDR, MPU6050_RA_ACCEL_CONFIG, 0x00);			// 加速度计量程，2g。
    //IIC_WriteOneByte(MPU_ADDR, MPU6050_RA_INT_PIN_CFG, 0x32);			// 中断信号为高电平，推挽输出，直到有读取操作才消失，直通辅助I2C。
    //IIC_WriteOneByte(MPU_ADDR, MPU6050_RA_INT_ENABLE, 0x01);			// 使用“数据准备好”中断。
    //IIC_WriteOneByte(MPU_ADDR, MPU6050_RA_USER_CTRL, 0x00);			// 不使用辅助I2C。
	MPU6050_TIM_Config();
    return 1;
}


float MPU_GetAccelX()
{
	int temp = (IIC_ReadByte(MPU_ADDR, MPU6050_RA_ACCEL_XOUT_H) << 8) + IIC_ReadByte(MPU_ADDR, MPU6050_RA_ACCEL_XOUT_L);
	if(temp > 32768)  temp -= 65536;                   //数据类型转换  也可通过short强制类型转换
	return temp;
}

float MPU_GetAccelY()
{
	int temp = (IIC_ReadByte(MPU_ADDR, MPU6050_RA_ACCEL_YOUT_H) << 8) + IIC_ReadByte(MPU_ADDR, MPU6050_RA_ACCEL_YOUT_L);
	if(temp > 32768)  temp -= 65536;
	return temp;
}

float MPU_GetAccelZ()
{
	int temp = (IIC_ReadByte(MPU_ADDR, MPU6050_RA_ACCEL_ZOUT_H) << 8) + IIC_ReadByte(MPU_ADDR, MPU6050_RA_ACCEL_ZOUT_L);
	if(temp > 32768)  temp -= 65536;
	return temp;
}


float MPU_GetGyroX()
{
	int temp = (IIC_ReadByte(MPU_ADDR, MPU6050_RA_GYRO_XOUT_H) << 8) + IIC_ReadByte(MPU_ADDR, MPU6050_RA_GYRO_XOUT_L);
	if(temp > 32768)  temp -= 65536;
	return temp;
}

float MPU_GetGyroY()
{
	int temp = (IIC_ReadByte(MPU_ADDR, MPU6050_RA_GYRO_YOUT_H) << 8) + IIC_ReadByte(MPU_ADDR, MPU6050_RA_GYRO_YOUT_L);
	if(temp > 32768)  temp -= 65536;
	return temp-40;//清除零偏
}

float MPU_GetGyroZ()
{
	int temp = (IIC_ReadByte(MPU_ADDR, MPU6050_RA_GYRO_ZOUT_H) << 8) + IIC_ReadByte(MPU_ADDR, MPU6050_RA_GYRO_ZOUT_L);
	if(temp > 32768)  temp -= 65536;
	return temp;
}

float MPU_GetTemp()
{
	int temp = (IIC_ReadByte(MPU_ADDR, MPU6050_RA_TEMP_OUT_H) << 8) + IIC_ReadByte(MPU_ADDR, MPU6050_RA_TEMP_OUT_L);
	temp = 35+temp/280; // 计算出温度
	return temp;
}
/*******************************************************************************
  * @brief  MPU6050_TIM_Config   
  * @param  None   
  * @retval None   
  * @Note   MPU6050读取数据定时中断
*******************************************************************************/
void MPU6050_TIM_Config()
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;

    TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
	TIM_TimeBaseStructure.TIM_Period = 9999; //设定计数器自动重装值
    TIM_TimeBaseStructure.TIM_Prescaler = 35; // 预分频器
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;//选择时钟分频：不分频
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;////TIM向上计数
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
	TIM_ClearFlag(TIM3, TIM_FLAG_Update);//清除TIM的更新标志位
    TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
    TIM_Cmd(TIM3, ENABLE);
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
	angle = 0.1 * angle_Accel + 0.9 * (angle - (Gyro_Y / 16.4f) * 0.01);
	//Balance_GyroY = Gyro_Y;							//更新平衡角速度
	//Balance_GyroZ = Gyro_Z;							//更新转向角速度
	//Acceleration_Z = Accel_Z;						//更新Z轴加速度计
	return angle;									//更新平衡倾角
}


/**************************************************************************
函数功能：限制PWM赋值
入口参数：无
返回  值：无
**************************************************************************/
void Xianfu_Pwm(int pwm)
{
    int Amplitude = 6900;  //===PWM满幅是7200 限制在6900
    if(pwm < -Amplitude) pwm = -Amplitude;
    if(pwm > Amplitude)  pwm = Amplitude;
}


PID_Type POS_PID = {.kP = 10,.kD = 0.1};
float target =0;
void TIM3_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM3,TIM_IT_Update) != RESET)	//发生了捕获中断   定时器计数没有溢出  
	{ 
		GetAngel();
		int pwm = LocPIDCalc(&POS_PID,angle-target);
		Xianfu_Pwm(pwm);
		
		
		
		TIM_ClearFlag(TIM3, TIM_FLAG_Update);//清除TIM的更新标志位
	}
}

/*********************************END OF FILE**********************************/

