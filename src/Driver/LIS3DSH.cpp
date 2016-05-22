#include "Driver/objet.h"
#include "Driver/Gpio.h"
#include "Driver/Spi.h"
#include "Driver/LIS3DSH.h"



LIS3DSH::LIS3DSH()
{
	m_CS = 0;
	m_Reg4 = 0;
	m_Reg5 = 0;
	m_Reg3 = 0;
	m_Spi = 0;
}

void LIS3DSH::init()
{
	//Initilaisation des pins
	m_CS->Init();
	m_Spi->Init();

	//Mise à 1  de CS
	m_CS->WriteBit(GPIO_PIN_SET);
	m_Spi->Active(ENABLE);
}

void LIS3DSH::SetSPI(Spi * spi)
{
	m_Spi = spi;
}

void LIS3DSH::SetCS(Gpio * CS)
{
	m_CS = CS;
}

void LIS3DSH::SetCTRLReg4(ACC_ODR odr,uint8_t BDU,uint8_t AXE)
{
	if( BDU <= 1 )
	{
		m_Reg4 = AXE | (BDU << 3 ) |( odr << 4 );
	}
	else
		m_Reg4 = 0;

	SPI_LIS3DSH_send(CTRL_REG4,m_Reg4);
}


void LIS3DSH::SetCTRLReg5(ACC_BW BW,ACC_FSCALE FSCALE,ACC_ST ST,ACC_SIM SIM)
{

		m_Reg5 = (BW<< 6) | (FSCALE << 3 ) |( ST << 1 ) | SIM;

		SPI_LIS3DSH_send(CTRL_REG5,m_Reg5);
}


void LIS3DSH::SetCTRLReg3(uint8_t DR_EN, uint8_t IEA, uint8_t IEL,uint8_t INT2_EN,uint8_t INT1_EN, uint8_t VFILT ,uint8_t STRT )
{
	if( (DR_EN <= 1) |(DR_EN <= 1) | (IEA <= 1) |(IEL <= 1) |(INT2_EN <= 1) |(INT1_EN <= 1) | (VFILT <= 1) | (STRT <= 1)  )
	{
		m_Reg3 = STRT | (VFILT<<2) | (INT1_EN<<3) | (INT2_EN <<4) | (IEL <<5) | (IEA <<6) | (DR_EN <<7);
	}

	SPI_LIS3DSH_send(CTRL_REG3,m_Reg3);
}

void LIS3DSH::SPI_LIS3DSH_send(uint8_t address, uint8_t data)
{
	  m_CS->WriteBit(GPIO_PIN_RESET);
	  uint8_t dt;
	  m_Spi->Send(&address,1,99);
	  //m_Spi->Read(&dt,1,999);

	  m_Spi->Send(&data,1,99);
	  //m_Spi->Read(&dt,1,999);

	  m_CS->WriteBit(GPIO_PIN_SET);
}


uint8_t LIS3DSH::SPI_LIS3DSH_read(uint8_t address)
{
	uint8_t data;
	m_CS->WriteBit(GPIO_PIN_RESET);

    address = 0x80 | address;                         // 0b10 - reading and clearing status

    m_Spi->Send(&address,1,99);

    m_Spi->Read(&data,1,99);
    uint8_t addresss = 0;

    m_Spi->Send(&addresss,1,99);

    m_CS->WriteBit(GPIO_PIN_SET);

  return  data;
}


int16_t LIS3DSH::GetXg()
{
	uint8_t MSB, LSB;
	MSB = SPI_LIS3DSH_read(OUT_X_H);      // X-axis MSB
	LSB = SPI_LIS3DSH_read(OUT_X_L);      // X-axis LSB
	return (MSB << 8) | (LSB);                // Merging

}

int16_t LIS3DSH::GetYg()
{
	uint8_t MSB, LSB;
	MSB = SPI_LIS3DSH_read(OUT_Y_H);      // Y-axis MSB
	LSB = SPI_LIS3DSH_read(OUT_Y_L);      // Y-axis LSB
	return (MSB << 8) | (LSB);                // Merging

}

int16_t LIS3DSH::GetZg()
{
	uint8_t MSB, LSB;
	MSB = SPI_LIS3DSH_read(OUT_Z_H);      // Z-axis MSB
	LSB = SPI_LIS3DSH_read(OUT_Z_L);      // Z-axis LSB
	return (MSB << 8) | (LSB);                // Merging

}
