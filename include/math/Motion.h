/*
 * IntegrationPosition.h
 *
 *  Created on: 11 août 2015
 *      Author: jul
 */
#include "Driver/timer.h"
#include "Driver/Gpio.h"
#include "Driver/Spi.h"
#include "Driver/LIS3DSH.h"
#include "math/VectPlan.h"
#include "math/PID.h"
#ifndef POSITION_H_
#define POSITION_H_

typedef enum
{
	MI_Rotation = 0,
	MI_Lineaire = 1,
} ModeIntegration ;


class Motion {
private:
	timer * m_Timer ;	//Timer utilisé d'échantillionnage
	LIS3DSH * m_mems;	//LIS3DSH
	uint32_t m_T;		//temps d'échantillionnage


	uint32_t m_W0; 		//Vitesse de rotation du dernier échantillion
	uint32_t m_V0; 		//Vitesse de translation échantillion

	uint32_t m_d;			//Distance en mm du centre de rotation
	ModeIntegration m_mode;


	VectPlan m_Position;

	float m_mouv;

	PID m_pidRotation;
	PID m_pidlineare;
public:
	Motion(LIS3DSH * mems,timer * Timer,ModeIntegration mode,float d){m_mems = mems; m_Timer = Timer;m_mode = mode;m_d = d;m_Position.theta = 0; m_Position.x = 0; m_Position.y = 0;} ;
	Motion() ;
	PID pidRotation;
	PID pidlineare;
	~Motion();
	bool Rotate(float theta);
	bool Movedistance(float d);
	void InitPosition();
	void SetPosition(float theta , float x, float y);
	void Setmode(ModeIntegration newmode){m_mode = newmode;};
	uint32_t Calculdelta();
	uint32_t SetPidRotation(float kp,float kd, float ki, float MAxIntegral,float Max);
	uint32_t SetPidLineaire(float kp,float kd, float ki, float MAxIntegral,float Max);
	void callback();
};

#endif /* POSITION_H_ */
