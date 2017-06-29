/*******************************************************************************
  * @file                   TIMER.c
  * @Author:                MQjehovah                 mail:MQjehovah@hotmail.com
  * @version                1.0.0
  * @date                   2017.5.9
  * @brief                  
  ******************************************************************************
  * @attention
*******************************************************************************/
/* Includes ------------------------------------------------------------------*/
#include "TIMER.h"
/* Definition ----------------------------------------------------------------*/

/* Functions -----------------------------------------------------------------*/
/*******************************************************************************
  * @brief  TIM4配置              
  * @param  freq：设置定时器频率 
			频率计算公式：f=TIMCLK/((Period+1)*(Prescaler+1))
  * @retval None              
  * @Note   默认APB1时钟为36M              
*******************************************************************************/
void TIM_init(TIM_DEV dev, u16 freq)
{ 
	TIM_Config(dev);
} 

/*******************************************************************************
  * @brief  TIM配置              
  * @param  None                 
  * @retval None                 
  * @Note   None                 
*******************************************************************************/
void TIM_Config(TIM_DEV dev)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;				//初始化结构体
	//时钟统一由RCC_Config配置
	TIM_DeInit(dev.timer);
	//((1+TIM_Prescaler )/72M)*(1+TIM_Period )=((1+7199)/72M)*(1+9999)=1秒 */ 
	TIM_TimeBaseStructure.TIM_Period=7200-1;					//定时器周期
	TIM_TimeBaseStructure.TIM_Prescaler=1-1;					//预分频数
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;		//TIM2时钟分频,为1表示不分频
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;	//定时器计数为向上计数模式
	TIM_TimeBaseInit(dev.timer, &TIM_TimeBaseStructure);     

	
	TIM_OCInitTypeDef  TIM_OCInitStructure;  
	TIM_ICInitTypeDef  TIM_ICInitStructure;  
	if(dev.channel1!=NULL)
	{
		if(dev.channel1->mode == TIM_MODE_PWM)
		{
			GPIO_Config(dev.channel1->gpio,GPIO_Mode_AF_PP);
			TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;                           //配置为PWM模式1  
			TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;                
			TIM_OCInitStructure.TIM_OCPolarity =TIM_OCPolarity_High;                    //当定时器计数值小于CCR1时为高电平  
			TIM_OCInitStructure.TIM_Pulse = 0;                                          //设置跳变值，当计数器计数到这个值时，电平发生跳变  
			TIM_OC1Init(dev.timer, &TIM_OCInitStructure);                               //使能通道1      
			TIM_OC1PreloadConfig(dev.timer, TIM_OCPreload_Enable);  
		}
		else if(dev.channel1->mode == TIM_MODE_CAP)
		{
			GPIO_Config(dev.channel1->gpio,GPIO_Mode_IPD);
			GPIO_WritePin(dev.channel1->gpio,LOW);  
			TIM_ICInitStructure.TIM_Channel = TIM_Channel_1; //CC1S=01     选择输入端 IC1映射到TI1上  
			TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;    //上升沿捕获  
			TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //映射到TI1上  
			TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;   //配置输入分频,不分频   
			TIM_ICInitStructure.TIM_ICFilter = 0x00;//IC1F=0000 配置输入滤波器 不滤波  
			TIM_ICInit(dev.timer, &TIM_ICInitStructure);
			TIM_ITConfig(dev.timer,TIM_IT_CC1,ENABLE);//允许更新中断 ,允许CC1IE捕获中断
		}
	}
	if(dev.channel2!=NULL)
	{
		if(dev.channel2->mode == TIM_MODE_PWM)
		{
			GPIO_Config(dev.channel2->gpio,GPIO_Mode_AF_PP);
			TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;                           //配置为PWM模式1  
			TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;                
			TIM_OCInitStructure.TIM_OCPolarity =TIM_OCPolarity_High;                    //当定时器计数值小于CCR1时为高电平  
			TIM_OCInitStructure.TIM_Pulse = 0;                                          //设置跳变值，当计数器计数到这个值时，电平发生跳变  
			TIM_OC2Init(dev.timer, &TIM_OCInitStructure);                               //使能通道1      
			TIM_OC2PreloadConfig(dev.timer, TIM_OCPreload_Enable);  
		}
		else if(dev.channel2->mode == TIM_MODE_CAP)
		{
			GPIO_Config(dev.channel2->gpio,GPIO_Mode_IPD);
			GPIO_WritePin(dev.channel2->gpio,LOW);  
			TIM_ICInitStructure.TIM_Channel = TIM_Channel_2; //CC1S=01     选择输入端 IC1映射到TI1上  
			TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;    //上升沿捕获  
			TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //映射到TI1上  
			TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;   //配置输入分频,不分频   
			TIM_ICInitStructure.TIM_ICFilter = 0x00;//IC1F=0000 配置输入滤波器 不滤波  
			TIM_ICInit(dev.timer, &TIM_ICInitStructure);  
			TIM_ITConfig(dev.timer,TIM_IT_CC2,ENABLE);//允许更新中断 ,允许CC1IE捕获中断
		}
	}
	if(dev.channel3!=NULL)
	{
		if(dev.channel3->mode == TIM_MODE_PWM)
		{
			GPIO_Config(dev.channel3->gpio,GPIO_Mode_AF_PP);
			TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;                           //配置为PWM模式1  
			TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;                
			TIM_OCInitStructure.TIM_OCPolarity =TIM_OCPolarity_High;                    //当定时器计数值小于CCR1时为高电平  
			TIM_OCInitStructure.TIM_Pulse = 0;                                          //设置跳变值，当计数器计数到这个值时，电平发生跳变  
			TIM_OC3Init(dev.timer, &TIM_OCInitStructure);                               //使能通道1      
			TIM_OC3PreloadConfig(dev.timer, TIM_OCPreload_Enable);  
		}
		else if(dev.channel3->mode == TIM_MODE_CAP)
		{
			GPIO_Config(dev.channel3->gpio,GPIO_Mode_IPD);
			GPIO_WritePin(dev.channel3->gpio,LOW);  
			TIM_ICInitStructure.TIM_Channel = TIM_Channel_3; //CC1S=01     选择输入端 IC1映射到TI1上  
			TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;    //上升沿捕获  
			TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //映射到TI1上  
			TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;   //配置输入分频,不分频   
			TIM_ICInitStructure.TIM_ICFilter = 0x00;//IC1F=0000 配置输入滤波器 不滤波  
			TIM_ICInit(dev.timer, &TIM_ICInitStructure);  
			TIM_ITConfig(dev.timer,TIM_IT_CC3,ENABLE);//允许更新中断 ,允许CC1IE捕获中断
		}
	}
	if(dev.channel4!=NULL)
	{
		if(dev.channel4->mode == TIM_MODE_PWM)
		{
			GPIO_Config(dev.channel4->gpio,GPIO_Mode_AF_PP);
			TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;                           //配置为PWM模式1  
			TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;                
			TIM_OCInitStructure.TIM_OCPolarity =TIM_OCPolarity_High;                    //当定时器计数值小于CCR1时为高电平  
			TIM_OCInitStructure.TIM_Pulse = 0;                                          //设置跳变值，当计数器计数到这个值时，电平发生跳变  
			TIM_OC4Init(dev.timer, &TIM_OCInitStructure);                               //使能通道1      
			TIM_OC4PreloadConfig(dev.timer, TIM_OCPreload_Enable);  
		}
		else if(dev.channel4->mode == TIM_MODE_CAP)
		{
			GPIO_Config(dev.channel4->gpio,GPIO_Mode_IPD);
			GPIO_WritePin(dev.channel4->gpio,LOW);							//下拉
			TIM_ICInitStructure.TIM_Channel = TIM_Channel_4;				//CC1S=01     选择输入端 IC1映射到TI1上  
			TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;		//上升沿捕获  
			TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;	//映射到TI1上  
			TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;			//配置输入分频,不分频   
			TIM_ICInitStructure.TIM_ICFilter = 0x00;						//IC1F=0000 配置输入滤波器 不滤波  
			TIM_ICInit(dev.timer, &TIM_ICInitStructure);  
			TIM_ITConfig(dev.timer,TIM_IT_CC4,ENABLE);						//允许更新中断 ,允许CC1IE捕获中断
		}
	}
	//PWM_Config(dev.timer,0,0,0,50);  
	//TIM_ClearFlag(TIMx, TIM_FLAG_Update);						//清除定时器的溢出标志位
	//TIM_ITConfig(TIMx,TIM_IT_Update,ENABLE);					//使能定时器2溢出中断	//定时器PWM输出       
	//TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);					//允许更新中断 ,允许CC1IE捕获中断															
	TIM_Cmd(dev.timer, ENABLE);									//定时器2使能
} 

