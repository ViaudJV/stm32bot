


#ifndef __INTERRUPTION_H
#define __INTERRUPTION_H


class interruption : public objet
{
private:
//Objet concernant les it de type usart
	objet * m_pusart1;
	objet * m_pusart2;
	objet * m_pusart3;
	objet * m_puart4;
	objet * m_puart5;
	objet * m_pusart6;
	//Objet concernant les it de type timer
	objet * m_ptimer1;
	objet * m_ptimer2;
	objet * m_ptimer3;
	objet * m_ptimer4;
	objet * m_ptimer5;
	objet * m_ptimer6;
	objet * m_ptimer7;
	objet * m_ptimer8;
	objet * m_ptimer9;
	objet * m_ptimer10;
	objet * m_ptimer11;
	objet * m_ptimer12;
	objet * m_ptimer13;
	objet * m_ptimer14;


public:

	interruption();
	~interruption(){};
	bool ActiveIT(IRQn_Type NVIC_IRQChannel);
	bool DesactiveIT(IRQn_Type NVIC_IRQChannel);
	bool SetObjetIT(uint32_t NVIC_IRQChannel,uint32_t NVIC_IRQChannelPreemptionPriority,uint32_t NVIC_IRQChannelSubPriority , objet * pobjet);

	void CallbackInteruption(UART_HandleTypeDef *UartHandle);
	void CallbackInteruption(TIM_HandleTypeDef *TimeHandle);
};


#endif
