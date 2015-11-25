/*
 * Buffer.h
 *
 *  Created on: 19 juil. 2015
 *      Author: jul
 */

#ifndef BUFFER_H_
#define BUFFER_H_
template<typename TBuffer> class Buffer;

template<typename TBuffer>
class Buffer
{
	TBuffer * 			m_pData;
	unsigned int		m_Taille;
public:

	Buffer();
	Buffer(unsigned int Taille);
	TBuffer * 	 GetBuffer();
	unsigned int GetTaille(){return m_Taille;};
	virtual ~Buffer();
};

#endif /* BUFFER_H_ */
