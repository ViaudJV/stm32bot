/*
 * TogleLedRedBlue.h
 *
 *  Created on: 24 mai 2016
 *      Author: jul
 */

#ifndef TOGLELEDREDBLUE_H_
#define TOGLELEDREDBLUE_H_
#include "Driver/Gpio.h"
#include <Middleware/Task.h>

class ToggleLed: public Task {
public:
	ToggleLed(char * name);
	virtual ~ToggleLed();
	void Init(Gpio * Led1,Gpio *Led2, uint32_t delay);
	void Thread(void const * argument);
	Gpio *m_Led1;
	Gpio *m_Led2;
	uint32_t m_Delay;
};


#endif /* TOGLELEDREDBLUE_H_ */