/*******************************************************************************
  * @brief  改变频率             
  * @param  None              
  * @retval None              
  * @Note   未实现             
*******************************************************************************/
void Change_F(TIM_TypeDef * TIMx,u16 arr,u16 pre)
{  
	//初始化结构体
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;  

	TIM_TimeBaseStructure.TIM_Period=arr;                   //定时器周期
	TIM_TimeBaseStructure.TIM_Prescaler=pre;                //预分频数
	TIM_TimeBaseInit(TIMx, &TIM_TimeBaseStructure);     

	TIM_Cmd(TIMx, ENABLE);                                   //定时器2使能
}

/*******************************************************************************
  * @brief  PWM配置              
  * @param  TIMx 定时器
			CCR1,CCR2,CCR3,CCR4:四个通道的重装值
  * @retval None              
  * @Note   None              
*******************************************************************************/
void PWM_Config(TIM_TypeDef * TIMx, u16 CCR1,u16 CCR2,u16 CCR3,u16 CCR4)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;  
	TIM_ICInitTypeDef  TIM_ICInitStructure;  

	/* PWM1 Mode configuration: Channel1 */  
	if(CCR1!=0)
	{
		//PWM输出引脚
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 ;       //Channel1
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOB,&GPIO_InitStructure);
	}
	
	
	/* PWM1 Mode configuration: Channel2 */  
	if(CCR2!=0)
	{
		//PWM输出引脚
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 ;       //Channel2
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOB,&GPIO_InitStructure);
		GPIO_ResetBits(GPIOB,GPIO_Pin_9);       
		
		TIM_ICInitStructure.TIM_Channel = TIM_Channel_2; //CC1S=01     选择输入端 IC1映射到TI1上  
		TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;    //上升沿捕获  
		TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //映射到TI1上  
		TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;   //配置输入分频,不分频   
		TIM_ICInitStructure.TIM_ICFilter = 0x00;//IC1F=0000 配置输入滤波器 不滤波  
		TIM_ICInit(TIM4, &TIM_ICInitStructure);  
		TIM_ITConfig(TIM2,TIM_IT_Update|TIM_IT_CC1,ENABLE);//允许更新中断 ,允许CC1IE捕获中断

	}
	
	/* PWM1 Mode configuration: Channel3 */  
	if(CCR3!=0)
	{
		//PWM输出引脚
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 ;       //Channel3
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOB,&GPIO_InitStructure);
		
		TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;                           //配置为PWM模式1  
		TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;                
		TIM_OCInitStructure.TIM_OCPolarity =TIM_OCPolarity_High;                    //当定时器计数值小于CCR1时为高电平  
		TIM_OCInitStructure.TIM_Pulse = CCR3;                                       //设置通道2的电平跳变值，输出另外一个占空比的PWM  
		TIM_OC3Init(TIMx, &TIM_OCInitStructure);                                    //使能通道2  
		TIM_OC3PreloadConfig(TIMx, TIM_OCPreload_Enable);  
	}
	
	/* PWM1 Mode configuration: Channel4 */  
	if(CCR4!=0)
	{
		GPIO_Config(&PB1,GPIO_Mode_AF_PP);
		
		TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;                           //配置为PWM模式1  
		TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;                
		TIM_OCInitStructure.TIM_OCPolarity =TIM_OCPolarity_High;                    //当定时器计数值小于CCR1时为高电平  
		TIM_OCInitStructure.TIM_Pulse = 50;                                       //设置通道2的电平跳变值，输出另外一个占空比的PWM  
		TIM_OC4Init(TIMx, &TIM_OCInitStructure);                                    //使能通道2  
		TIM_OC4PreloadConfig(TIMx, TIM_OCPreload_Enable);  
	}
	
	TIM_CtrlPWMOutputs(TIMx,ENABLE);                                            //MOE 主输出使能        
    TIM_ARRPreloadConfig(TIMx, ENABLE);                                         //使能TIM3重载寄存器ARR  
}

