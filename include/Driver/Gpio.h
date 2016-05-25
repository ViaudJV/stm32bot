
#ifndef __GPIO_H
#define __GPIO_H



#include "objet.h"
#include "stm32f4xx_hal.h"
class Gpio : public objet
{
public:
	GPIO_InitTypeDef m_GPIO_InitStructure;
	GPIO_TypeDef* m_GPIOx;
	bool m_init;

	Gpio();
	Gpio(GPIO_TypeDef* GPIOx,uint32_t GPIO_Pin,uint32_t GPIO_Mode,uint32_t GPIO_Alternate, uint32_t GPIO_Speed,uint32_t GPIO_PuPd);
	~Gpio(){};
	bool Set(GPIO_TypeDef* GPIOx,uint32_t GPIO_Pin,uint32_t GPIO_Mode,uint32_t GPIO_Alternate, uint32_t GPIO_Speed,uint32_t GPIO_PuPd);
	bool Init();
	bool WriteBit(GPIO_PinState BitVal);
	void CallbackInteruption(void * Handle);
	bool Toggle();

};



#endif






