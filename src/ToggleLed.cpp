/*
 * TogleLedRedBlue.cpp
 *
 *  Created on: 24 mai 2016
 *      Author: jul
 */

#include "ToggleLed.h"

ToggleLed::ToggleLed(char * name) :Task(name,osPriorityNormal,0,200)
{
	// TODO Auto-generated constructor stub

}

ToggleLed::~ToggleLed() {
	// TODO Auto-generated destructor stub
}


void ToggleLed::Init(Gpio * Led1,Gpio *Led2, uint32_t delay)
{
	Task::Init();
	m_Led1 =Led1;
	m_Led2 = Led2;
	m_Delay = delay;

	m_Led1->WriteBit(GPIO_PIN_RESET);
	m_Led2->WriteBit(GPIO_PIN_RESET);


}

void ToggleLed::Thread(void const * argument)
{
	while(1)
	{
		m_Led1->Toggle();
		m_Led2->Toggle();
		osDelay(m_Delay);
	}
}
