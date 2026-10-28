#include	"stm32f10x.h"                  // Device header
#include	"OLED.h"
#include	"PWM.h"
#include	"Motor.h"
#include	"Delay.h"
#include	"SERVO.h"


int main(void)
{
		PWM_Init();
		Motor_Init();
		OLED_Init();
		Servo_Init();
	
		
		
	
	while(1)
	{
		
		Servo_Angle(0);
		Delay_ms(500);
		Servo_Angle(120);
		Delay_ms(500);
		
		
//		Motor_L_Speed(50);
//		Delay_s(2);
//		Motor_R_Speed(50);
//		Delay_s(2);

	}
		
}
