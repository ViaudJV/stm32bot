/*
 * L298PTwinV11.cpp
 *
 *  Created on: 2 août 2015
 *      Author: jul
 */

#include "Robot/L298PTwinV11.h"

L298PTwinV11::L298PTwinV11() {
	// TODO Auto-generated constructor stub

	m_pEn1 = 0;
	m_pMn1 = 0;

	m_pEn2 = 0;
	m_pMn2 = 0;
}


L298PTwinV11::~L298PTwinV11() {
	// TODO Auto-generated destructor stub
}



void L298PTwinV11::Set(PWM *	En1,Gpio *	Mn1,PWM *	En2,Gpio *	Mn2)
{
	if(En1 != 0
	   && Mn1 != 0)
	{
		m_pEn1 = En1;
		m_pMn1 = Mn1;
	}

	if(En2 != 0
	   && Mn2 != 0)
	{
		m_pEn2 = En2;
		m_pMn2 = Mn2;
	}

}

void L298PTwinV11::Forward(MOTOR m)
{
	switch(m)
	{
	case MLeft:
		L298PTwinV11_MLeft_Forward();
		break;
	case MRight:
		L298PTwinV11_MRight_Forward();
		break;
	default:
		break;
	}
}

void L298PTwinV11::Backward(MOTOR m)
{
	switch(m)
	{
	case MLeft:
		L298PTwinV11_MLeft_Backward();
		break;
	case MRight:
		L298PTwinV11_MRight_Backward();
		break;
	default:
		break;
	}
}



void L298PTwinV11::SetSpeed(MOTOR m,float Speed)
{
	if(Speed < 100 )
	{
		switch(m)
		{
		case MLeft:
			L298PTwinV11_MLeft_SetSpeed(Speed);
			break;
		case MRight:
			L298PTwinV11_MRight_SetSpeed(Speed);
			break;
		default:
			break;
		}



	}
}

void L298PTwinV11::L298PTwinV11_MLeft_Forward()
{
	m_pMn1->WriteBit(GPIO_PIN_SET);

}

void L298PTwinV11::L298PTwinV11_MLeft_Backward()
{
	m_pMn1->WriteBit(GPIO_PIN_RESET);

}



void L298PTwinV11::L298PTwinV11_MLeft_SetSpeed(float Speed)
{
	if(Speed < 100.0f )
	{
		m_pEn1->UpdateDutyCycle(Speed);
	}
}



void L298PTwinV11::L298PTwinV11_MRight_Forward()
{
	m_pMn2->WriteBit(GPIO_PIN_SET);
}

void L298PTwinV11::L298PTwinV11_MRight_Backward()
{
	m_pMn2->WriteBit(GPIO_PIN_RESET);
}



void L298PTwinV11::L298PTwinV11_MRight_SetSpeed(float Speed)
{
	m_pEn2->UpdateDutyCycle(Speed);
}



