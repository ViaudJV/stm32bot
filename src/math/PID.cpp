/*
 * PID.cpp
 *
 *  Created on: 9 août 2015
 *      Author: jul
 */

#include "math/PID.h"
#include <stdint.h>
PID::PID() {
	// TODO Auto-generated constructor stub
	m_Kp = 0;
	m_Ki = 0;;
	m_Kd = 0;;
	m_max_out = 0;
	m_max_integral = 0;
	m_integral = 0;
	m_lastError = 0;
}


PID::PID(float kp,float ki,float kd,float Max, float max_integral )
{
	m_Kp = kp;
	m_Ki = ki;
	m_Kd = kd;
	m_max_out = Max;
	m_max_integral = max_integral;
	m_integral = 0;
	m_lastError = 0;
}


PID::~PID() {
	// TODO Auto-generated destructor stub
}


float PID::compute(float error, float dt)
{
	float out;

	float derivate = (error - m_lastError) / dt;
	m_lastError = error;
	m_integral += error * dt;

	// saturation de l'integrale
	if(m_max_integral)
	{
		if(m_integral > m_max_integral)
		{
			m_integral = m_max_integral;
		}
		else if(m_integral < -m_max_integral)
		{
			m_integral = -m_max_integral;
		}
	}

	// calcul du PID
	out = m_Kp * error + m_Ki * m_integral + m_Kd * derivate;

	// saturation de la sortie
	if(m_max_out)
	{
		if(out > m_max_out)
		{
			out = m_max_out;
		}
		else if(out < -m_max_out)
		{
			out = -m_max_out;
		}
	}

	return out;
}

