
//Output Data Rate (ODR)

typedef enum
{
	ODR_Power_Down = 0,
	ODR_3_125HZ = 1,
	ODR_6_25HZ = 2,
	ODR_12_5HZ = 3,
	ODR_25HZ = 4,
	ODR_50HZ = 5,
	ODR_100HZ = 6,
	ODR_400HZ = 7,
	ODR_800HZ = 8,
	ODR_1600HZ = 9,

} ACC_ODR;

typedef enum
{
	BW_800_HZ = 0,
	BW_400_HZ = 1,
	BW_200_HZ = 2,
	BW_50_HZ = 3,


} ACC_BW;

typedef enum
{
	FSCALE_2G = 0,
	FSCALE_4G = 1,
	FSCALE_6G = 2,
	FSCALE_8G = 3,
	FSCALE_16G = 4,
} ACC_FSCALE;

typedef enum
{
	ST_NORMAL		 = 0,
	ST_POSITIVE_SIGN = 1,
	ST_NEGATIVE_SIGN = 2,
	ST_NOT_ALLOWED 	 = 3,

} ACC_ST;

typedef enum
{
	SIM_4 = 0,
	SIM_3 = 1,
} ACC_SIM;





#define INFO01				0x0D
#define INFO02				0x0E
#define WHO_AM_I			0x0F


#define CTRL_REG1			0x21
#define CTRL_REG2			0x22
#define CTRL_REG3			0x23
#define CTRL_REG4	 		0x20
#define CTRL_REG5	 		0x24
#define CTRL_REG6	 		0x25
#define STATUS		 		0x27
#define OUT_T		 		0x0C

#define OFF_X		 		0x10
#define OFF_Y				0x11
#define OFF_Z				0x12
#define CS_X		 		0x13
#define CS_Y				0x14
#define CS_Z				0x15

#define LC_L				0x16
#define LC_H				0x17
#define STAT				0x18

#define VFC_1				0x1B
#define VFC_2	 			0x1C
#define VFC_3	 			0x1D
#define VFC_4	 			0x1E

#define THRS3	 			0x1F

#define OUT_X_L				0x28
#define OUT_X_H				0x29
#define OUT_Y_L				0x2A
#define OUT_Y_H				0x2B
#define OUT_Z_L				0x2C
#define OUT_Z_H				0x2D

#define FIFO_CTRL			0x2E
#define FIFO_SRC			0x2F

#define ST01_1				0x40
#define ST02_1				0x41
#define ST03_1				0x42
#define ST04_1				0x43
#define ST05_1				0x44
#define ST06_1				0x45
#define ST07_1				0x46
#define ST08_1				0x47
#define ST09_1				0x48
#define ST10_1				0x49
#define ST11_1				0x4A
#define ST12_1				0x4B
#define ST13_1				0x4C
#define ST14_1				0x4D
#define ST15_1				0x4E
#define ST16_1				0x4F

#define ST01				0x60
#define ST02				0x61
#define ST03				0x62
#define ST04				0x63
#define ST05				0x64
#define ST06				0x65
#define ST07				0x66
#define ST08				0x67
#define ST09				0x68
#define ST10				0x69
#define ST11				0x6A
#define ST12				0x6B
#define ST13				0x6C
#define ST14				0x6D
#define ST15				0x6E
#define ST16				0x6F


#define TIM4_1				0x50
#define TIM4_2				0x70


#define TIM3_1				0x51
#define TIM3_2				0x71

#define TIM2_1_L			0x52
#define TIM2_1_H			0x53
#define TIM1_1_L			0x54
#define TIM1_1_H			0x55
#define TIM2_2_L			0x72
#define TIM2_2_H			0x73
#define TIM1_2_L			0x74
#define TIM1_2_H			0x75

#define THRS2_1				0x56
#define THRS1_1				0x57
#define THRS2_2				0x76
#define THRS1_2				0x77

#define MASK1_B				0x59
#define MASK1_A				0x5A

#define MASK2_B				0x79
#define MASK2_A				0x7A
#define SETT1				0x5B
#define PR1					0x5C
#define TC1_L				0x5D
#define TC1_H				0x5E
#define OUTS1				0x5F
#define PEAK1				0x19

#define SETT2				0x7B
#define PR2					0x7C
#define TC2_L				0x7D
#define TC2_H				0x7E
#define OUTS2				0x7F
#define PEAK2				0x1A
#define DES2				0x78


class LIS3DSH
{
	private:
	Gpio * 		m_CS;
	uint8_t 	m_Reg4;
	uint8_t 	m_Reg5;
	uint8_t 	m_Reg3;
	Spi *		m_Spi;

	public:
	LIS3DSH();
	~LIS3DSH(){};
	void init();
	void SetCS(Gpio * CS);
	void SetSPI(Spi * spi);
	void SetCTRLReg4(ACC_ODR odr,uint8_t BDU,uint8_t AXE);
	void SetCTRLReg5(ACC_BW BW,ACC_FSCALE FSCALE,ACC_ST ST,ACC_SIM SIM);
	void SetCTRLReg3(uint8_t DR_EN, uint8_t IEA, uint8_t IEL,uint8_t INT2_EN,uint8_t INT1_EN, uint8_t VFILT ,uint8_t STRT );
	void SPI_LIS3DSH_send(uint8_t address, uint8_t data);
	uint8_t SPI_LIS3DSH_read(uint8_t address);

};
