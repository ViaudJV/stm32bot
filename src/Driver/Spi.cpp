#include "Driver/objet.h"
#include "Driver/Gpio.h"
#include "Driver/Spi.h"


Spi::Spi()
{
	m_init = false;
	m_SPIx = 0;
	m_SCL_SPC = 0;
	m_SDO = 0;
	m_SDA_SDI_SDO =0;
	m_GPIO_AFX = 0;
}
Spi::Spi(SPI_TypeDef* SPIx,uint32_t SPI_Mode, uint32_t SPI_Direction , uint16_t SPI_DataSize, uint32_t SPI_CPOL,uint32_t SPI_CPHA,uint32_t SPI_NSS,uint32_t SPI_BaudRatePrescaler,uint32_t SPI_FirstBit,uint32_t SPI_TIMode,uint32_t SPI_CRCCalculation,uint32_t  SPI_CRCPolynomial)
{
	m_SPI_HandleTypeDefStruct.Instance 					= SPIx;
	m_SPI_HandleTypeDefStruct.Init.Mode 				= SPI_Mode;
	m_SPI_HandleTypeDefStruct.Init.Direction 			= SPI_Direction;
	m_SPI_HandleTypeDefStruct.Init.DataSize 			= SPI_DataSize;
	m_SPI_HandleTypeDefStruct.Init.CLKPolarity 			= SPI_CPOL;
	m_SPI_HandleTypeDefStruct.Init.CLKPhase 			= SPI_CPHA;
	m_SPI_HandleTypeDefStruct.Init.NSS 					= SPI_NSS;
	m_SPI_HandleTypeDefStruct.Init.BaudRatePrescaler 	= SPI_BaudRatePrescaler;
	m_SPI_HandleTypeDefStruct.Init.FirstBit 			= SPI_FirstBit;
	m_SPI_HandleTypeDefStruct.Init.TIMode 				= SPI_TIMode;
	m_SPI_HandleTypeDefStruct.Init.CRCCalculation		= SPI_CRCCalculation;
	m_SPI_HandleTypeDefStruct.Init.CRCPolynomial		= SPI_CRCPolynomial;


	m_init = false;

}

bool Spi::SetGpio(Gpio * SCL_SPC, Gpio * SDO,Gpio * SDA_SDI_SDO )
{
	if(SCL_SPC != 0 && SDO != 0 && SDA_SDI_SDO != 0)
	{
		m_SCL_SPC = SCL_SPC;
		m_SDO = SDO;
		m_SDA_SDI_SDO = SDA_SDI_SDO;
		return true;
	}
	return false;
}
bool Spi::SetSpi(SPI_TypeDef* SPIx,uint32_t SPI_Mode, uint32_t SPI_Direction , uint16_t SPI_DataSize, uint32_t SPI_CPOL,uint32_t SPI_CPHA,uint32_t SPI_NSS,uint32_t SPI_BaudRatePrescaler,uint32_t SPI_FirstBit,uint32_t SPI_TIMode,uint32_t SPI_CRCCalculation,uint32_t  SPI_CRCPolynomial)
{
	m_SPI_HandleTypeDefStruct.Instance 					= SPIx;
	m_SPI_HandleTypeDefStruct.Init.Mode 				= SPI_Mode;
	m_SPI_HandleTypeDefStruct.Init.Direction 			= SPI_Direction;
	m_SPI_HandleTypeDefStruct.Init.DataSize 			= SPI_DataSize;
	m_SPI_HandleTypeDefStruct.Init.CLKPolarity 			= SPI_CPOL;
	m_SPI_HandleTypeDefStruct.Init.CLKPhase 			= SPI_CPHA;
	m_SPI_HandleTypeDefStruct.Init.NSS 					= SPI_NSS;
	m_SPI_HandleTypeDefStruct.Init.BaudRatePrescaler 	= SPI_BaudRatePrescaler;
	m_SPI_HandleTypeDefStruct.Init.FirstBit 			= SPI_FirstBit;
	m_SPI_HandleTypeDefStruct.Init.TIMode 				= SPI_TIMode;
	m_SPI_HandleTypeDefStruct.Init.CRCCalculation		= SPI_CRCCalculation;
	m_SPI_HandleTypeDefStruct.Init.CRCPolynomial		= SPI_CRCPolynomial;

	return false;
}
bool Spi::Init()
{

	  m_SCL_SPC->Init();
	  m_SDO->Init();
	  m_SDA_SDI_SDO->Init();

	  HAL_SPI_Init(&m_SPI_HandleTypeDefStruct);

	return true;
}

HAL_StatusTypeDef Spi::Send(uint8_t * Data, uint16_t Size, uint32_t Timeout)
{
	return HAL_SPI_Transmit(&m_SPI_HandleTypeDefStruct,Data,Size,Timeout);
}

HAL_StatusTypeDef Spi::Read(uint8_t * Data, uint16_t Size, uint32_t Timeout)
{
	return HAL_SPI_Receive(&m_SPI_HandleTypeDefStruct,Data,Size,Timeout);
}

HAL_SPI_StateTypeDef Spi::GetFlagStatus()
{
	return HAL_SPI_GetState(&m_SPI_HandleTypeDefStruct);
}



void Spi::Active(FunctionalState newState)
{

	if(ENABLE == newState)
		__HAL_SPI_ENABLE(&m_SPI_HandleTypeDefStruct);
	else
		__HAL_SPI_DISABLE(&m_SPI_HandleTypeDefStruct);
}


bool Spi::InitInteruption(interruption * ITSuperviseur,IRQn_Type NVIC_IRQChannel,uint32_t NVIC_IRQChannelPreemptionPriority,uint32_t NVIC_IRQChannelSubPriority )
{
	if(0 == ITSuperviseur)
	{
		return false;
	}

	m_NVIC_IRQChannel = NVIC_IRQChannel;
	m_ITSuperviseur = ITSuperviseur;
	m_ITSuperviseur->SetObjetIT(m_NVIC_IRQChannel,NVIC_IRQChannelPreemptionPriority,NVIC_IRQChannelSubPriority ,this);

    HAL_SPI_IRQHandler(&m_SPI_HandleTypeDefStruct);

    NVIC_ClearPendingIRQ(m_NVIC_IRQChannel);
}

void Spi::ActiveInteruption(FunctionalState NewState )
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



void Spi::CallbackInteruption(void * handle)
{

}
