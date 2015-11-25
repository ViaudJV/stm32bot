#include "stm32f4xx_hal.h"

#ifndef __OBJET_DRIVER_H
#define __OBJET_DRIVER_H


class objet
{
public:
	objet(){};
	~objet(){};
	virtual void CallbackInteruption(void * Handle){while(1);};
};



#endif






