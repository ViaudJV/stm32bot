/*
 *Mems_Location .h
 *
 *  Created on: 12 déc. 2015
 *      Author: jul
 */

#ifndef MEMS_LOCATION_H_
#define MEMS_LOCATION_H_

#include "Driver/Gpio.h"
#include "Driver/Spi.h"
#include "Driver/LIS3DSH.h"
#include "Driver/timer.h"
#include "math/VectPlan.h"
#include "math/Location.h"
class MemsLocation : public Location{
public:
	MemsLocation(uint32_t ad,LIS3DSH * pamems);
	virtual ~MemsLocation();
	void InitPosition();
	void SetPosition(float theta , float x, float y);
	void CalculPosition();
	void callback();
private:
	LIS3DSH * 	m_pmems;	//LIS3DSH
	uint32_t 	m_ptEch;	//temps d'échantillionnage

	uint32_t 	m_W0; 		//Vitesse de rotation du dernier échantillion
	uint32_t 	m_V0; 		//Vitesse de translation échantillion

	uint32_t	m_TEch;			//Temps d'echantillonnage

	uint32_t m_d;			//Distance en mm du centre de rotation
};

#endif /* LOCATION_H_ */
