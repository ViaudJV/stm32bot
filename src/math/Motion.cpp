/*
 * IntegrationPosition.cpp
 *
 *  Created on: 11 août 2015
 *      Author: jul
 */
#include "Seconde.h"
#include "math/Motion.h"

Motion::~Motion() {
	// TODO Auto-generated destructor stub
}


Motion::Motion()
{

	m_Dest.theta = 0;
	m_Dest.x 	 = 0;
	m_Dest.y     = 0;
}

void Motion::callback()
{

	VectPlan position = m_plocation->getLocation();
	float cmd = 0;
	float error = 0;

	///On génère le PID
	if(m_mode ==  MI_Rotation)
	{

		float errorTheta = 0;
		errorTheta = m_Dest.theta - position.theta;
		cmd = pidRotation.compute(errorTheta,m_tPid);
	}
	if(m_mode ==  MI_Lineaire)
	{
		error = m_Dest.x - position.x;

		cmd = pidlineare.compute(error,m_tPid);
	}

//	MoteurCommande.Update(cmd);
}
bool Motion::Movedistance(float d)
{
	if(MOTION_STATUS_MOVING == m_Status)
	{
		m_mode = MI_Lineaire;
		m_Status = MOTION_STATUS_MOVING;

		m_bInPosition = false;
		while(!m_bInPosition)
		{
			Seconde::sleep(100);
				m_bInPosition = true;
		}
		m_Status = MOTION_STATUS_IDLE;
	}
	else
	{
		return false;
	}
	return true;
}


bool Motion::Rotate(float theta)
{
	if(MOTION_STATUS_MOVING == m_Status)
	{
		m_Status = MOTION_STATUS_MOVING;
		m_mode = MI_Rotation;

		m_bInPosition = false;

		while(!m_bInPosition)
		{
			Seconde::sleep(100);

			m_bInPosition =  true;
		}

		m_Status = MOTION_STATUS_IDLE;
	}
	else
	{
		return false;
	}
	return true;
}

uint32_t Motion::SetPidLineaire(float kp,float kd, float ki, float MAxIntegral,float Max)
{
	 m_pidlineare.SetKd(kd);
	 m_pidlineare.SetKp(kp);
	 m_pidlineare.SetKi(ki);
	 m_pidlineare.SetMAxIntegral(MAxIntegral);
	 m_pidlineare.SetMax(Max);

}
uint32_t Motion::SetPidRotation(float kp,float kd, float ki, float MAxIntegral,float Max)
{
	 m_pidRotation.SetKd(kd);
	 m_pidRotation.SetKp(kp);
	 m_pidRotation.SetKi(ki);
	 m_pidRotation.SetMAxIntegral(MAxIntegral);
	 m_pidRotation.SetMax(Max);

}

