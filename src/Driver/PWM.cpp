/*
 * PWM.cpp
 *
 *  Created on: 26 juil. 2015
 *      Author: jul
 */
#include "Driver/objet.h"
#include "Driver/interrupt.h"
#include "Driver/PWM.h"

PWM::PWM():timer() {
	// TODO Auto-generated constructor stub

}

PWM::~PWM() {
	// TODO Auto-generated destructor stub
}

PWM::PWM(TIM_TypeDef* TIMERx,uint32_t TIM_Prescaler ,uint32_t TIM_CounterMode, uint32_t TIM_Period, uint32_t TIM_ClockDivision,uint32_t TIM_RepetitionCounter, HAL_TIM_ActiveChannel channel):timer(TIMERx,TIM_Prescaler,TIM_CounterMode,TIM_Period,TIM_ClockDivision,TIM_RepetitionCounter,channel)
{

/*
	m_TIM_THandleStructure.Instance = TIMERx;

	TIM_Base_InitTypeDef	TIM_TimeBaseInitStructure;



	TIM_TimeBaseInitStructure.Prescaler = TIM_Prescaler;
	TIM_TimeBaseInitStructure.CounterMode = TIM_CounterMode;
	TIM_TimeBaseInitStructure.Period = TIM_Period;
	TIM_TimeBaseInitStructure.ClockDivision = TIM_ClockDivision;
	TIM_TimeBaseInitStructure.RepetitionCounter = TIM_RepetitionCounter;

	m_init = false;
	m_TIM_THandleStructure.Init = TIM_TimeBaseInitStructure;
	m_TIM_THandleStructure.Channel = channel;
*/
}

bool PWM::ConfigChannel(uint32_t OCMode, float Duty, uint32_t OCPolarity, uint32_t OCNPolarity,uint32_t OCFastMode ,uint32_t OCIdleState, uint32_t OCNIdleState, uint32_t channel )
{

	uint32_t cmp = 0;
	m_Channel = channel;
	m_hTyeOC.OCMode 		= OCMode;
	cmp = ( (m_TIM_THandleStructure.Init.Period - 1 ) * Duty) / 100 ;
	m_hTyeOC.Pulse = cmp;
	m_hTyeOC.OCPolarity 	= OCPolarity;
	m_hTyeOC.OCNPolarity 	= OCNPolarity;
	m_hTyeOC.OCFastMode 	= OCFastMode;
	m_hTyeOC.OCIdleState	= OCIdleState;
	m_hTyeOC.OCNIdleState	= OCNIdleState;

}

void PWM::SetGpio(Gpio * Output )
{
	if(0 != Output)
	{
		m_Output = Output;
	}
}

bool PWM::UpdateDutyCycle(float Duty)
{
	uint32_t cmp = 0;

	Active(DISABLE);
	cmp =(uint32_t) ( (m_TIM_THandleStructure.Init.Period -1) * Duty) / 100.0f ;
	m_hTyeOC.Pulse = cmp;
	HAL_TIM_PWM_ConfigChannel(&m_TIM_THandleStructure,&m_hTyeOC,m_Channel);

	Active(ENABLE);

}
bool PWM::Init()
{
	m_Output->Init();
	HAL_TIM_PWM_Init (&m_TIM_THandleStructure);
	HAL_TIM_PWM_ConfigChannel(&m_TIM_THandleStructure,&m_hTyeOC,m_Channel);
	m_init = true;
	return true;
}


void PWM::Active(FunctionalState newState)
{

	if(ENABLE == newState)
		HAL_TIM_PWM_Start(&m_TIM_THandleStructure,m_Channel);
	else
		HAL_TIM_PWM_Stop(&m_TIM_THandleStructure,m_Channel);
}


bool PWM::InitInteruption(interruption * ITSuperviseur,IRQn_Type NVIC_IRQChannel,uint32_t NVIC_IRQChannelPreemptionPriority,uint32_t NVIC_IRQChannelSubPriority )
{
	if(0 == ITSuperviseur)
	{
		return false;
	}

	m_NVIC_IRQChannel = NVIC_IRQChannel;
	m_ITSuperviseur = ITSuperviseur;
	m_ITSuperviseur->SetObjetIT(m_NVIC_IRQChannel,NVIC_IRQChannelPreemptionPriority,NVIC_IRQChannelSubPriority ,this);

    HAL_TIM_PWM_Start_IT(&m_TIM_THandleStructure,m_Channel);

    NVIC_ClearPendingIRQ(m_NVIC_IRQChannel);
}

void PWM::ActiveInteruption(FunctionalState NewState )
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



void PWM::IRQ()
{
	 HAL_TIM_IRQHandler(&m_TIM_THandleStructure);

}

void PWM::CallbackInteruption(void * Handle)
{

	 NVIC_ClearPendingIRQ(m_NVIC_IRQChannel);
}

