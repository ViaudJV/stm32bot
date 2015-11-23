#include "stm32f4xx.h"
#include "stm32f4xx_hal_cortex.h"
#include "objet.h"
#include "Gpio.h"
#include "Usart.h"

#include "interrupt.h"



interruption::interruption()
{
	//IT USART UART
	m_pusart1 	= 0;
	m_pusart2 	= 0;
	m_pusart3 	= 0;
	m_puart4 	= 0;
	m_puart5 	= 0;
	m_pusart6 	= 0;

	//IT TIMER
	m_ptimer1 = 0;
	m_ptimer2 = 0;
	m_ptimer3 = 0;
	m_ptimer4 = 0;
	m_ptimer5 = 0;
	m_ptimer6 = 0;
	m_ptimer7 = 0;
	m_ptimer8 = 0;
	m_ptimer9 = 0;
	m_ptimer10 = 0;
	m_ptimer11 = 0;
	m_ptimer12 = 0;
	m_ptimer13 = 0;
	m_ptimer14 = 0;
}


bool interruption::SetObjetIT(uint32_t NVIC_IRQChannel,uint32_t NVIC_IRQChannelPreemptionPriority,uint32_t NVIC_IRQChannelSubPriority , objet * pobjet)
{
	if( 0 == pobjet )
	{
			return false;
	}
	if( (int) USART1_IRQn == NVIC_IRQChannel)
	{
		m_pusart1 = pobjet;
	}
	else if( USART2_IRQn == NVIC_IRQChannel)
	{
		m_pusart2 = pobjet;
	}
	else if( USART3_IRQn == NVIC_IRQChannel)
	{
		m_pusart3 = pobjet;
	}
	else if( UART4_IRQn == NVIC_IRQChannel)
	{
		m_puart4 = pobjet;
	}
	else if( UART5_IRQn == NVIC_IRQChannel)
	{
		m_puart5 = pobjet;
	}
	else if( USART6_IRQn == NVIC_IRQChannel)
	{
		m_pusart6 = pobjet;

	}
	else if( TIM2_IRQn == NVIC_IRQChannel)
	{
		m_ptimer2 = pobjet;

	}
	else if( TIM3_IRQn == NVIC_IRQChannel)
	{
		m_ptimer3 = pobjet;

	}
	else if( TIM4_IRQn == NVIC_IRQChannel)
	{
		m_ptimer4 = pobjet;

	}
	else if( TIM5_IRQn == NVIC_IRQChannel)
	{
		m_ptimer5 = pobjet;

	}
	else if( TIM6_DAC_IRQn == NVIC_IRQChannel)
	{
		m_ptimer6 = pobjet;

	}
	else if( TIM7_IRQn == NVIC_IRQChannel)
	{
		m_ptimer7 = pobjet;
	}
	else if( TIM1_BRK_TIM9_IRQn == NVIC_IRQChannel)
	{
		m_ptimer9 = pobjet;

	}
	else if( TIM1_UP_TIM10_IRQn == NVIC_IRQChannel)
	{
		m_ptimer10 = pobjet;

	}
	else if( TIM1_TRG_COM_TIM11_IRQn == NVIC_IRQChannel)
	{
		m_ptimer11 = pobjet;

	}
	else if( TIM8_BRK_TIM12_IRQn == NVIC_IRQChannel)
	{
		m_ptimer12 = pobjet;

	}
	else if( TIM8_UP_TIM13_IRQn == NVIC_IRQChannel)
	{
		m_ptimer12 = pobjet;

	}
	else if( TIM8_TRG_COM_TIM14_IRQn == NVIC_IRQChannel)
	{
		m_ptimer12 = pobjet;

	}
	  HAL_NVIC_SetPriority((IRQn_Type)NVIC_IRQChannel, NVIC_IRQChannelPreemptionPriority, NVIC_IRQChannelSubPriority);
	return true;

}

bool interruption::ActiveIT(IRQn_Type NVIC_IRQChannel)
{
	HAL_NVIC_EnableIRQ(NVIC_IRQChannel);
	return true;
}
bool interruption::DesactiveIT(IRQn_Type NVIC_IRQChannel)
{
	HAL_NVIC_DisableIRQ(NVIC_IRQChannel);
	return true;
}

void interruption::CallbackInteruption(TIM_HandleTypeDef *TimeHandle)
{
	if( 0 == TimeHandle )
		return;

	if( TIM1 == (TimeHandle->Instance) )
	{
		if(m_ptimer12 != 0)
		{
			m_ptimer1->CallbackInteruption( TimeHandle);
		}
	}
	else if( TIM2 == (TimeHandle->Instance))
	{
		if(m_ptimer2 != 0)
		{
			m_ptimer2->CallbackInteruption( TimeHandle);

		}
	}
	if( TIM3 == (TimeHandle->Instance) )
	{
		if(m_ptimer3 != 0)
		{
			m_ptimer3->CallbackInteruption( TimeHandle);
		}
	}
	else if( TIM4 == (TimeHandle->Instance))
	{
		if(m_ptimer4 != 0)
		{
			m_ptimer4->CallbackInteruption( TimeHandle);

		}
	}
	if( TIM5 == (TimeHandle->Instance) )
	{
		if(m_ptimer5 != 0)
		{
			m_ptimer5->CallbackInteruption( TimeHandle);
		}
	}
	else if( TIM6 == (TimeHandle->Instance))
	{
		if(m_ptimer6 != 0)
		{
			m_ptimer6->CallbackInteruption( TimeHandle);

		}
	}
	if( TIM7 == (TimeHandle->Instance) )
	{
		if(m_ptimer7 != 0)
		{
			m_ptimer7->CallbackInteruption( TimeHandle);
		}
	}
	else if( TIM8 == (TimeHandle->Instance))
	{
		if(m_ptimer8 != 0)
		{
			m_ptimer8->CallbackInteruption( TimeHandle);

		}
	}
	else if( TIM9 == (TimeHandle->Instance))
	{
		if(m_ptimer9 != 0)
		{
			m_ptimer9->CallbackInteruption( TimeHandle);

		}
	}
	else if( TIM10 == (TimeHandle->Instance))
	{
		if(m_ptimer10 != 0)
		{
			m_ptimer10->CallbackInteruption( TimeHandle);

		}
	}
	else if( TIM11 == (TimeHandle->Instance))
	{
		if(m_ptimer11 != 0)
		{
			m_ptimer11->CallbackInteruption( TimeHandle);

		}
	}
	else if( TIM12 == (TimeHandle->Instance))
	{
		if(m_ptimer12 != 0)
		{
			m_ptimer12->CallbackInteruption( TimeHandle);

		}
	}
	else if( TIM13 == (TimeHandle->Instance))
	{
		if(m_ptimer13 != 0)
		{
			m_ptimer13->CallbackInteruption( TimeHandle);

		}
	}
	else if( TIM14 == (TimeHandle->Instance))
	{
		if(m_ptimer14 != 0)
		{
			m_ptimer14->CallbackInteruption( TimeHandle);

		}
	}
}


void interruption::CallbackInteruption(UART_HandleTypeDef *UartHandle)
{
	if( 0 == UartHandle )
		return;

	if( UART4 == (UartHandle->Instance) )
	{
		if(m_puart4 != 0)
		{
				m_puart4->CallbackInteruption( UartHandle);
		}
	}
	else if( UART5 == (UartHandle->Instance))
	{
		if(m_puart5 != 0)
		{
			m_puart5->CallbackInteruption( UartHandle);

		}
	}

}

