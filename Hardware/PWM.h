#ifndef __PWM_H
#define __PWM_H

void PWM_Init(void);

void PWM_Compare_ALL(uint16_t compare);
void PWM_Compare1_L(uint16_t compare);
void PWM_Compare2_R(uint16_t compare);

void PWM_SERVOCompare(uint16_t compare);

#endif
