/*
 * Buffer.cpp
 *
 *  Created on: 19 juil. 2015
 *      Author: jul
 */

#include "Buffer.h"

template<typename TBuffer>
Buffer<TBuffer>::Buffer() {
	// TODO Auto-generated constructor stub
	m_pData = 0;
	m_Taille = 0;
}

template<typename TBuffer>
Buffer<TBuffer>::~Buffer() {
	// TODO Auto-generated destructor stub
//	free(m_pBuffer);
	m_Taille = 0;
}

template<typename TBuffer>
Buffer<TBuffer>::Buffer (unsigned int Taille)
{
	m_Taille = 0;
	m_pData = new TBuffer[Taille];
	if(0 != m_pData)
	{
		m_Taille = Taille;
	}
}

template<typename TBuffer>
TBuffer * Buffer<TBuffer>::GetBuffer()
{
	return m_pData;
}

