#include "stm32f10x.h"                  // Device header
#include	"Delay.h"
#include	"Motor.h"
#include	"Servo.h"
#include	"HCSOR04.h"

/* 当前 main.c 未启用避障，本文件为备用控制层。
 * 注意：Get_Data() 里 3 次测距 + 3 次 200ms 延时 ≈ 1s 完全不控车，
 * 启用前务必确认场地安全。 */

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

		Servo_Angle(50);          /* 测完回中，别让舵机卡在一边 */
}

void Scan_HCSOR(void)
{
		if (Servo_M > 0 && Servo_M <= 15)          /* 原来误写成 Servo_M<<15 */
		{
				Motor_Stop(0);
				Get_Data();

			if (Servo_L > Servo_R)                 /* 原来误写成 >> */
			{
					Motor_Down_Speed(50);
					Delay_ms(400);
					Motor_L_Speed(50);
					Delay_ms(400);
					Motor_Speed(50);
			}
			else if (Servo_L < Servo_R)            /* 原来误写成 << */
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
