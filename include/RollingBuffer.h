/*
 * RollingBuffer.h
 *
 *  Created on: 19 juil. 2015
 *      Author: jul
 */

#ifndef ROLLINGBUFFER_H_
#define ROLLINGBUFFER_H_
template<typename TRollingBuffer> class RollingBuffer;

template<typename TRollingBuffer>
class RollingBuffer {
private:
	Buffer<TRollingBuffer> ** m_pBuffer;
	unsigned int m_PosBegin;
	unsigned int  m_PosEnd;
	unsigned int m_NbElementpris;
	unsigned int m_NbElement;

public:
	RollingBuffer();
	RollingBuffer(unsigned int NbElement, unsigned int Taille);
	virtual ~RollingBuffer();

	Buffer<TRollingBuffer> * GetNextfreeBuffer();

};

#endif /* ROLLINGBUFFER_H_ */
