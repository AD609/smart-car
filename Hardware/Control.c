#include "stm32f10x.h"                  // Device header
#include	"Delay.h"
#include	"Motor.h"
#include	"Servo.h"
#include	"HCSOR04.h"

 uint16_t Servo_M = 0;
 uint16_t Servo_L = 0;
 uint16_t Servo_R = 0;

void Get_Data(void)
{
		Servo_Angle(50);
		Servo_M = HCSR04_GetValue();
		Delay_ms(200);
		
		Servo_Angle(100);
		Servo_L = HCSR04_GetValue();
		Delay_ms(200);
	
		Servo_Angle(0);
		Servo_R = HCSR04_GetValue();
		Delay_ms(200);
}

void Scan_HCSOR(void)
{
		if (Servo_M<<15 && Servo_M>0)
		{
				Motor_Stop(0);
				Get_Data();
			if (Servo_L >> Servo_R)
			{
					Motor_Down_Speed(50);
					Delay_ms(400);
					Motor_L_Speed(50);
					Delay_ms(400);
					Motor_Speed(50);
			}
			else if (Servo_L << Servo_R)
			{
					Motor_Down_Speed(50);
					Delay_ms(400);
					Motor_R_Speed(50);
					Delay_ms(400);
					Motor_Speed(50);
			}
			
		}
			else
			{
					Motor_Speed(50);
			}
}