void PWM_SetDuty(TIM_CHANNEL channel, u16 duty)
{
	switch(channel.id)
	{
		case TIM_CH1:
			TIM_SetCompare1(channel.timer,duty);
			break;
		case TIM_CH2:
			TIM_SetCompare2(channel.timer,duty);
			break;
		case TIM_CH3:
			TIM_SetCompare3(channel.timer,duty);
			break;
		case TIM_CH4:
			TIM_SetCompare4(channel.timer,duty);
			break;
	}
}

///*******************************************************************************
//  * @brief  定时器2中断             
//  * @param  None              
//  * @retval None              
//  * @Note   None             
//*******************************************************************************/
//extern u16 speed,lastspeed;

//u8 capstate = 0;
//u8 cnt = 0;
//u32 start,end;
////float speed;
//void TIM2_IRQHandler(void)  
//{   
//	if(TIM_GetITStatus(TIM2,TIM_IT_Update) != RESET)	//发生了捕获中断   定时器计数没有溢出  
//	{  
//		cnt++;
//	}  
//	if(TIM_GetITStatus(TIM2,TIM_IT_CC3) != RESET)		//发生了捕获中断   定时器计数没有溢出  
//	{  
//		if(capstate)
//		{
//			capstate = 0;
//			end = cnt*1000 + TIM_GetCapture3(TIM2);//k次测量值   设定值是多少
//			float pausecnt = (end-start)*10.0f;
//			MOTOR[0].cur_speed = (int)((1/pausecnt)*100000000);

//		}
//		else
//		{
//			start = TIM_GetCapture3(TIM2);	//获取计数值   
//			capstate = 1;
//			cnt =0;
//		}
//		//TIM_OC1PolarityConfig(TIM2,TIM_ICPolarity_Rising);	//设置成上升沿捕获  
//        //TIM_SetCounter(TIM5,0);   							//清空TIM5计数寄存器数值  
//        //TIM_OC1PolarityConfig(TIM5,TIM_ICPolarity_Falling);	// 设置为下降沿捕获  
//	}  
//	TIM_ClearITPendingBit(TIM2, TIM_IT_Update | TIM_IT_CC3);
//}
/*********************************END OF FILE**********************************/
