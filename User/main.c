#include	"stm32f10x.h"                  // Device header
#include	"OLED.h"
#include 	"TCRT5000.h"
//#include	"PWM.h"
#include	"Motor.h"
//#include	"Delay.h"
//#include	"SERVO.h"
//#include	"HCSOR04.h"
#include	"Follow.h"
#include 	"Serial.h"

//extern uint16_t Time;    //HCSOR04.c 里的原始计数，用来算 0.1cm 位
//uint16_t  distance;

//extern	uint16_t Servo_M ;
//extern	uint16_t Servo_L ;
//extern	uint16_t Servo_R ;

//extern uint8_t value;
extern uint8_t RxData;

int main(void)
{

	OLED_Init();
//	OLED_ShowString(1,1,"s");      // 固定字符只刷一次
//	HCRT500_Init();
	Motor_Init();                  // 内部已调 PWM_Init，不用重复调
	Serial_Init();
	
	
	while(1)
	{
		switch(RxData)
		{
			case 'f':
			Motor_Speed(50);
			break ;
			
			case 'd':
			Motor_Speed(-50);
			break ;
			
			case 'l':
			Motor_Differential(30,50);
			break ;
			
			case 'r':
			Motor_Differential(50,30);	
			break ;
			
			case 's':
			Motor_Differential(0,0);	
			break ;
		}
	}

}
