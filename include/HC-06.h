
#include "Uart.h"
#include "Gpio.h"

#ifndef HC_06_H
#define HC_06_H

class HC06 : public Uart
{
private :
	Gpio * m_Enable;
	char Hello[12];
public:
	HC06();
	virtual ~HC06(){};
	HC06(USART_TypeDef *UART_Typedef,uint32_t UART_BaudRate ,uint32_t UART_Mode, uint32_t UART_Parity  ,uint32_t UART_StopBits, uint32_t UART_WordLength, uint32_t UART_HwFlowCtl, uint32_t UART_OverSampling);
	void SetGpio(Gpio * TX, Gpio * Rx, Gpio * Enable  );
	bool Init();
	void Active(FunctionalState newState);
};

#endif

