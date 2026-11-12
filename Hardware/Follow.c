#include "stm32f10x.h"                  // Device header
#include "TCRT5000.h"
#include "Motor.h"
#include "Delay.h"

extern uint8_t value;


void Follow_car(void)
{
	if ( value == 9)
	{
		Motor_Speed(50);
	}
	if (value == 14 || value == 12 || value == 13)
	{
	  Motor_Differential(0,50);
	}
	if (value == 7 ||value ==3 || value == 11)
	{
		Motor_Differential(50,0);
	}
	if (value == 8)
	{
		if (value == 8)
{
		Delay_ms(100);
		Motor_Stop(0);
    Motor_Differential(-50, 50);   
    Delay_ms(600);                                 
    Read_HCRT();                   
}
	}
	if (value == 1)
	{
		Delay_ms(100);  
		Motor_Stop(0); 
		Motor_Differential(50, -50);   
    Delay_ms(600);                                  
    Read_HCRT(); 
	}
	if (value == 0 | value == 15)
	{
		Motor_Stop(0);
	}
	
}
