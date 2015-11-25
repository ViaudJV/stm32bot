
#include "stm32f4xx_hal.h"

#include "objet.h"
#include "Gpio.h"
#include "interrupt.h"


#ifndef __USART_H
#define __USART_H


class Usart : public objet
{
private:
	USART_HandleTypeDef m_husart;
	//NVIC_InitTypeDef m_NVIC_UsartInitStruct;
	uint32_t m_UsartBase;
protected:
	USART_TypeDef *m_USART_Typedef;
	uint8_t m_GPIO_AFX;
	Gpio * m_TX;
	Gpio * m_RX;

public :
	Usart();
	 ~Usart(){};
	Usart(USART_TypeDef *USART_Typedef,uint32_t USART_BaudRate ,uint32_t USART_CLKLastBit ,uint32_t USART_CLKPhase, uint32_t USART_CLKPolarity,uint32_t USART_Mode, uint32_t USART_Parity  ,uint32_t USART_StopBits, uint32_t USART_WordLength);
	bool SetUsart(USART_TypeDef *USART_Typedef,uint32_t USART_BaudRate ,uint32_t USART_CLKLastBit ,uint32_t USART_CLKPhase, uint32_t USART_CLKPolarity,uint32_t USART_Mode, uint32_t USART_Parity  ,uint32_t USART_StopBits, uint32_t USART_WordLength,uint8_t GPIO_AFX,uint32_t Usart_Base);
	bool Init();
	void Send(volatile char s);
	uint32_t GetUsart(){return m_UsartBase;};
	uint16_t Read();
	void Active(FunctionalState newState);
	void SetGpio(Gpio * TX, Gpio * Rx );
	void InitInteruption(uint8_t NVIC_IRQChannel,uint8_t NVIC_IRQChannelPreemptionPriority,uint8_t NVIC_IRQChannelSubPriority,FunctionalState NVIC_IRQChannelCmd );
	void ActiveInteruption(uint16_t USART_IT,FunctionalState NewState );
	void CallbackInteruption(USART_HandleTypeDef *UsartHandle);

};





#endif






