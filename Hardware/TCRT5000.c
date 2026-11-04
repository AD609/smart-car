#include "stm32f10x.h"                  // Device header

uint8_t value = 0;


void HCRT500_Init(void)
{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
		GPIO_InitTypeDef GPIO_InitStructure;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_10 | GPIO_Pin_11;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOB,&GPIO_InitStructure);
	
}

uint8_t Read_HCRT(void)
{
	uint16_t s = 0;
	
		if ( GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_0) == SET) 
		 {
		   s |=0x01;
		 }
		if ( GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1) == SET) 
	   {
		   s |=0x02;
		 }
		if ( GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_10) == SET) 
		 {
		   s |=0x04;
		 }
		if ( GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11) == SET) 
		 {
		   s |=0x08;
		 }
	
	   value = s;

		return value;
}

