
#ifndef __UART_H
#define __UART_H



#include "stm32f4xx_hal.h"

#include "objet.h"
#include "Gpio.h"
#include "interrupt.h"
#include "Buffer.h"
#include "RollingBuffer.h"





class Uart : public objet
{
private:
	interruption * m_ITSuperviseur;
	UART_HandleTypeDef m_huart;
	Gpio * m_TX;
	Gpio * m_RX;
	IRQn_Type m_NVIC_IRQChannel;
	uint8_t caract[1];
	RollingBuffer<char> * m_Buffer;
	char RecvCharBuuf[1];
	char CharBuuf[1];
	bool recvdata;
protected:

public :
	Uart();
	~Uart(){};
	Uart(USART_TypeDef *UART_Typedef,uint32_t UART_BaudRate ,uint32_t UART_Mode, uint32_t UART_Parity  ,uint32_t UART_StopBits, uint32_t UART_WordLength, uint32_t UART_HwFlowCtl, uint32_t UART_OverSampling);
	bool SetUart(USART_TypeDef *UART_Typedef,uint32_t UART_BaudRate ,uint32_t UART_Mode, uint32_t UART_Parity  ,uint32_t UART_StopBits, uint32_t UART_WordLength, uint32_t UART_HwFlowCtl, uint32_t UART_OverSampling);
	bool Init();
	void IRQ();
	HAL_StatusTypeDef Send(uint8_t *pData, uint16_t Size, uint32_t Timeout );
	HAL_StatusTypeDef Read(uint8_t *pData, uint16_t Size, uint32_t Timeout);

	void Active(FunctionalState newState);


	void SetGpio(Gpio * Tx, Gpio * Rx );




	bool InitInteruption(interruption * ITSuperviseur,IRQn_Type NVIC_IRQChannel,uint32_t NVIC_IRQChannelPreemptionPriority,uint32_t NVIC_IRQChannelSubPriority );
	void ActiveInteruption(FunctionalState NewState );

	bool GetStateRev(){return recvdata;};

	void SendRecvdata();
	virtual void CallbackInteruption(void *UartHandle);

	HAL_UART_StateTypeDef GetState();

};





#endif






