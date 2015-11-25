/*
 * IntegrationPosition.cpp
 *
 *  Created on: 11 août 2015
 *      Author: jul
 */
#include "Seconde.h"
#include "math/Motion.h"

Motion::Motion() {
	// TODO Auto-generated constructor stub
	m_Position.theta = 0;
	m_Position.x = 0;
	m_Position.y = 0;
}

Motion::~Motion() {
	// TODO Auto-generated destructor stub
}

void Motion::InitPosition()
{
	m_Position.theta = 0;
	m_Position.x = 0;
	m_Position.y = 0;
}
void Motion::SetPosition(float theta , float x, float y)
{
	m_Position.theta = theta;
	m_Position.x = x;
	m_Position.y = y;
}
void Motion::callback()
{
	float error = 0;
	//On calcul la  nouvelle position
	Calculdelta();
	float cmd = 0;
	error = m_mouv - m_Position.theta;
	///On génère le PID
	if(m_mode ==  MI_Rotation)
	{
		error = m_mouv - m_Position.theta;
		cmd = pidRotation.compute(error,m_T);
	}
	if(m_mode ==  MI_Lineaire)
	{
		error = m_mouv - m_Position.x;
		cmd = pidlineare.compute(error,m_T);
	}

//	MoteurCommande.Update(cmd);
}
bool Motion::Movedistance(float d)
{
	m_mode = MI_Lineaire;
	bool in_position = false;
	m_Position.x =0;
	if(0 != m_Timer)
	{
		m_Timer->ActiveInteruption(ENABLE);
	}

	while(in_position)
	{
		Seconde::sleep(100);
		if( m_Position.x == d)
			in_position = true;
	}
}


bool Motion::Rotate(float theta)
{
	bool in_position = false;

	m_mode = MI_Rotation;
	m_Position.theta = 0;

	if(0 != m_Timer)
	{
		m_Timer->ActiveInteruption(ENABLE);
	}
	while(in_position)
	{
		Seconde::sleep(100);
		if( m_Position.theta == theta)
			in_position = true;
	}
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
uint32_t Motion::Calculdelta()
{
	uint8_t MSB, LSB;
	int16_t Xg, Yg;
	uint32_t Py = 0;
	uint32_t Ro = 0;

	if( MI_Rotation == m_mode )
	{

		MSB = m_mems->SPI_LIS3DSH_read(OUT_X_H);    // X-axis MSB
		LSB = m_mems->SPI_LIS3DSH_read(OUT_X_L);    // X-axis LSB
		Xg = (MSB << 8) | (LSB);                	// Merging
		Xg /= -141;
		Xg *= 1000;    //Converting to mm/s²
		m_W0 = Xg * m_T * m_d + m_W0; // calcul de la rotation angulaire
		Ro = m_W0 * m_T;


		m_Position.theta = m_Position.theta + Ro;

	}
	else
	{
		MSB = m_mems->SPI_LIS3DSH_read(OUT_Y_H);    // Y-axis MSB
		LSB = m_mems->SPI_LIS3DSH_read(OUT_Y_L);    // Y-axis LSB
		Yg = (MSB << 8) | (LSB);                	// Merging
		Yg /= -141;                        // converting to meters per second squared
		Yg *= 1000;  //converting to mm par secondes²
		m_V0 = Yg * m_T + m_V0;
		Py = m_V0 * m_T;

		m_Position.x = m_Position.x + Py;
	}

	return 0;
}
