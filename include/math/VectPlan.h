/*
 * VectPlan.h
 *
 *  Created on: 4 août 2015
 *      Author: jul
 */

#ifndef VECTPLAN_H_
#define VECTPLAN_H_
#include "vector2.h"


class VectPlan : public vector2
{
public:

	float x;          //!< coordonnée selon l'axe x en mm
	float y;          //!< coordonnée selon l'axe y en mm
	float theta;      //!< orientation en rd
public:
	VectPlan()
	{
		x = 0;
		y = 0;
		theta = 0;
	};

	VectPlan(float X, float Y, float Theta)
	{
		x = X;
		y = Y;
		theta = Theta;
	};

	inline VectPlan operator/( float k)
	{
		return VectPlan(x / k, y / k, theta / k);
	};

	inline VectPlan operator+( VectPlan b)
	{
		return VectPlan(x + b.x, y + b.y, theta + b.theta);
	};

	inline VectPlan operator-(VectPlan b)
	{
		return VectPlan(x - b.x,y - b.y, theta - b.theta);
	};

	inline VectPlan operator*(float k)
	{
		return VectPlan(k * x, k * y, k * theta);
	};

	inline VectPlan operator=(VectPlan a)
	{
	    x = a.x;
	    y = a.y;
	    theta = a.theta;
	    return *this;
	};



};

#endif /* VECTPLAN_H_ */
