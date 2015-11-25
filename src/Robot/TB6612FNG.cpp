/*
 * TB6612FNG.cpp
 *
 *  Created on: 20 août 2015
 *      Author: jul
 */

#include "Robot/TB6612FNG.h"





TB6612FNG::TB6612FNG() {
	// TODO Auto-generated constructor stub

	m_pEn1 = 0;
	m_pMn1 = 0;
	m_pMn1B = 0;

	m_pEn2 = 0;
	m_pMn2 = 0;
	m_pMn2B = 0;

	m_pStandBy = 0;


}


TB6612FNG::~TB6612FNG() {
	// TODO Auto-generated destructor stub
}

void TB6612FNG::Set(PWM *	En1, Gpio *	Mn1, Gpio *	Mn1B, PWM *	En2, Gpio *	Mn2, Gpio *	Mn2B, Gpio * StandBy)
{
	if(En1 != 0
	   && Mn1 != 0
	   &&  Mn1B != 0)
	{
		m_pEn1 = En1;
		m_pMn1 = Mn1;
	}

	if(En2 != 0
	   && Mn2 != 0
	   &&  Mn2B != 0)
	{
		m_pEn2 = En2;
		m_pMn2 = Mn2;
	}

	if(StandBy != 0 )
	{
		m_pStandBy = StandBy;
	}
}

void TB6612FNG::Set(PWM *	En1,Gpio *	Mn1,PWM *	En2,Gpio *	Mn2)
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

void TB6612FNG::Forward(MOTOR m)
{
	switch(m)
	{
	case MLeft:
		TB6612FNG_MLeft_Forward();
		break;
	case MRight:
		TB6612FNG_MRight_Forward();
		break;
	default:
		break;
	}
}

void TB6612FNG::Backward(MOTOR m)
{
	switch(m)
	{
	case MLeft:
		TB6612FNG_MLeft_Backward();
		break;
	case MRight:
		TB6612FNG_MRight_Backward();
		break;
	default:
		break;
	}
}



void TB6612FNG::SetSpeed(MOTOR m,float Speed)
{
	if(Speed < 100 )
	{
		switch(m)
		{
		case MLeft:
			TB6612FNG_MLeft_SetSpeed(Speed);
			break;
		case MRight:
			TB6612FNG_MRight_SetSpeed(Speed);
			break;
		default:
			break;
		}



	}
}

void TB6612FNG::TB6612FNG_MLeft_Forward()
{
	m_pStandBy->WriteBit(GPIO_PIN_SET);
	m_pMn1->WriteBit(GPIO_PIN_SET);
	m_pMn1B->WriteBit(GPIO_PIN_RESET);
}

void TB6612FNG::TB6612FNG_MLeft_Backward()
{
	m_pStandBy->WriteBit(GPIO_PIN_SET);
	m_pMn1->WriteBit(GPIO_PIN_RESET);
	m_pMn1B->WriteBit(GPIO_PIN_SET);
}



void TB6612FNG::TB6612FNG_MLeft_SetSpeed(float Speed)
{
	if(Speed < 100 )
	{
		m_pEn1->UpdateDutyCycle(Speed);
	}
}



void TB6612FNG::TB6612FNG_MRight_Forward()
{
	m_pStandBy->WriteBit(GPIO_PIN_SET);
	m_pMn2->WriteBit(GPIO_PIN_SET);
	m_pMn2B->WriteBit(GPIO_PIN_RESET);
}

void TB6612FNG::TB6612FNG_MRight_Backward()
{
	m_pStandBy->WriteBit(GPIO_PIN_SET);
	m_pMn2->WriteBit(GPIO_PIN_RESET);
	m_pMn2B->WriteBit(GPIO_PIN_SET);
}



void TB6612FNG::TB6612FNG_MRight_SetSpeed(float Speed)
{
	m_pEn2->UpdateDutyCycle(Speed);
}

void TB6612FNG::TB6612FNG_MRight_Break()
{
	m_pMn1->WriteBit(GPIO_PIN_SET);
	m_pMn1B->WriteBit(GPIO_PIN_SET);
}
void TB6612FNG::TB6612FNG_MLeft_Break()
{
	m_pMn2->WriteBit(GPIO_PIN_SET);
	m_pMn2B->WriteBit(GPIO_PIN_SET);
}



void TB6612FNG::Stop(MOTOR m)
{
		switch(m)
		{
		case MLeft:
			TB6612FNG_MLeft_Break();
			break;
		case MRight:
			TB6612FNG_MRight_Break();
			break;
		default:
			break;
		}
}
