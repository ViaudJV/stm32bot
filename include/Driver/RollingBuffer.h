/*
 * RollingBuffer.h
 *
 *  Created on: 19 juil. 2015
 *      Author: jul
 */

#ifndef ROLLINGBUFFER_H_
#define ROLLINGBUFFER_H_

#include "Driver/Buffer.h"
template<typename TRollingBuffer> class RollingBuffer;

template<typename TRollingBuffer>
class RollingBuffer {
private:
	Buffer<TRollingBuffer> ** m_pBuffer;
	uint32_t m_PosBegin;
	uint32_t  m_PosEnd;
	uint32_t m_NbElementpris;
	uint32_t m_NbElement;

public:
	RollingBuffer();
	RollingBuffer(uint32_t NbElement, uint32_t Taille);
	virtual ~RollingBuffer();

	Buffer<TRollingBuffer> * GetNextfreeBuffer();

};

#endif /* ROLLINGBUFFER_H_ */
