
#ifndef __GPIO_H
#define __GPIO_H


#include "stm32f4xx_hal_gpio.h"
#include "objet.h"

class Gpio : public objet
{
public:
	GPIO_InitTypeDef m_GPIO_InitStructure;
	GPIO_TypeDef* m_GPIOx;
	//uint8_t m_PINSource;
	bool m_init;

	Gpio();
	Gpio(GPIO_TypeDef* GPIOx,uint32_t GPIO_Pin,uint32_t GPIO_Mode,uint32_t GPIO_Alternate, uint32_t GPIO_Speed,uint32_t GPIO_PuPd);
	~Gpio(){};
	bool Set(GPIO_TypeDef* GPIOx,uint32_t GPIO_Pin,uint32_t GPIO_Mode,uint32_t GPIO_Alternate, uint32_t GPIO_Speed,uint32_t GPIO_PuPd);
	bool Init();
	bool WriteBit(GPIO_PinState BitVal);
	void CallbackInteruption(uint8_t NVIC_IRQChannel);
	bool Toggle();

};



#endif






