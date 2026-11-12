#include "stm32f10x.h"                  // Device header

/* bit0=PB1  bit1=PB0  bit2=PB10  bit3=PB11，白=1 黑=0
 * 居中压线 value=9，全白 15，全黑 0 */
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
		uint8_t s = 0;
		if (GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1))  s |= 0x01;
		if (GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_0))  s |= 0x02;
		if (GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_10)) s |= 0x04;
		if (GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11)) s |= 0x08;
		value = s;
		return value;
}
