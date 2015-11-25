#include "Driver/objet.h"
#include "Driver/interrupt.h"
#include "Driver/timer.h"


timer::timer()
{

}
timer::timer(TIM_TypeDef* TIMERx,uint32_t TIM_Prescaler ,uint32_t TIM_CounterMode, uint32_t TIM_Period, uint32_t TIM_ClockDivision,uint32_t TIM_RepetitionCounter, HAL_TIM_ActiveChannel Channel)
{


	m_TIM_THandleStructure.Instance = TIMERx;

	TIM_Base_InitTypeDef	TIM_TimeBaseInitStructure;



	TIM_TimeBaseInitStructure.Prescaler = TIM_Prescaler;
	TIM_TimeBaseInitStructure.CounterMode = TIM_CounterMode;
	TIM_TimeBaseInitStructure.Period = TIM_Period;
	TIM_TimeBaseInitStructure.ClockDivision = TIM_ClockDivision;
	TIM_TimeBaseInitStructure.RepetitionCounter = TIM_RepetitionCounter;

	m_init = false;
	m_TIM_THandleStructure.Init = TIM_TimeBaseInitStructure;
}


void timer::SetAutoreload( uint32_t TIM_Period)
{
	if(m_init)
	{
		Active(DISABLE);
		Active(ENABLE);
	}

}

void timer::SetTimer(TIM_TypeDef* TIMERx,uint16_t TIM_Prescaler ,uint16_t TIM_CounterMode, uint32_t TIM_Period, uint16_t TIM_ClockDivision,uint8_t TIM_RepetitionCounter )
{
	m_TIM_THandleStructure.Instance = TIMERx;

	TIM_Base_InitTypeDef	TIM_TimeBaseInitStructure;



	TIM_TimeBaseInitStructure.Prescaler = TIM_Prescaler;
	TIM_TimeBaseInitStructure.CounterMode = TIM_CounterMode;
	TIM_TimeBaseInitStructure.Period = TIM_Period;
	TIM_TimeBaseInitStructure.ClockDivision = TIM_ClockDivision;
	TIM_TimeBaseInitStructure.RepetitionCounter = TIM_RepetitionCounter;

	m_init = false;
	m_TIM_THandleStructure.Init = TIM_TimeBaseInitStructure;
}
bool timer::Init()
{

	HAL_TIM_Base_Init(&m_TIM_THandleStructure);

	  m_init = true;
	  return true;
}


void timer::Active(FunctionalState newState)
{

	if(ENABLE == newState)
		HAL_TIM_Base_Start(&m_TIM_THandleStructure);
	else
		HAL_TIM_Base_Stop(&m_TIM_THandleStructure);
}


bool timer::InitInteruption(interruption * ITSuperviseur,IRQn_Type NVIC_IRQChannel,uint32_t NVIC_IRQChannelPreemptionPriority,uint32_t NVIC_IRQChannelSubPriority )
{
	if(0 == ITSuperviseur)
	{
		return false;
	}
	m_NVIC_IRQChannel = NVIC_IRQChannel;
	m_ITSuperviseur = ITSuperviseur;
	m_ITSuperviseur->SetObjetIT(m_NVIC_IRQChannel,NVIC_IRQChannelPreemptionPriority,NVIC_IRQChannelSubPriority ,this);

    HAL_TIM_Base_Start_IT(&m_TIM_THandleStructure);

    NVIC_ClearPendingIRQ(m_NVIC_IRQChannel);
}

void timer::ActiveInteruption(FunctionalState NewState )
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



void timer::IRQ()
{
	 HAL_TIM_IRQHandler(&m_TIM_THandleStructure);

}

void timer::CallbackInteruption(void * Handle)
{

	 NVIC_ClearPendingIRQ(m_NVIC_IRQChannel);
}

