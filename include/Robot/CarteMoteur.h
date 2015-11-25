/*
 * CarteMoteur.h
 *
 *  Created on: 18 août 2015
 *      Author: jul
 */

#include "Driver/Gpio.h"
#include "Driver/PWM.h"

#ifndef CARTEMOTEUR_H_
#define CARTEMOTEUR_H_

typedef enum MOTOR
{
	MLeft	 	= 0,
	MRight 		= 1
};


class CarteMoteur {

protected:
	PWM *	m_pEn1;
	Gpio *	m_pMn1;
	PWM *	m_pEn2;
	Gpio *	m_pMn2;
public:
	CarteMoteur(){};
	~CarteMoteur(){};
	void Set(PWM *	En1,Gpio *	Mn1, PWM *	En2,Gpio *	Mn2){};
	void Forward(MOTOR m){};
	void Backward(MOTOR m){};
	void SetSpeed(MOTOR m, double Speed){};
	void Stop(MOTOR m){};


};

#endif /* CARTEMOTEUR_H_ */
