
#include "stm32f4xx_hal_spi.h"
#include "interrupt.h"
#ifndef __SPI_H
#define __SPI_H


class Spi : public objet
{
private:

	SPI_HandleTypeDef m_SPI_HandleTypeDefStruct;
	SPI_TypeDef* m_SPIx;
	bool 	m_init;
	Gpio * 	m_SCL_SPC;
	Gpio * 	m_SDO;
	Gpio * 	m_SDA_SDI_SDO;
	uint8_t m_GPIO_AFX;
	IRQn_Type 				m_NVIC_IRQChannel;
	interruption *	m_ITSuperviseur;

public :
	Spi();
	Spi(SPI_TypeDef* SPIx,uint32_t SPI_Mode, uint32_t SPI_Direction , uint16_t SPI_DataSize, uint32_t SPI_CPOL,uint32_t SPI_CPHA,uint32_t SPI_NSS,uint32_t SPI_BaudRatePrescaler,uint32_t SPI_FirstBit,uint32_t SPI_TIMode,uint32_t SPI_CRCCalculation,uint32_t  SPI_CRCPolynomial);
	~Spi(){};
	bool SetSpi(SPI_TypeDef* SPIx,uint32_t SPI_Mode, uint32_t SPI_Direction , uint16_t SPI_DataSize, uint32_t SPI_CPOL,uint32_t SPI_CPHA,uint32_t SPI_NSS,uint32_t SPI_BaudRatePrescaler,uint32_t SPI_FirstBit,uint32_t SPI_TIMode,uint32_t SPI_CRCCalculation,uint32_t  SPI_CRCPolynomial);
	bool SetGpio(Gpio * SCL_SPC, Gpio * SDO,Gpio * SDA_SDI_SDO );
	bool Init();
	HAL_StatusTypeDef Send(uint8_t * Data, uint16_t Size, uint32_t Timeout);
	HAL_StatusTypeDef Read(uint8_t * Data, uint16_t Size, uint32_t Timeout);
	HAL_SPI_StateTypeDef GetFlagStatus();
	void Active(FunctionalState newState);
	bool InitInteruption(interruption * ITSuperviseur,IRQn_Type NVIC_IRQChannel,uint32_t NVIC_IRQChannelPreemptionPriority,uint32_t NVIC_IRQChannelSubPriority );
	void ActiveInteruption(FunctionalState NewState );
	void CallbackInteruption(void * handle);
};





#endif






