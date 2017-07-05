/*******************************************************************************
  * @file                   protocol.c
  * @Author:                MQjehovah                 mail:MQjehovah@hotmail.com
  * @version                1.0.0
  * @date                   2016.5.26
  * @brief					串口协议
  ******************************************************************************
  * @attention
*******************************************************************************/
/* Includes ------------------------------------------------------------------*/
#include "protocol.h"
#include "USART.h"
/* Definition ----------------------------------------------------------------*/
u8 sendData[10] = {0xA5, 0x5A, 0x00, 0x00, 0x00,
                   0x00, 0x00, 0x00, 0x00, 0x00};
/* Functions -----------------------------------------------------------------*/
u8 recData[10];
u8 recPtr = 0;
RecState recState = IDLE;
PID_Type MOTOR_PID;
extern u16 target;
/*******************************************************************************
  * @brief  协议帧处理
  * @param  None
  * @retval None
  * @Note   None
*******************************************************************************/
void Process(u8 data[])
{
    if(data[3] == 0x03)
    {
        target = Byte2Short(data, 7);
    }

    if(data[3] == 0x02)
    {
        switch(data[4])
        {
        case 0x00:
            MOTOR_PID.kP = (double)Byte2float(data, 5);
            break;
        case 0x01:
            MOTOR_PID.kI = (double)Byte2float(data, 5);
            break;
        case 0x02:
            MOTOR_PID.kD = (double)Byte2float(data, 5);
            break;
        }
    }
}
/*******************************************************************************
  * @brief  协议帧解析
  * @param  None
  * @retval None
  * @Note   None
*******************************************************************************/
void Parser(u8 data)
{
    switch(recState)
    {
    case IDLE:
        if (data == 0xA5)
        {
            recPtr = 0;
            recData[recPtr++] = 0xA5;
            recState = HEADREADY;
        }
        break;
    case HEADREADY:
        if (data == 0x5A)
        {
            recData[recPtr++] = 0x5A;
            recState = RECING;
        }
        else
        {
            recPtr = 0;
            recState = IDLE;
        }
        break;
    case RECING:
        recData[recPtr++] = data;
        if (recPtr > 9)
        {
            Process(recData);
            recPtr = 0;
            recState = IDLE;
        }
        break;
    }

}

void short2Byte(short num, u8 bytes[], int offset)
{
    bytes[offset]   = (u8)(num);
    bytes[offset + 1] = (u8)(num >> 8);
}

short Byte2Short(u8 bytes[], int offset)
{
    short tmp;
    tmp = bytes[offset + 1];
    tmp <<= 8;
    tmp += bytes[offset];
    return tmp;
}

void int2Byte(int num, u8 bytes[], int offset)
{
    bytes[offset]   = (u8)(num);
    bytes[offset + 1] = (u8)(num >> 8);
	bytes[offset + 2] = (u8)(num >> 16);
	bytes[offset + 3] = (u8)(num >> 24);
}

int Byte2int(u8 bytes[], int offset)
{
    int tmp;
    tmp = bytes[offset + 3];
    tmp <<= 8;
    tmp += bytes[offset + 2];
	tmp <<= 8;
    tmp += bytes[offset + 1];
	tmp <<= 8;
    tmp += bytes[offset];
    return tmp;
}

void float2Byte(float *target, unsigned char *buf, unsigned char beg)
{
    unsigned char *point;
    point = (unsigned char*)target;	  //得到float的地址
    buf[beg]   = point[0];
    buf[beg + 1] = point[1];
    buf[beg + 2] = point[2];
    buf[beg + 3] = point[3];
}

short Byte2float(u8 bytes[], int offset)
{
    float tmp;
    u8 * Ptr = (u8*)(&tmp);
    Ptr[0] = bytes[offset];
    Ptr[1] = bytes[offset + 1];
    Ptr[2] = bytes[offset + 2];
    Ptr[3] = bytes[offset + 3];
    return tmp;
}

void SetData(int num)
{
    int2Byte(num, sendData, 5);
}

void DataUpload(void)
{
    USART_SendArray(USART1,sendData,10);
}

/*********************************END OF FILE**********************************/
