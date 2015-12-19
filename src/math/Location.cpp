/*
 * Location.cpp
 *
 *  Created on: 12 déc. 2015
 *      Author: jul
 */

#include "math/Location.h"

Location::Location() {
	// TODO Auto-generated constructor stub

}

Location::~Location() {
	// TODO Auto-generated destructor stub
}


void Location::InitPosition()
{
	m_Position.theta = 0;
	m_Position.x = 0;
	m_Position.y = 0;
}

void Location::SetPosition(float theta , float x, float y)
{
	m_Position.theta = theta;
	m_Position.x = x;
	m_Position.y = y;
}
