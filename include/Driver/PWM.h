/*
 * PWM.h
 *
 *  Created on: 26 juil. 2015
 *      Author: jul
 */

#ifndef PWM_H_
#define PWM_H_

#include "Driver/objet.h"
#include "Driver/interrupt.h"
#include "Driver/timer.h"
#include "Driver/Gpio.h"
class PWM: public timer {

protected:
	TIM_OC_InitTypeDef m_hTyeOC;
	uint32_t m_Channel;
	Gpio * m_Output;
public:
	PWM();
	~PWM();
	bool UpdateDutyCycle(float Duty);
	PWM(TIM_TypeDef* TIMERx,uint32_t TIM_Prescaler ,uint32_t TIM_CounterMode, uint32_t TIM_Period, uint32_t TIM_ClockDivision,uint32_t TIM_RepetitionCounter, HAL_TIM_ActiveChannel Channel);
	bool Init();
	void Active(FunctionalState newState);
	bool InitInteruption(interruption * ITSuperviseur,IRQn_Type NVIC_IRQChannel,uint32_t NVIC_IRQChannelPreemptionPriority,uint32_t NVIC_IRQChannelSubPriority );
	void ActiveInteruption(FunctionalState NewState );
	bool SetCallback(objet * p_Callback);
	void CallbackInteruption(void * Handle);
	void IRQ();
	bool ConfigChannel(uint32_t OCMode, float Duty, uint32_t OCPolarity, uint32_t OCNPolarity,uint32_t OCFastMode ,uint32_t OCIdleState, uint32_t OCNIdleState, uint32_t channel );
	void SetGpio(Gpio * Output );

};

#endif /* PWM_H_ */
