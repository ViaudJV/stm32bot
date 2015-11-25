/*
 * Robot.h
 *
 *  Created on: 14 août 2015
 *      Author: jul
 */
#include "math/VectPlan.h"
#include "Robot/CarteMoteur.h"

#ifndef ROBOT_H_
#define ROBOT_H_

class Robot {
public:

	VectPlan m_Position;
	CarteMoteur* CmdMoteur;

	void MovePosition(float x,float y){};
	void MoveDistance(float distance, float rotation){};
	Robot();
	~Robot();
};

#endif /* ROBOT_H_ */
