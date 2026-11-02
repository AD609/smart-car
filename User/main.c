#include	"stm32f10x.h"                  // Device header
#include	"OLED.h"
#include	"PWM.h"
#include	"Motor.h"
#include	"Delay.h"
#include	"SERVO.h"
#include	"HCSOR04.h"
#include	"Control.h"

extern uint16_t Time;    //HCSOR04.c 里的原始计数，用来算 0.1cm 位
uint16_t  distance;

extern	uint16_t Servo_M ;
extern	uint16_t Servo_L ;
extern	uint16_t Servo_R ;


int main(void)
{
		PWM_Init();
		Motor_Init();
		OLED_Init();
		Servo_Init();
		HCSOR_Init();

		 
	
		OLED_ShowString(1,1,"dis:");
		OLED_ShowString(1,7,".");
		OLED_ShowString(1,10,"cm");
	
		
		
	while(1)
	{
			distance = HCSR04_GetValue();
			OLED_ShowNum(1,5,distance,2);
			OLED_ShowNum(1,8,(distance*10)%100,2);
			OLED_ShowNum(2,1,distance,2);
		
			Servo_Angle(50 );
			Motor_Speed(80);
		  Servo_M = HCSR04_GetValue();

	
		if (Servo_M<=15 && Servo_M>0)
		{
			
				Motor_Stop(0);
				Get_Data();
			
			if (Servo_L >= Servo_R)
			{
					Motor_Down_Speed(80);
					Delay_ms(400);
					Motor_L_Speed(80);
					Delay_ms(400);

			}
			else 
			{
					Motor_Down_Speed(80);
					Delay_ms(400);
					Motor_R_Speed(80);
					Delay_ms(400);
			}
					Motor_Speed(80);
			 
  	}
			else
			{
				Motor_Speed(80);
			}
  }
}
