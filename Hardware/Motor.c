#include "stm32f10x.h"                  // Device header
#include	"PWM.h"

void Motor_Init(void)
{
	PWM_Init();
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
  GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 |GPIO_Pin_6 |GPIO_Pin_7 |GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);

}

void Motor_Speed(int8_t Speed)
{
	if (Speed > 0)
	{
		GPIO_SetBits(GPIOB,GPIO_Pin_5 |GPIO_Pin_7);
		GPIO_ResetBits(GPIOB,GPIO_Pin_6 |GPIO_Pin_8);
		PWM_Compare_ALL(Speed);
		
	}
	else 
	{
		GPIO_SetBits(GPIOB,GPIO_Pin_6 |GPIO_Pin_8);
		GPIO_ResetBits(GPIOB,GPIO_Pin_5 |GPIO_Pin_7);
		PWM_Compare_ALL(-Speed);
	}

}

void Motor_L_Speed(int8_t Speed)
{
	if (Speed > 0)
	{
		GPIO_ResetBits(GPIOA, GPIO_Pin_7); // PWMA (A7) 输出低电平 (0% 占空比)
		GPIO_ResetBits(GPIOB, GPIO_Pin_5); // AIN1 (B5) 低电平
		GPIO_ResetBits(GPIOB, GPIO_Pin_6); // AIN2 (B6) 低电平
		
		GPIO_SetBits(GPIOB,GPIO_Pin_7);
		GPIO_ResetBits(GPIOB,GPIO_Pin_8);
		PWM_Compare_ALL(Speed);

	}
}
	 
void Motor_R_Speed(int8_t Speed)
{
	if (Speed > 0)
	{
		GPIO_ResetBits(GPIOA, GPIO_Pin_6); // PWMB (A6) 输出低电平 (0% 占空比)
		GPIO_ResetBits(GPIOB, GPIO_Pin_7); // AIN1 (B7) 低电平
		GPIO_ResetBits(GPIOB, GPIO_Pin_8); // AIN2 (B8) 低电平
		
		
		GPIO_SetBits(GPIOB,GPIO_Pin_5 );
		GPIO_ResetBits(GPIOB,GPIO_Pin_6);
		PWM_Compare_ALL(Speed);
	}
}
