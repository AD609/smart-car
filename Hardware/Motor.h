#ifndef __MOTOR_H
#define __MOTOR_H

void Motor_Init(void);

void Motor_Speed(int8_t Straight_Speed);
void Motor_Down_Speed(int8_t Down_Speed);
void Motor_L_Speed(int8_t L_Speed);
void Motor_R_Speed(int8_t R_Speed);
void Motor_Differential(int16_t left, int16_t right);
void Motor_Stop(int8_t Speed);
#endif
