#ifndef __HCSOR_H
#define __HCSOR_H

void HCSOR_Init(void);
void TIM4_Init(void);
void TIM4_IRQHandler(void);
void HCSOR_Start(void);
uint16_t HCSR04_GetValue(void);

#endif

