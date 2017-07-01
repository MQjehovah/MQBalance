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

/*********************************END OF FILE**********************************/

