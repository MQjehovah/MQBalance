/**
  ******************************************************************************
  * @file                   USART_Driver.c
  * @Author:                MQjehovah                      MQjehovah@hotmail.com
  * @version                1.0.0
  * @date                   2015.5.19
  * @brief                  
  ******************************************************************************
  * @attention
  * 
  ******************************************************************************
**/

/* Includes ------------------------------------------------------------------*/
#include "USART_Driver.h"
#include "stm32f10x_usart.h"
/* Definition ----------------------------------------------------------------*/
#ifdef __GNUC__
/* With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf
     set to 'Yes') calls __io_putchar() */
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */
/* Functions -----------------------------------------------------------------*/
void USART1_Configuration(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;  		 
	USART_InitTypeDef USART_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);		 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;    
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;    
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;    
	GPIO_Init(GPIOA, &GPIO_InitStructure);        
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;  
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;   
	GPIO_Init(GPIOA, &GPIO_InitStructure);    
	USART_InitStructure.USART_BaudRate = 9600;//115200;    
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;    
	USART_InitStructure.USART_StopBits = USART_StopBits_1;    
	USART_InitStructure.USART_Parity = USART_Parity_No ;    
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;   
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;   
	USART_Init(USART1, &USART_InitStructure);    
	USART_Cmd(USART1, ENABLE);    
}

void USART_SendStr(char* senddata)
{
	int lenth=strlen(senddata);
	int i;
	for (i=0; i<lenth; i++)
 	{
		USART_SendData(USART1,*senddata++);
		while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
	}        
}  

//不使用半主机模式
#if 1 //如果没有这段，则需要在target选项中选择使用USE microLIB
#pragma import(__use_no_semihosting)
struct __FILE  
{  
	int handle;  
};  
FILE __stdout;  

_sys_exit(int x)  
{  
	x = x;  
}
#endif


PUTCHAR_PROTOTYPE
{
	/* Place your implementation of fputc here */
	/* e.g. write a character to the USART */
	USART_SendData(USART1,(u8)ch);

	/* Loop until the end of transmission */
	while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);

	return ch;
}
/*********************************END OF FILE**********************************/
