/*
 * RollingBuffer.cpp
 *
 *  Created on: 19 juil. 2015
 *      Author: jul
 */
#include "Driver/Buffer.h"
#include <stdlib.h>
#include "Driver/RollingBuffer.h"

template<typename TRollingBuffer>
RollingBuffer<TRollingBuffer>::RollingBuffer() {
	// TODO Auto-generated constructor stub
	m_pBuffer = 0;
	m_PosBegin = 0;
	m_PosEnd = 0;
	m_NbElementpris = 0;
	m_NbElement = 0;
}

template<typename TRollingBuffer>
RollingBuffer<TRollingBuffer>::RollingBuffer(unsigned int NbElement, unsigned int Taille) {
	// TODO Auto-generated constructor stub
	m_NbElementpris = 0;
	m_NbElement = NbElement;
	m_pBuffer = new Buffer<TRollingBuffer>[NbElement];

	if(0 != m_pBuffer )
	{
		for (int i = 0; i < NbElement; i++)
		{
			m_pBuffer[i] =new Buffer<TRollingBuffer>(Taille);
		}


		m_PosBegin = 0;
		m_PosEnd = 0;
	}

}


template<typename TRollingBuffer>
Buffer<TRollingBuffer> * RollingBuffer<TRollingBuffer>::GetNextfreeBuffer()
{
	Buffer<TRollingBuffer> * pBufferUse = 0;
	//Si aucun buffer n'est libre alors on envoie le pt null
	if(m_NbElement == m_NbElementpris)
	{
		pBufferUse = 0;
	}
	//sinon on envoi la position du pointeur de fin
	else
	{
		pBufferUse = m_pBuffer[m_PosEnd];
	}
	//On décale la position du pointeur de fin
	m_PosEnd ++;
	//On augmente le nb d'elementpris dans la liste du buffeur
	m_NbElementpris++;

	//Si le pointeur de
	if(m_PosEnd > m_NbElement)
	{
		m_PosEnd = 0;
	}
	return pBufferUse;
}

template<typename TRollingBuffer>
RollingBuffer<TRollingBuffer>::~RollingBuffer()
{
//	for(unsigned int i = 0;  i < m_NbElement; i++ )
//	{
//		free(m_pBuffer[i]);
//	}

//	free(m_pBuffer);

	m_pBuffer = 0;
	m_PosBegin = 0;
	m_PosEnd = 0;
	m_NbElementpris = 0;
	m_NbElement = 0;
	// TODO Auto-generated destructor stub
}

