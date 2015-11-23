#include "HC-06.h"



HC06::HC06():Uart()
{

	m_Enable = 0;
}

HC06::HC06(USART_TypeDef *UART_Typedef,uint32_t UART_BaudRate ,uint32_t UART_Mode, uint32_t UART_Parity  ,uint32_t UART_StopBits, uint32_t UART_WordLength, uint32_t UART_HwFlowCtl, uint32_t UART_OverSampling):Uart(UART_Typedef,UART_BaudRate,UART_Mode,UART_Parity,UART_StopBits,UART_WordLength,UART_HwFlowCtl,UART_OverSampling)
{
	m_Enable = 0;
}
void HC06::SetGpio(Gpio * Tx, Gpio * Rx, Gpio * Enable  )
{
	Uart::SetGpio(Tx,Rx);
	m_Enable = Enable;
}

bool HC06::Init()
{
	Uart::Init();
	m_Enable->Init();
}

void HC06::Active(FunctionalState newState)
{
	Uart::Active(newState);
	m_Enable->WriteBit(GPIO_PIN_SET);

}

void CallbackInteruption(int NVIC_IRQChannel)
{

}


