



#include "objet.h"
#include "Gpio.h"

Gpio::Gpio()
{
	m_GPIO_InitStructure.Pin = 0;
	m_GPIOx = 0;
	m_init = false;
	//m_PINSource = 0;
}
Gpio::Gpio(GPIO_TypeDef* GPIOx,uint32_t GPIO_Pin,uint32_t GPIO_Mode, uint32_t GPIO_Alternate, uint32_t GPIO_Speed,uint32_t GPIO_PuPd)
{
	if(0 != GPIOx )
	{
		m_GPIOx = GPIOx;
	}
	m_GPIO_InitStructure.Pin = GPIO_Pin;
	m_GPIO_InitStructure.Mode = GPIO_Mode;
	m_GPIO_InitStructure.Alternate= GPIO_Alternate;
	m_GPIO_InitStructure.Pull = GPIO_PuPd;
	m_GPIO_InitStructure.Speed = GPIO_Speed;

	//m_PINSource = PINSource;
	m_init = false;
}

bool Gpio::Set(GPIO_TypeDef* GPIOx,uint32_t GPIO_Pin,uint32_t GPIO_Mode,uint32_t GPIO_Alternate, uint32_t GPIO_Speed,uint32_t GPIO_PuPd)
{
	m_GPIO_InitStructure.Pin = GPIO_Pin;
	m_GPIO_InitStructure.Mode = GPIO_Mode;
	m_GPIO_InitStructure.Alternate= GPIO_Alternate;
	m_GPIO_InitStructure.Pull = GPIO_PuPd;
	m_GPIO_InitStructure.Speed = GPIO_Speed;

	if(0 == GPIOx)
	{
		return false;
	}

	m_GPIOx = GPIOx;
	//m_PINSource = PINSource;
	return true;
}

bool Gpio::Init()
{

	if(m_GPIO_InitStructure.Pin != 0 && m_GPIOx != 0 )
	{
		HAL_GPIO_Init(m_GPIOx, &m_GPIO_InitStructure);
		m_init = true;
		return true;
	}

	return false;
}
bool Gpio::Toggle()
{
	if(m_init)
	{
		HAL_GPIO_TogglePin(m_GPIOx,m_GPIO_InitStructure.Pin);
		return true;
	}
	return false;
}

bool Gpio::WriteBit(GPIO_PinState BitVal)
{
	if(m_init)
	{
		HAL_GPIO_WritePin(m_GPIOx,m_GPIO_InitStructure.Pin,BitVal);
		return true;
	}
	return false;
}

void Gpio::CallbackInteruption(uint8_t NVIC_IRQChannel)
{
	while(true);
}
