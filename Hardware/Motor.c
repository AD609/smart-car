#include "stm32f10x.h"                  // Device header
#include	"PWM.h"

int8_t s_speed,l_speed,r_spped;


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

void Motor_Speed(int8_t Straight_Speed)
{
	if (Straight_Speed > 0)
	{
		GPIO_SetBits(GPIOB,GPIO_Pin_5 |GPIO_Pin_7);
		GPIO_ResetBits(GPIOB,GPIO_Pin_6 |GPIO_Pin_8);
		PWM_Compare_ALL(Straight_Speed);
		
	}
//	else 
//	{
//		GPIO_SetBits(GPIOB,GPIO_Pin_6 |GPIO_Pin_8);
//		GPIO_ResetBits(GPIOB,GPIO_Pin_5 |GPIO_Pin_7);
//		PWM_Compare_ALL(-Straight_Speed);
//	}

}

void Motor_Down_Speed(int8_t Down_Speed)
{
		GPIO_SetBits(GPIOB,GPIO_Pin_6 |GPIO_Pin_8);
		GPIO_ResetBits(GPIOB,GPIO_Pin_5 |GPIO_Pin_7);
		PWM_Compare_ALL(Down_Speed);
}


void Motor_L_Speed(int8_t L_Speed)
{
	if (L_Speed > 0)
	{
		GPIO_SetBits(GPIOB, GPIO_Pin_5);
		GPIO_ResetBits(GPIOB, GPIO_Pin_6);
		PWM_Compare2_R(L_Speed);
	}
	else if (L_Speed < 0)
	{
		GPIO_SetBits(GPIOB, GPIO_Pin_6);
		GPIO_ResetBits(GPIOB, GPIO_Pin_5);
		PWM_Compare2_R((-L_Speed));
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
		GPIO_SetBits(GPIOB, GPIO_Pin_7);
		GPIO_ResetBits(GPIOB, GPIO_Pin_8);
		PWM_Compare1_L(R_Speed);
	}
	else if (R_Speed < 0)
	{
		GPIO_SetBits(GPIOB, GPIO_Pin_8);
		GPIO_ResetBits(GPIOB, GPIO_Pin_7);
		PWM_Compare1_L(-R_Speed);
	}
	else
	{
		GPIO_SetBits(GPIOB, GPIO_Pin_7 | GPIO_Pin_8);
		PWM_Compare1_L(0);
	}
}

void Motor_Differential(int16_t left, int16_t right)
{
		Motor_L_Speed(left);
		Motor_R_Speed(right);
}


void Motor_Stop(int8_t Speed)
{
		
		PWM_Compare_ALL(0);
}









