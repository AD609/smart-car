#include "stm32f10x.h"                  // Device header

void PWM_Init(void)
{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);

		
		GPIO_InitTypeDef GPIO_InitStructure;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7 |GPIO_Pin_0;
	  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOA,&GPIO_InitStructure);
	
		TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	
		TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
		TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
		TIM_TimeBaseInitStructure.TIM_Period = 100-1;   //arr的值
		TIM_TimeBaseInitStructure.TIM_Prescaler = 72-1; //psc的值
		TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0; //重复计数器，只用于高级定时器
		TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure);
	
		TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
		TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
		TIM_TimeBaseInitStructure.TIM_Period = 20000 - 1;   //arr的值
		TIM_TimeBaseInitStructure.TIM_Prescaler = 72-1; //psc的值
		TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0; //重复计数器，只用于高级定时器
		TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStructure);

	
		TIM_OCInitTypeDef TIM_OCInitStructure;
		TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
		TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
		TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
		TIM_OCInitStructure.TIM_Pulse = 0;
		TIM_OC1Init(TIM3,&TIM_OCInitStructure);
		
		
		TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
		TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
		TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
		TIM_OCInitStructure.TIM_Pulse = 0;
		TIM_OC2Init(TIM3,&TIM_OCInitStructure);
		
		TIM_OCInitTypeDef TIM_OCInitStrucure;
		TIM_OCInitStrucure.TIM_OCMode = TIM_OCMode_PWM1;
		TIM_OCInitStrucure.TIM_OCPolarity = TIM_OCPolarity_High;
		TIM_OCInitStrucure.TIM_OutputState = TIM_OutputState_Enable;
		TIM_OCInitStrucure.TIM_Pulse = 0;
		TIM_OC1Init(TIM2,&TIM_OCInitStrucure);
		
		
		TIM_Cmd(TIM3,ENABLE);
		TIM_Cmd(TIM2,ENABLE);

}

void PWM_Compare_ALL(uint16_t compare)
{
		TIM_SetCompare1(TIM3,compare);
		TIM_SetCompare2(TIM3,compare);
}

void PWM_Compare1_L(uint16_t compare)
{
		TIM_SetCompare1(TIM3,compare);
	
}

void PWM_Compare2_R(uint16_t compare)
{
		TIM_SetCompare2(TIM3,compare);
	
}

void PWM_SERVOCompare(uint16_t compare)
{
		TIM_SetCompare1(TIM2,compare);
	
}

















