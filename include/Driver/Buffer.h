/*
 * Buffer.h
 *
 *  Created on: 19 juil. 2015
 *      Author: jul
 */

#ifndef BUFFER_H_
#define BUFFER_H_

#include <stdio.h>
#include <stdlib.h>


template<typename TBuffer> class Buffer;

template<typename TBuffer>
class Buffer
{
	TBuffer * 			m_pData;
	uint32_t		m_Taille;
public:

	Buffer();
	Buffer(uint32_t Taille);
	TBuffer * 	 GetBuffer();
	uint32_t GetTaille(){return m_Taille;};
	virtual ~Buffer();
};

#endif /* BUFFER_H_ */
