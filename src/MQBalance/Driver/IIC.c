/*******************************************************************************
  * @file                   IIC.c
  * @Author:                MQjehovah                 mail:MQjehovah@hotmail.com
  * @version                1.0.3
  * @date                   2017.4.14
  * @brief                  
  ******************************************************************************
  * @attention
*******************************************************************************/
/* Includes ------------------------------------------------------------------*/
#include "IIC.h"
/* Definition ----------------------------------------------------------------*/

/* Functions -----------------------------------------------------------------*/
/*******************************************************************************
  * @brief  初始化IIC             
  * @param  None              
  * @retval None              
  * @Note   需要Delay.c               
*******************************************************************************/ 
void IIC_Init(void)
{
	GPIO_Config(&IIC_SCL_GPIO,GPIO_Mode_Out_PP);
	GPIO_Config(&IIC_SDA_GPIO,GPIO_Mode_Out_PP);
 	IIC_SCL_H;						                  //输出高
 	IIC_SDA_H;
}

/*******************************************************************************
  * @brief  产生IIC启动信号              
  * @param  None              
  * @retval None              
  * @Note   None              
*******************************************************************************/
void IIC_Start(void)
{
	IIC_SDA_OUT;    //SDA线输出
	IIC_SDA_H;	  	  
	IIC_SCL_H;
	IIC_delay_us(IIC_PAUSE);
 	IIC_SDA_L;		//START:when CLK is high,DATA change form high to low 
	IIC_delay_us(IIC_PAUSE);
	IIC_SCL_L;      //钳住I2C总线，准备发送或接收数据 
}	
/*******************************************************************************
  * @brief  产生IIC停止信号              
  * @param  None              
  * @retval None              
  * @Note   None              
*******************************************************************************/  
void IIC_Stop(void)
{
	IIC_SDA_OUT;    //SDA线输出
	IIC_SCL_L;
	IIC_SDA_L;      //STOP:when CLK is high DATA change form low to high
 	IIC_delay_us(IIC_PAUSE);
	IIC_SCL_H; 
	IIC_SDA_H;      //发送I2C总线结束信号
	IIC_delay_us(IIC_PAUSE);							   	
}

/*******************************************************************************
  * @brief  等待应答信号到来              
  * @param  None              
  * @retval None              
  * @Note   返回值：1，接收应答失败
                    0，接收应答成功            
*******************************************************************************/  
u8 IIC_Wait_Ack(void)
{
	uint16_t ucErrTime=0;
	IIC_SDA_IN;             //SDA设置为输入  
//	IIC_SDA_H;
	IIC_delay_us(IIC_PAUSE);	   
	IIC_SCL_H;
	IIC_delay_us(IIC_PAUSE);
	while(IIC_SDA_READ)
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			IIC_Stop();
			return 1;
		}
	}
	IIC_SCL_L;              //时钟输出0 	   
	return 0;  
} 
/*******************************************************************************
  * @brief  产生ACK应答             
  * @param  None              
  * @retval None              
  * @Note   None              
*******************************************************************************/  
void IIC_Ack(void)
{
	IIC_SCL_L;
	IIC_SDA_OUT;
	IIC_SDA_L;
	IIC_delay_us(IIC_PAUSE);
	IIC_SCL_H;
	IIC_delay_us(IIC_PAUSE);
	IIC_SCL_L;
}

/*******************************************************************************
  * @brief  不产生ACK应答	             
  * @param  None              
  * @retval None              
  * @Note   None              
*******************************************************************************/      
void IIC_NAck(void)
{
	IIC_SCL_L;
	IIC_SDA_OUT;
	IIC_SDA_H;
	IIC_delay_us(IIC_PAUSE);
	IIC_SCL_H;
	IIC_delay_us(IIC_PAUSE);
	IIC_SCL_L;
}

/*******************************************************************************
  * @brief  IIC读取一个字节	             
  * @param  None              
  * @retval None              
  * @Note   ack=1时，发送ACK，ack=0，发送nACK              
*******************************************************************************/      
u8 IIC_Read_Byte(void)
{
	unsigned char i,receive=0x00;
	IIC_SDA_IN;      //SDA设置为输入
    for(i=0;i<8;i++ )
	{
        IIC_SCL_L; 
        IIC_delay_us(IIC_PAUSE);
		IIC_SCL_H;
        receive<<=1;
        if(IIC_SDA_READ)receive|=0x01;   
		    IIC_delay_us(IIC_PAUSE); 
    }	
//    在读取字节时发送ACK信号，注释后需要在读写时用IIC_Ack和IIC_NAck手动发送	
//    if (!ack)
//        IIC_NAck();//发送nACK
//    else
//        IIC_Ack(); //发送ACK   
    return receive;
}

