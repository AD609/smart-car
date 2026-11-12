#include "stm32f10x.h"                  // Device header
#include	"PWM.h"
#include	"Motor.h"



void Motor_Init(void)
{
	PWM_Init();
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	GPIO_SetBits(GPIOB, GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8);
	PWM_Compare_ALL(0);
}



void Motor_Speed(int8_t Straight_Speed)
{
	if (Straight_Speed > 0)
	{
		GPIO_SetBits(GPIOB,   GPIO_Pin_5 | GPIO_Pin_7);
		GPIO_ResetBits(GPIOB, GPIO_Pin_6 | GPIO_Pin_8);
		PWM_Compare_ALL((uint16_t)Straight_Speed);
	}
	else if (Straight_Speed < 0)
	{
		GPIO_SetBits(GPIOB,   GPIO_Pin_6 | GPIO_Pin_8);
		GPIO_ResetBits(GPIOB, GPIO_Pin_5 | GPIO_Pin_7);
		PWM_Compare_ALL((uint16_t)(-Straight_Speed));
	}
	else
	{
		Motor_Stop(0);
	}
}


void Motor_Down_Speed(int8_t Down_Speed)
{
	if (Down_Speed <= 0)
	{
		Motor_Stop(0);
		return;
	}
	GPIO_SetBits(GPIOB,   GPIO_Pin_6 | GPIO_Pin_8);
	GPIO_ResetBits(GPIOB, GPIO_Pin_5 | GPIO_Pin_7);
	PWM_Compare_ALL((uint16_t)Down_Speed);
}



void Motor_L_Speed(int8_t L_Speed)
{
	if (L_Speed > 0)
	{
		GPIO_SetBits(GPIOB,   GPIO_Pin_5);
		GPIO_ResetBits(GPIOB, GPIO_Pin_6);
		PWM_Compare2_R((uint16_t)L_Speed);
	}
	else if (L_Speed < 0)
	{
		GPIO_SetBits(GPIOB,   GPIO_Pin_6);
		GPIO_ResetBits(GPIOB, GPIO_Pin_5);
		PWM_Compare2_R((uint16_t)(-L_Speed));
	}
	else
	{
		GPIO_SetBits(GPIOB, GPIO_Pin_5 | GPIO_Pin_6);   
		PWM_Compare2_R(0);
	}
}


void Motor_R_Speed(int8_t R_Speed)
{
	if (R_Speed > 0)
	{
		GPIO_SetBits(GPIOB,   GPIO_Pin_7);
		GPIO_ResetBits(GPIOB, GPIO_Pin_8);
		PWM_Compare1_L((uint16_t)R_Speed);
	}
	else if (R_Speed < 0)
	{
		GPIO_SetBits(GPIOB,   GPIO_Pin_8);
		GPIO_ResetBits(GPIOB, GPIO_Pin_7);
		PWM_Compare1_L((uint16_t)(-R_Speed));
	}
	else
	{
		GPIO_SetBits(GPIOB, GPIO_Pin_7 | GPIO_Pin_8);   /* 短接制动 */
		PWM_Compare1_L(0);
	}
}



void Motor_Differential(int16_t left, int16_t right)
{

	if (left  >  100) left  =  100;
	if (left  < -100) left  = -100;
	if (right >  100) right =  100;
	if (right < -100) right = -100;

	Motor_L_Speed((int8_t)left);
	Motor_R_Speed((int8_t)right);
}


void Motor_Stop(int8_t Speed)
{
	(void)Speed;
	GPIO_SetBits(GPIOB, GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8);
	PWM_Compare_ALL(0);
}
