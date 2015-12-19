/*
 * IntegrationPosition.h
 *
 *  Created on: 11 août 2015
 *      Author: jul
 */
#include "Driver/timer.h"
#include "math/PID.h"
#include "math/Location.h"
#ifndef POSITION_H_
#define POSITION_H_
typedef enum
{
	MOTION_STATUS_IDLE = 0,
	MOTION_STATUS_MOVING = 1,

}MotionStatus;
typedef enum
{
	MI_Rotation = 0,
	MI_Lineaire = 1,
} ModeIntegration ;


class Motion : public timer
{
private:
	timer * m_ptimer ;	//Timer utilisé pour la correction PID
	uint32_t m_tPid;		//temps d'échantillionnage
	ModeIntegration m_mode;
	MotionStatus m_Status;
	Location * m_plocation;
	float m_mouv;
	bool m_bInPosition;
	PID m_pidRotation;
	PID m_pidlineare;

	VectPlan m_Dest;

public:

	Motion() ;
	PID pidRotation;
	PID pidlineare;
	~Motion();
	bool Rotate(float theta);
	bool Movedistance(float d);
	void InitPosition();
	void SetPosition(float theta , float x, float y);
	void Setmode(ModeIntegration newmode){m_mode = newmode;};
	uint32_t SetPidRotation(float kp,float kd, float ki, float MAxIntegral,float Max);
	uint32_t SetPidLineaire(float kp,float kd, float ki, float MAxIntegral,float Max);
	void callback();
};

#endif /* POSITION_H_ */
