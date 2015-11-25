

#include "Driver/Uart.h"




Uart::Uart()
{

	m_TX = 0;
	m_RX = 0;
	m_Buffer = 0;
}

Uart::Uart(USART_TypeDef *UART_Typedef,uint32_t UART_BaudRate ,uint32_t UART_Mode, uint32_t UART_Parity  ,uint32_t UART_StopBits, uint32_t UART_WordLength, uint32_t UART_HwFlowCtl, uint32_t UART_OverSampling)
{

	m_huart.Init .BaudRate 					= UART_BaudRate;
	m_huart.Init .Mode 						= UART_Mode;
	m_huart.Init .Parity 					= UART_Parity;
	m_huart.Init .StopBits 					= UART_StopBits;
	m_huart.Init .WordLength 				= UART_WordLength;
	m_huart.Init .HwFlowCtl					= UART_HwFlowCtl;
	m_huart.Init .OverSampling				= UART_OverSampling;

	m_huart.Instance 						= UART_Typedef;
	m_NVIC_IRQChannel 						= NonMaskableInt_IRQn;
	m_RX = 0;
	m_TX = 0;
}

bool Uart::SetUart(USART_TypeDef *UART_Typedef,uint32_t UART_BaudRate ,uint32_t UART_Mode, uint32_t UART_Parity  ,uint32_t UART_StopBits, uint32_t UART_WordLength, uint32_t UART_HwFlowCtl, uint32_t UART_OverSampling)
{
	UART_InitTypeDef UART_InitStruct;

	m_huart.Init.BaudRate 					= UART_BaudRate;
	m_huart.Init.Mode 						= UART_Mode;
	m_huart.Init.Parity 					= UART_Parity;
	m_huart.Init.StopBits 					= UART_StopBits;
	m_huart.Init.WordLength					= UART_WordLength;
	m_huart.Init.HwFlowCtl					= UART_HwFlowCtl;
	m_huart.Init.OverSampling				= UART_OverSampling;


	m_huart.Instance 	= UART_Typedef;


	return true;
}

bool Uart::Init()
{
	m_TX->Init();
	m_RX->Init();
	HAL_UART_Init(&m_huart);
	return true;
}

void Uart::Active(FunctionalState newState)
{
	if(ENABLE == newState)
	{
		__HAL_UART_ENABLE(&m_huart);
	}
	else
	{
		__HAL_UART_DISABLE(&m_huart);
	}

}

HAL_UART_StateTypeDef Uart::GetState()
{
 return  HAL_UART_GetState(&m_huart);
}

HAL_StatusTypeDef Uart::Send(uint8_t *pData, uint16_t Size, uint32_t Timeout )
{
	return HAL_UART_Transmit(&m_huart, pData, Size, Timeout);
}


void Uart::SetGpio(Gpio * Tx, Gpio * Rx )
{
	m_TX = Tx;
	m_RX = Rx;
}

HAL_StatusTypeDef Uart::Read(uint8_t *pData, uint16_t Size, uint32_t Timeout)
{
	return HAL_UART_Receive(&m_huart, pData, Size, Timeout);
}



bool Uart::InitInteruption(interruption * ITSuperviseur,IRQn_Type NVIC_IRQChannel,uint32_t NVIC_IRQChannelPreemptionPriority,uint32_t NVIC_IRQChannelSubPriority )
{
	if(0 == ITSuperviseur)
	{
		return false;
	}
	m_NVIC_IRQChannel = NVIC_IRQChannel;
	m_ITSuperviseur = ITSuperviseur;
	m_ITSuperviseur->SetObjetIT(m_NVIC_IRQChannel,NVIC_IRQChannelPreemptionPriority,NVIC_IRQChannelSubPriority ,this);
    /* Compute the Corresponding IRQ Priority --------------------------------*/



    HAL_UART_Receive_IT(&m_huart, caract, 1);

    NVIC_ClearPendingIRQ(m_NVIC_IRQChannel);

}


void Uart::IRQ()
{

	 HAL_UART_IRQHandler(& m_huart);
	//__HAL_UART_CLEAR_FLAG(& m_huart,UART_FLAG_RXNE);
}

void Uart::ActiveInteruption(FunctionalState NewState )
{

	if(NonMaskableInt_IRQn != m_NVIC_IRQChannel)
	{
		if(ENABLE == NewState)
		{
			HAL_NVIC_EnableIRQ(m_NVIC_IRQChannel);
			HAL_NVIC_ClearPendingIRQ(m_NVIC_IRQChannel);

			m_ITSuperviseur->ActiveIT(m_NVIC_IRQChannel);
		}
		else
		{
			m_ITSuperviseur->DesactiveIT(m_NVIC_IRQChannel);
		}
	}

}

void Uart::CallbackInteruption(void *UartHandle)
{
	if( 0 == UartHandle)
	{
		return;
	}
	RecvCharBuuf[0] = caract[0];
	//Retriger de l'IT

    //Renvoi le caractere
    Send((uint8_t*) RecvCharBuuf, 1,99);
    HAL_UART_Receive_IT(&m_huart, caract, 1);

}

void Uart::SendRecvdata()
{
	recvdata = false;
	Send((uint8_t*)RecvCharBuuf,1, 999 );
}


