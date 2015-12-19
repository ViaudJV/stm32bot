/*
 * Location.cpp
 *
 *  Created on: 12 déc. 2015
 *      Author: jul
 */

#include "math/MemsLocation.h"

MemsLocation::MemsLocation(uint32_t ad,LIS3DSH * pamems)
{
	// TODO Auto-generated constructor stub

	m_d = ad;
	m_pmems = pamems;
}




MemsLocation::~MemsLocation() {
	// TODO Auto-generated destructor stub
}

void MemsLocation::callback()
{
	CalculPosition();
}

void MemsLocation::CalculPosition()
{
	uint8_t MSB, LSB;
	int16_t Xg, Yg;
	uint32_t Py = 0;
	uint32_t Ro = 0;

	//Calcul de la rotation
	MSB = m_pmems->SPI_LIS3DSH_read(OUT_X_H);    // X-axis MSB
	LSB = m_pmems->SPI_LIS3DSH_read(OUT_X_L);    // X-axis LSB
	Xg = (MSB << 8) | (LSB);                	// Merging
	Xg /= -141;
	Xg *= 1000;    //Converting to mm/s²
	m_W0 = Xg * m_TEch * m_d + m_W0; // calcul de la rotation angulaire
	Ro = m_W0 * m_TEch;


	m_Position.theta = m_Position.theta + Ro;

	//Calcul d'un déplacement avant arrière
	MSB = m_pmems->SPI_LIS3DSH_read(OUT_Y_H);    // Y-axis MSB
	LSB = m_pmems->SPI_LIS3DSH_read(OUT_Y_L);    // Y-axis LSB
	Yg = (MSB << 8) | (LSB);                	// Merging
	Yg /= -141;                        // converting to meters per second squared
	Yg *= 1000;  //converting to mm par secondes²
	m_V0 = Yg * m_TEch + m_V0;
	Py = m_V0 * m_TEch;
	//Py distance dans l'axe des x relatif
	m_Position.x = m_Position.x + ( Py * cosf(m_Position.theta));
	m_Position.y = m_Position.y + ( Py * sinf(m_Position.theta));
}
