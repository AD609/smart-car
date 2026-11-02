#include "stm32f10x.h"                  // Device header

#include	"Delay.h"
#include "HCSOR04.h"

uint16_t  Time;

void TIM4_Init(void)
{
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);

			TIM_InternalClockConfig(TIM4);                       

			TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
			TIM_TimeBaseInitStructure.TIM_ClockDivision =  TIM_CKD_DIV1;
			TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
			TIM_TimeBaseInitStructure.TIM_Period = 7199;         //ARR: 7200/72MHz = 0.1ms/tick
			TIM_TimeBaseInitStructure.TIM_Prescaler = 0;         //PSC
			TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
			TIM_TimeBaseInit(TIM4,&TIM_TimeBaseInitStructure);

			TIM_ClearFlag(TIM4, TIM_FLAG_Update);                //清除TimeBaseInit置位的残留标志
			TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE);

			NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

			NVIC_InitTypeDef NVIC_InitStructure;
			NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;
			NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
			NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
			NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
			NVIC_Init(&NVIC_InitStructure);

	    TIM_Cmd(TIM4, ENABLE);                             
}

void TIM4_IRQHandler(void)
{
			if (TIM_GetITStatus(TIM4,TIM_IT_Update) == SET)
			{
				if (GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_5) == 1)
				{
					Time ++ ;
				}
				TIM_ClearITPendingBit(TIM4,TIM_IT_Update);
			}

}

void HCSOR_Init(void)
{		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);

		GPIO_InitTypeDef GPIO_InitStructure;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOA,&GPIO_InitStructure);

		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOA,&GPIO_InitStructure);

		GPIO_ResetBits(GPIOA,GPIO_Pin_4);

}

void HCSOR_Start(void)
{                              
		GPIO_SetBits(GPIOA,GPIO_Pin_4);
		Delay_us(15);                                         //触发脉宽15us(模块要求>=10us)
		GPIO_ResetBits(GPIOA,GPIO_Pin_4);
		
		Time = 0;
		TIM4_Init();     
}

uint16_t HCSR04_GetValue(void)
{
    HCSOR_Start();
    Delay_ms(60);                        //等待测量完成(同时满足60ms最小间隔)
    TIM_Cmd(TIM4, DISABLE);

    if(Time > 235)
	{
		Time = 0;                         //0.1ms计数下超过235(23.5ms)=超4m无回波
		return 0;
	}
    return ((Time * 0.0001f) * 34000) / 2;              //Time*1.7 = cm（整数运算）
}
