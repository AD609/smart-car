#include "stm32f10x.h"                  // Device header
#include "TCRT5000.h"
#include "Motor.h"

extern uint8_t value;

void Follow_car(void)
{
		if (value == 0)
			{
				Motor_Stop(0);
			}
			if (value == 10)
			{
				Motor_Speed(90);
			}
			else if ( value == 8)
			{
				Motor_Differential(90,50);
				
			}
			else if ( value == 2)
			{
				Motor_Differential(50,90);
			}

}

