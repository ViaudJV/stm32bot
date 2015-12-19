/*
 * Location.h
 *
 *  Created on: 12 déc. 2015
 *      Author: jul
 */

#ifndef LOCATION_H_
#define LOCATION_H_
#include "math/VectPlan.h"
#include "Driver/timer.h"
class Location : public timer {
protected :

	VectPlan m_Position;
public:
	Location();
	virtual ~Location();
    VectPlan getLocation(){return m_Position;};
	void InitPosition();
	void SetPosition(float theta , float x, float y);

	virtual void callback(){};
};

#endif /* LOCATION_H_ */
