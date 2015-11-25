/*
 * TB6612FNG.h
 *
 *  Created on: 20 août 2015
 *      Author: jul
 */

#ifndef TB6612FNG_H_
#define TB6612FNG_H_

#include "Robot/CarteMoteur.h"

class TB6612FNG: public CarteMoteur {

private :

	Gpio *	m_pMn1B;

	Gpio *	m_pMn2B;

	Gpio *	m_pStandBy;

	void TB6612FNG_MLeft_Forward();
	void TB6612FNG_MLeft_Backward();
	void TB6612FNG_MLeft_SetSpeed(float Speed);

	void TB6612FNG_MRight_Forward();
	void TB6612FNG_MRight_Backward();
	void TB6612FNG_MRight_SetSpeed(float Speed);

	void TB6612FNG_MRight_Break();
	void TB6612FNG_MLeft_Break();

public:
	TB6612FNG();
	~TB6612FNG();

	void Set(PWM *	En1,Gpio *	Mn1, PWM *	En2,Gpio *	Mn2);
	void Set(PWM *	En1, Gpio *	Mn1, Gpio *	Mn1B, PWM *	En2, Gpio *	Mn2, Gpio *	Mn2B, Gpio * Standby);
	void Forward(MOTOR m);
	void Backward(MOTOR m);
	void SetSpeed(MOTOR m, float Speed);
	void Stop(MOTOR m);
};

#endif /* TB6612FNG_H_ */
