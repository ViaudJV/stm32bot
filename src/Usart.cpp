
#include "Usart.h"




Usart::Usart()
{

	m_TX = 0;
	m_RX = 0;
	m_GPIO_AFX = 0;
	m_USART_Typedef = 0;
	m_UsartBase = 0;

}

Usart::Usart(USART_TypeDef *USART_Typedef,uint32_t USART_BaudRate ,uint32_t USART_CLKLastBit ,uint32_t USART_CLKPhase, uint32_t USART_CLKPolarity,uint32_t USART_Mode, uint32_t USART_Parity  ,uint32_t USART_StopBits, uint32_t USART_WordLength)
{
	USART_InitTypeDef USART_InitStruct;

	m_husart.Init.BaudRate 					= USART_BaudRate;
	m_husart.Init.CLKLastBit 				= USART_CLKLastBit;
	m_husart.Init.CLKPhase 					= USART_CLKPhase;
	m_husart.Init.CLKPolarity				= USART_CLKPolarity;
	m_husart.Init.Mode 						= USART_Mode;
	m_husart.Init.Parity 					= USART_Parity;
	m_husart.Init.StopBits 					= USART_StopBits;
	m_husart.Init.WordLength 				= USART_WordLength;

	m_husart.Instance = USART_Typedef;

	//m_UsartBase = Usart_Base;
	//m_GPIO_AFX = GPIO_AFX;
	m_RX = 0;
	m_TX = 0;
}

bool Usart::SetUsart(USART_TypeDef *USART_Typedef,uint32_t USART_BaudRate ,uint32_t USART_CLKLastBit ,uint32_t USART_CLKPhase, uint32_t USART_CLKPolarity,uint32_t USART_Mode, uint32_t USART_Parity  ,uint32_t USART_StopBits, uint32_t USART_WordLength,uint8_t GPIO_AFX,uint32_t Usart_Base)
{
	USART_InitTypeDef USART_InitStruct;

	m_husart.Init.BaudRate 					= USART_BaudRate;
	m_husart.Init.CLKLastBit 				= USART_CLKLastBit;
	m_husart.Init.CLKPhase 					= USART_CLKPhase;
	m_husart.Init.CLKPolarity				= USART_CLKPolarity;
	m_husart.Init.Mode 						= USART_Mode;
	m_husart.Init.Parity 					= USART_Parity;
	m_husart.Init.StopBits 					= USART_StopBits;
	m_husart.Init.WordLength 				= USART_WordLength;

	m_husart.Instance = USART_Typedef;


	return true;
}

bool Usart::Init()
{
	m_TX->Init();
	m_RX->Init();
	HAL_USART_Init(&m_husart);
	return true;
}

void Usart::Active(FunctionalState newState)
{
//	USART_Cmd(m_USART_Typedef, newState);
}

void Usart::Send(volatile char s)
{
		// wait until data register is empty
//		while( USART_GetFlagStatus(m_USART_Typedef, USART_FLAG_TC) == RESET );
//		USART_SendData(m_USART_Typedef, s);
}


void Usart::SetGpio(Gpio * TX, Gpio * RX )
{
	m_TX = TX;
	m_RX = RX;
}

uint16_t Usart::Read()
{
	// wait until data register is empty
	//while(!(m_USART_Typedef->SR & USART_FLAG_RXNE) );
//	return USART_ReceiveData(m_USART_Typedef);
}


void Usart::InitInteruption(uint8_t NVIC_IRQChannel,uint8_t NVIC_IRQChannelPreemptionPriority,uint8_t NVIC_IRQChannelSubPriority,FunctionalState NVIC_IRQChannelCmd )
{
//	m_NVIC_UsartInitStruct.NVIC_IRQChannel = NVIC_IRQChannel;
//	m_NVIC_UsartInitStruct.NVIC_IRQChannelCmd = NVIC_IRQChannelCmd;
//	m_NVIC_UsartInitStruct.NVIC_IRQChannelPreemptionPriority = NVIC_IRQChannelPreemptionPriority;
//	m_NVIC_UsartInitStruct.NVIC_IRQChannelSubPriority = NVIC_IRQChannelSubPriority;
//	NVIC_Init(&m_NVIC_UsartInitStruct);
}
void Usart::ActiveInteruption(uint16_t USART_IT,FunctionalState NewState )
{
//	USART_ITConfig(m_USART_Typedef,USART_IT,NewState);

}

void Usart::CallbackInteruption(USART_HandleTypeDef *UsartHandle)
{

//	Read();

//	USART_ClearITPendingBit(m_USART_Typedef,USART_IT_RXNE);




}
