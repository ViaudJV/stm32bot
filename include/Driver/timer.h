
#include "stm32f4xx.h"
#include "stm32f4xx_hal_tim.h"
//#include "misc.h"
#include "objet.h"
#include "interrupt.h"
#ifndef __TIMER_H
#define __TIMER_H



class timer : public objet
{
protected:
	interruption *			m_ITSuperviseur;
	bool 					m_init;
	IRQn_Type 				m_NVIC_IRQChannel;
	TIM_HandleTypeDef		m_TIM_THandleStructure;
public :
	timer();
	timer(TIM_TypeDef* TIMERx,uint32_t TIM_Prescaler ,uint32_t TIM_CounterMode, uint32_t TIM_Period, uint32_t TIM_ClockDivision,uint32_t TIM_RepetitionCounter, HAL_TIM_ActiveChannel Channel);
	~timer(){};
	void SetTimer(TIM_TypeDef* TIMERx,uint16_t TIM_Prescaler ,uint16_t TIM_CounterMode, uint32_t TIM_Period, uint16_t TIM_ClockDivision,uint8_t TIM_RepetitionCounter );
	bool Init();
	void Active(FunctionalState newState);
	bool InitInteruption(interruption * ITSuperviseur,IRQn_Type NVIC_IRQChannel,uint32_t NVIC_IRQChannelPreemptionPriority,uint32_t NVIC_IRQChannelSubPriority );
	void ActiveInteruption(FunctionalState NewState );
	void SetAutoreload( uint32_t TIM_Period);
	bool SetCallback(objet * p_Callback);
	void CallbackInteruption(void * Handle);
	void IRQ();
};





#endif






