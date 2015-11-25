/*
 * L298PTwinV11.h
 *
 *  Created on: 2 août 2015
 *      Author: jul
 */

#ifndef L298PTWINV11_H_
#define L298PTWINV11_H_

#include "Driver/PWM.h"
#include "Driver/Gpio.h"


#include "Robot/CarteMoteur.h"



class L298PTwinV11 : public CarteMoteur{
private:

	void L298PTwinV11_MLeft_Forward();
	void L298PTwinV11_MLeft_Backward();
	void L298PTwinV11_MLeft_SetSpeed(float Speed);

	void L298PTwinV11_MRight_Forward();
	void L298PTwinV11_MRight_Backward();
	void L298PTwinV11_MRight_SetSpeed(float Speed);
public:
	L298PTwinV11();
	~L298PTwinV11();
	void Set(PWM *	En1,Gpio *	Mn1, PWM *	En2,Gpio *	Mn2);
	void Forward(MOTOR m);
	void Backward(MOTOR m);
	void SetSpeed(MOTOR m, float Speed);
};

#endif /* L298PTWINV11_H_ */