/*******************************************************************************
  * @brief  IIC发送一个字节             
  * @param  None              
  * @retval None              
  * @Note   返回从机有无应答 1，有应答
                             0，无应答		            
*******************************************************************************/ 					 				       
void IIC_Send_Byte(u8 txd)
{                        
    u8 t;   
	IIC_SDA_OUT; 	    
    IIC_SCL_L;         //拉低时钟开始数据传输
    for(t=0;t<8;t++)
    {              
        if(txd&0x80)IIC_SDA_H;
		else IIC_SDA_L;
        txd<<=1; 	  
		IIC_delay_us(IIC_PAUSE);   //对TEA5767这三个延时都是必须的
		IIC_SCL_H;
		IIC_delay_us(IIC_PAUSE); 
		IIC_SCL_L;	
		IIC_delay_us(IIC_PAUSE);
    }
	//在发送字节时接收ACK信号，注释后需要在读写时用IIC_Wait_Ack手动判断
	//IIC_SDA_IN;		               //设置SDA为输入 
	//IIC_delay_us(IIC_PAUSE);
	//IIC_SCL_H;			           //接收第九位,以判断是否发送成功
	//IIC_delay_us(IIC_PAUSE);
	//if(IIC_SDA_READ)res=1;          //SDA=1发送失败，返回1
	//else res=0;                      //SDA=0发送成功，返回0
	//IIC_SCL_L;		 
	//IIC_SDA_OUT;	                   //设置SDA为输出    
	//return res;  	
} 	 

/*******************************************************************************
  * @brief  读一个字节	             
  * @param  addr：器件slave_address
			reg ：从器件将要写入数据的地址
			data：将要写入的一个数据           
  * @retval None              
  * @Note   0 失败
			1 成功           
*******************************************************************************/ 
u8 IIC_ReadOneByte(u8 addr, u8 reg, u8* data)
{
    IIC_Start();
    IIC_Send_Byte(addr << 1 | I2C_Direction_Transmitter);
    if (IIC_Wait_Ack()) 
	{
        IIC_Stop();
        return 0;
    }
    IIC_Send_Byte(reg);
    IIC_Wait_Ack();
	IIC_Start();
	IIC_Send_Byte(addr << 1 | I2C_Direction_Receiver);
	IIC_Wait_Ack();
    *data = IIC_Read_Byte();
    IIC_NAck();
    IIC_Stop();
    return 1;
}

/*******************************************************************************
  * @brief  写一个字节	             
  * @param  addr：器件slave_address
			reg ：从器件将要写入数据的地址
			data：将要写入的一个数据           
  * @retval None              
  * @Note   0 失败
			1 成功           
*******************************************************************************/ 
u8 IIC_WriteOneByte(u8 addr, u8 reg, u8 data)
{
    IIC_Start();
    IIC_Send_Byte(addr << 1 | I2C_Direction_Transmitter);
    if (IIC_Wait_Ack()) 
	{
        IIC_Stop();
        return 0;
    }
    IIC_Send_Byte(reg);
    IIC_Wait_Ack();
    IIC_Send_Byte(data);
    IIC_Wait_Ack();
    IIC_Stop();
    return 1;
}

/*******************************************************************************
  * @brief  读数据	             
  * @param  addr：器件slave_address
			reg ：从器件将要读的数据的首地址
			len ：读出数据的长度
			buf ：将要读出的数据存储位置	           
  * @retval None              
  * @Note   0 失败
			1 成功         
*******************************************************************************/  

u8 IIC_Read_Buffer(u8 addr, u8 reg, u8 len, u8* buf)
{
    IIC_Start();
    IIC_Send_Byte(addr << 1 | I2C_Direction_Transmitter);
    if (IIC_Wait_Ack())
	{
        IIC_Stop();
        return 0;
    }
    IIC_Send_Byte(reg);
    IIC_Wait_Ack();

    IIC_Start();
    IIC_Send_Byte(addr << 1 | I2C_Direction_Receiver);
    IIC_Wait_Ack();
    while (len)
	{
        *buf = IIC_Read_Byte();
        if (len == 1)
            IIC_NAck();
        else
            IIC_Ack();
        buf++;
        len--;
    }
    IIC_Stop();
    return 1;
}

/*******************************************************************************
  * @brief  写数据	             
  * @param  addr：器件slave_address
			reg ：从器件将要写入数据的首地址
			len ：写入数据的长度
			data：将要写入的一串数据	           
  * @retval None              
  * @Note   0 失败
			1 成功
*******************************************************************************/  
u8 IIC_Write_Buffer(u8 addr, u8 reg, u8 len, u8* data)
{
    int i;
    IIC_Start();
    IIC_Send_Byte(addr << 1 | I2C_Direction_Transmitter);//7位器件从地址+读写位
    if (IIC_Wait_Ack()) 
	{
        IIC_Stop();
        return 0;
    }
    IIC_Send_Byte(reg);
    IIC_Wait_Ack();
    for (i = 0; i < len; i++) 
	{
        IIC_Send_Byte(*data);
        if (IIC_Wait_Ack()) 
		{
            IIC_Stop();
            return 0;
        }
		data++;
    }
    IIC_Stop();
    return 1;
}


u16 IIC_GetErrorCounter(void)
{
    return 0;
}

void IIC_SDA_GPIO_OUTPUT(void)  //设置SID引脚为输出模式
{
	GPIO_Config(&IIC_SDA_GPIO,GPIO_Mode_Out_PP);
}

void IIC_SDA_GPIO_INPUT(void)   //设置SID引脚为输入模式
{
	GPIO_Config(&IIC_SDA_GPIO,GPIO_Mode_IPU);
}
/*********************************END OF FILE**********************************/
