#include "stm32f10x.h"                  // Device header
#include	"PWM.h"


void Servo_Init(void)
{
		PWM_Init();
}


void Servo_Angle(float Angle)
{
		PWM_SERVOCompare(Angle / 180 *2000 +500);
}

