#include "objet.h"
#include "Gpio.h"
#include "Spi.h"


Spi::Spi()
{
	m_init = false;
	m_SPIx = 0;
	m_SPI_InitTypeDefStruct.Direction = 0;
	m_SPI_InitTypeDefStruct.Mode = 0;
	m_SPI_InitTypeDefStruct.DataSize = 0;
	m_SPI_InitTypeDefStruct.CLKPhase= 0;
	m_SPI_InitTypeDefStruct.CLKPolarity = 0;
	m_SPI_InitTypeDefStruct.NSS = 0;
	m_SPI_InitTypeDefStruct.BaudRatePrescaler = 0;
	m_SPI_InitTypeDefStruct.FirstBit = 0;
	m_SPI_InitTypeDefStruct.CRCPolynomial = 0;
	m_SPI_InitTypeDefStruct.CRCCalculation = 0;
	m_SPI_InitTypeDefStruct.TIMode = 0;
	m_SCL_SPC = 0;
	m_SDO = 0;
	m_SDA_SDI_SDO =0;
	m_GPIO_AFX = 0;
}
Spi::Spi(SPI_TypeDef* SPIx,uint32_t SPI_Direction ,uint32_t SPI_Mode, uint32_t SPI_DataSize, uint32_t SPI_CLKPhase,uint32_t CLKPolarity,uint32_t SPI_CPHA,uint32_t SPI_NSS,uint32_t SPI_BaudRatePrescaler,uint32_t SPI_FirstBit,uint32_t  SPI_CRCPolynomial, uint32_t SPI_CRCCalculation, uint32_t SPI_TIMode,uint8_t GPIO_AFX )
{
	if( SPIx != 0)
	{
		m_SPIx = SPIx;
	}

	m_SPI_InitTypeDefStruct.Direction = SPI_Direction;
	m_SPI_InitTypeDefStruct.Mode = SPI_Mode;
	m_SPI_InitTypeDefStruct.DataSize = SPI_DataSize;
	m_SPI_InitTypeDefStruct.CLKPhase= SPI_CLKPhase;
	m_SPI_InitTypeDefStruct.CLKPolarity = CLKPolarity;
	m_SPI_InitTypeDefStruct.NSS = SPI_NSS;
	m_SPI_InitTypeDefStruct.BaudRatePrescaler = SPI_BaudRatePrescaler;
	m_SPI_InitTypeDefStruct.FirstBit = SPI_FirstBit;
	m_SPI_InitTypeDefStruct.CRCPolynomial = SPI_CRCPolynomial;
	m_SPI_InitTypeDefStruct.CRCCalculation = SPI_CRCCalculation;
	m_SPI_InitTypeDefStruct.TIMode = SPI_TIMode;

	m_init = false;
	m_GPIO_AFX = GPIO_AFX;
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
bool Spi::SetSpi(SPI_TypeDef* SPIx,uint32_t SPI_Direction ,uint32_t SPI_Mode, uint32_t SPI_DataSize, uint32_t SPI_CLKPhase,uint32_t CLKPolarity,uint32_t SPI_CPHA,uint32_t SPI_NSS,uint32_t SPI_BaudRatePrescaler,uint32_t SPI_FirstBit,uint32_t  SPI_CRCPolynomial, uint32_t SPI_CRCCalculation, uint32_t SPI_TIMode,uint8_t GPIO_AFX )
{
	if( 0 == SPIx)
	{
		return false;
	}

	m_SPIx = SPIx;
	m_SPI_InitTypeDefStruct.Direction = SPI_Direction;
	m_SPI_InitTypeDefStruct.Mode = SPI_Mode;
	m_SPI_InitTypeDefStruct.DataSize = SPI_DataSize;
	m_SPI_InitTypeDefStruct.CLKPhase= SPI_CLKPhase;
	m_SPI_InitTypeDefStruct.CLKPolarity = CLKPolarity;
	m_SPI_InitTypeDefStruct.NSS = SPI_NSS;
	m_SPI_InitTypeDefStruct.BaudRatePrescaler = SPI_BaudRatePrescaler;
	m_SPI_InitTypeDefStruct.FirstBit = SPI_FirstBit;
	m_SPI_InitTypeDefStruct.CRCPolynomial = SPI_CRCPolynomial;
	m_SPI_InitTypeDefStruct.CRCCalculation = SPI_CRCCalculation;
	m_SPI_InitTypeDefStruct.TIMode = SPI_TIMode;
	m_GPIO_AFX = GPIO_AFX;

	return false;
}
bool Spi::Init()
{

	  m_SCL_SPC->Init();
	  m_SDO->Init();
	  m_SDA_SDI_SDO->Init();
	  HAL_SPI_Init(SPI_HandleTypeDef *hspi);

	return true;
}

void Spi::Send(uint16_t Data, uint16_t Size, uint32_t Timeout)
{
	HAL_SPI_Transmit(m_SPIx,Data,Size,Timeout);
}

uint16_t Spi::Read()
{
	return SPI_I2S_ReceiveData(m_SPIx);
}

FlagStatus Spi::GetFlagStatus(uint16_t SPI_I2S_FLAG)
{
	return SPI_I2S_GetFlagStatus(m_SPIx,SPI_I2S_FLAG);
}
