//
// This file is part of the GNU ARM Eclipse distribution.
// Copyright (c) 2014 Liviu Ionescu.
//

// ----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include "diag/Trace.h"
#include "Driver/PWM.h"
#include "Seconde.h"
#include "Driver/Gpio.h"
#include "Driver/Usart.h"
#include "Driver/Uart.h"
#include "Driver/timer.h"
#include "Driver/Spi.h"
#include "Driver/LIS3DSH.h"
#include "math.h"
// ----------------------------------------------------------------------------
//
// Standalone STM32F4 led blink sample (trace via DEBUG).
//
// In debug configurations, demonstrate how to print a greeting message
// on the trace device. In release configurations the message is
// simply discarded.
//
// Then demonstrates how to blink a led with 1Hz, using a
// continuous loop and SysTick delays.
//
// Trace support is enabled by adding the TRACE macro definition.
// By default the trace messages are forwarded to the DEBUG output,
// but can be rerouted to any device or completely suppressed, by
// changing the definitions required in system/src/diag/trace_impl.c
// (currently OS_USE_TRACE_ITM, OS_USE_TRACE_SEMIHOSTING_DEBUG/_STDOUT).
//

#define   APB1_FREQ        42000000                           // Clock driving TIM3
#define   CNT_FREQ         21000000                           // TIM3 counter clock (prescaled APB1)
#define   IT_PER_SEC       1                               // Interrupts per second
#define   TIM3_PULSE       ((CNT_FREQ) / (IT_PER_SEC))        // Output compare reg value
#define   TIM_PRESCALER    (((APB1_FREQ) / (CNT_FREQ))-1)     // APB1 prescaler


uint8_t i;
uint8_t MSB, LSB;
int16_t Xg, Zg;                                 // 16-bit values from accelerometer
int16_t x_array[100];                           // 100 samples for X-axis
int16_t z_array[100];                           // 100 samples for Z-axis
float x_average;                                // x average of samples
float z_average;                                // z average of samples
float zx_theta;                                 // degrees between Z and X planes
char print_buffer[20];                          // printing the values in Putty

extern "C"
{
	void Sort_Signed(int16_t A[], uint8_t L);       // Bubble sort min to max, input: Array/Length
float  gToDegrees(float V, float H);             // output: degrees between two planes, input: Vertical/Horizontal force

}


// Definitions visible only within this translation unit.
namespace
{
  // ----- Timing definitions -------------------------------------------------

  // Keep the LED on for 2/3 of a second.
  constexpr Seconde::ticks_t BLINK_ON_TICKS = Seconde::FREQUENCY_HZ * 2 / 3;
  constexpr Seconde::ticks_t BLINK_OFF_TICKS = Seconde::FREQUENCY_HZ
      - BLINK_ON_TICKS;
}

// ----- main() ---------------------------------------------------------------

// Sample pragmas to cope with warnings. Please note the related line at
// the end of this function, used to pop the compiler diagnostics status.
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wmissing-declarations"
#pragma GCC diagnostic ignored "-Wreturn-type"

interruption SuperIT;
//Usart Usart6(USART6,(uint32_t) 9600,USART_LASTBIT_DISABLE,USART_PHASE_1EDGE,USART_POLARITY_LOW,USART_MODE_TX_RX,USART_PARITY_NONE, USART_STOPBITS_1, USART_WORDLENGTH_8B);
Uart Uart4(UART4,(uint32_t) 9600,UART_MODE_TX_RX,UART_PARITY_NONE, UART_STOPBITS_1, UART_WORDLENGTH_8B,UART_HWCONTROL_NONE,UART_OVERSAMPLING_8);
// Pramétrage du Timer
timer Timer2(TIM2,42000 - 1,TIM_COUNTERMODE_UP,1000 - 1,TIM_CLOCKDIVISION_DIV1,0,HAL_TIM_ACTIVE_CHANNEL_CLEARED);
PWM PWMBlue(TIM4,42000 - 1,TIM_COUNTERMODE_UP,1000 - 1,TIM_CLOCKDIVISION_DIV1,0,HAL_TIM_ACTIVE_CHANNEL_4);
Gpio Ledred(GPIOD,GPIO_PIN_14,GPIO_MODE_OUTPUT_PP,0,GPIO_SPEED_FAST,GPIO_NOPULL);
Spi spi_LIS3DSH(SPI1,SPI_MODE_MASTER,SPI_DIRECTION_2LINES,SPI_DATASIZE_8BIT,SPI_POLARITY_HIGH,SPI_PHASE_2EDGE,SPI_NSS_SOFT|SPI_NSS_HARD_INPUT,SPI_BAUDRATEPRESCALER_256,SPI_FIRSTBIT_MSB,SPI_TIMODE_DISABLE,SPI_CRCCALCULATION_DISABLE,(uint32_t)0);
LIS3DSH mems;

uint32_t Duty;

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *UsartHandle)
{
	//Uart4.CallbackInteruption(UsartHandle);
	SuperIT.CallbackInteruption(UsartHandle);

}

void
HAL_TIM_PeriodElapsedCallback (TIM_HandleTypeDef *
htim)
{
	Ledred.Toggle();
	SuperIT.CallbackInteruption(htim);

}

int main(int argc, char* argv[])
{
  // Send a greeting to the trace device (skipped on Release).
  trace_puts("Hello ARM World!");

  Duty = 50;

  // At this stage the system clock should have already been configured
  // at high speed.
  trace_printf("System clock: %uHz\n", SystemCoreClock);


  Seconde timerSeconde;
  timerSeconde.start();



  //Preparation de la CLock
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();

  /* Enable USART1 clock */
  __UART4_CLK_ENABLE();

  /* Enable SPI1 clock */
  __SPI1_CLK_ENABLE();


  /* Enable TIMER clock */
  __TIM2_CLK_ENABLE();
  __TIM4_CLK_ENABLE();

  //



  uint8_t Message2[7];
  uint8_t Message[] = "Hello\n\0";
  uint16_t size 	= 7;


  //GPIO de LED
  Gpio Ledgreen(GPIOD,GPIO_PIN_12,GPIO_MODE_OUTPUT_PP,0,GPIO_SPEED_FAST,GPIO_NOPULL);
  Gpio Ledorange(GPIOD,GPIO_PIN_13,GPIO_MODE_OUTPUT_PP,0,GPIO_SPEED_FAST,GPIO_NOPULL);


  // Paramétrage de L'uart
  Gpio TX(GPIOC,GPIO_PIN_10,GPIO_MODE_AF_PP,GPIO_AF8_UART4,GPIO_SPEED_FAST,GPIO_PULLUP);
  Gpio RX(GPIOC,GPIO_PIN_11,GPIO_MODE_AF_PP,GPIO_AF8_UART4,GPIO_SPEED_FAST,GPIO_PULLUP);
  Uart4.SetGpio(&TX,&RX);


  // Paramétrage du SPI pour LIS3DSH
  Gpio SCK(GPIOA, GPIO_PIN_5,GPIO_MODE_AF_PP,GPIO_AF5_SPI1,GPIO_SPEED_FAST,GPIO_NOPULL);
  Gpio MOSI(GPIOA, GPIO_PIN_7,GPIO_MODE_AF_PP,GPIO_AF5_SPI1,GPIO_SPEED_FAST,GPIO_NOPULL);
  Gpio MISO(GPIOA, GPIO_PIN_6,GPIO_MODE_AF_PP,GPIO_AF5_SPI1,GPIO_SPEED_FAST,GPIO_NOPULL);
  spi_LIS3DSH.SetGpio(&SCK,&MISO,&MOSI);

  //Paramétrage du Cs du LIS3DSH
  Gpio CSMems(GPIOE, GPIO_PIN_3,GPIO_MODE_OUTPUT_PP,0,GPIO_SPEED_FAST,GPIO_PULLUP);

  mems.SetSPI(&spi_LIS3DSH);
  mems.SetCS(&CSMems);
  mems.init();

  mems.SetCTRLReg3(1,1,0,0,1,0,1); 		// resetting the accelerometer internal circuit
  mems.SetCTRLReg4(ODR_100HZ,0,0x7);	// 100Hz data update rate, block data update disable, x/y/z enabled
  mems.SetCTRLReg5(BW_800_HZ,FSCALE_16G,ST_NORMAL,SIM_4);// Anti aliasing filter bandwidth 800Hz, 16G (very sensitive), no self-test, 4-wire interface
  mems.SPI_LIS3DSH_send(0x10,0x00);		//OFF_X  // Output(X) = Measurement(X) - OFFSET(X) * 32;
  mems.SPI_LIS3DSH_send(0x11,0x00);		//OFF_Y  // Output(Y) = Measurement(Y) - OFFSET(Y) * 32;
  mems.SPI_LIS3DSH_send(0x12,0x00);		//OFF_Z  // Output(Z) = Measurement(Z) - OFFSET(Z) * 32;

  //Paremétrage du PWM
  Gpio Ledblue(GPIOD,GPIO_PIN_15,GPIO_MODE_AF_PP,GPIO_AF2_TIM4,GPIO_SPEED_HIGH,GPIO_NOPULL);
  PWMBlue.SetGpio(&Ledblue);
  PWMBlue.ConfigChannel(TIM_OCMODE_PWM1, Duty, TIM_OCPOLARITY_HIGH, TIM_OCNPOLARITY_HIGH,TIM_OCFAST_DISABLE ,TIM_CCx_ENABLE,TIM_OCNIDLESTATE_RESET,TIM_CHANNEL_4);


  // Perform all necessary initialisations
  Ledgreen.Init();
//  Ledblue.Init();
  PWMBlue.Init();
  Ledred.Init();
  Ledorange.Init();
  Uart4.Init();
  Timer2.Init();
  mems.init();





  Uart4.Active(ENABLE);
  Timer2.Active(ENABLE);
  PWMBlue.Active(ENABLE);



  mems.SetCTRLReg3(1,1,0,0,1,0,1); 		// resetting the accelerometer internal circuit
  mems.SetCTRLReg4(ODR_100HZ,0,0x7);	// 100Hz data update rate, block data update disable, x/y/z enabled
  mems.SetCTRLReg5(BW_800_HZ,FSCALE_16G,ST_NORMAL,SIM_4);// Anti aliasing filter bandwidth 800Hz, 16G (very sensitive), no self-test, 4-wire interface
  mems.SPI_LIS3DSH_send(0x10,0x00);		//OFF_X  // Output(X) = Measurement(X) - OFFSET(X) * 32;
  mems.SPI_LIS3DSH_send(0x11,0x00);		//OFF_Y  // Output(Y) = Measurement(Y) - OFFSET(Y) * 32;
  mems.SPI_LIS3DSH_send(0x12,0x00);		//OFF_Z  // Output(Z) = Measurement(Z) - OFFSET(Z) * 32;



  //Preparation de L'IT
  Timer2.InitInteruption(&SuperIT,TIM2_IRQn,0,1);
  Timer2.ActiveInteruption(ENABLE);

  //Preparation de L'IT
  Uart4.InitInteruption(&SuperIT,UART4_IRQn,0,1);
  Uart4.ActiveInteruption(ENABLE);

  Ledred.WriteBit(GPIO_PIN_RESET);

  uint32_t seconds = 0;

  // Infinite loop
  while (1)
    {
	   for(i = 0; i < 100; i++)                   // getting 100 samples
	    {
	      MSB = mems.SPI_LIS3DSH_read(0x29);      // X-axis MSB
	      LSB = mems.SPI_LIS3DSH_read(0x28);      // X-axis LSB
	      Xg = (MSB << 8) | (LSB);                // Merging
	      x_array[i] = Xg;

	      MSB = mems.SPI_LIS3DSH_read(0x2d);      // Z-axis MSB
	      LSB = mems.SPI_LIS3DSH_read(0x2c);      // Z-axis LSB
	      Zg = (MSB << 8) | (LSB);                // Merging
	      z_array[i] = Zg;
	    }

	    Sort_Signed(x_array, 100);                // Sorting min to max
	    Sort_Signed(z_array, 100);                // Sorting min to ma0x

	    x_average = 0.0f;
	    z_average = 0.0f;
	    for(i = 10; i < 90; i++)                  // removing 10 samples from bottom and 10 from top
	    {
	      x_average += x_array[i];                // summing up
	      z_average += z_array[i];                // summing up
	    }

	    x_average /= 80.0f;                          // dividing by the number of samples used
	    x_average /= -141.0f;                        // converting to meters per second squared

	    z_average /= 80.0f;                          // dividing by the number of samples used
	    z_average /= -141.0f;                        // converting to meters per second squared

	    zx_theta = gToDegrees(z_average,x_average);  // getting the degrees between Z and X planes

	    sprintf(print_buffer, "x: %f\tz: %f\tZ-X: %f", x_average, -z_average, zx_theta);
	    Uart4.Send((uint8_t*)"a\n",2,99);
	   Uart4.Send((uint8_t*)print_buffer,20,99);           // printing in Putty
	 }
	 // Ledorange.WriteBit(GPIO_PIN_SET);
      //Ledblue.WriteBit(GPIO_PIN_SET);
    //  Ledred.WriteBit(GPIO_PIN_SET);
     // Ledgreen.WriteBit(GPIO_PIN_SET);
      //envoie du message
      //Uart4.Send(Message,size,999);


     // timerSeconde.sleep(BLINK_ON_TICKS);


	  //Ledorange.WriteBit(GPIO_PIN_RESET);
      //Ledblue.WriteBit(GPIO_PIN_RESET);
    //  Ledred.WriteBit(GPIO_PIN_RESET);
     // Ledgreen.WriteBit(GPIO_PIN_RESET);
     // timerSeconde.sleep(BLINK_OFF_TICKS);
     // ++seconds;

      // Count seconds on the trace device.
      trace_printf("Second %u\n", seconds);
   //}
  // Infinite loop, never return.
}
extern "C"
{
	void UART4_IRQHandler(void)
	{
		Uart4.IRQ();
		Duty = (Duty + 10);
		if(100 == Duty)
		{
			Duty = 10;
		}
		PWMBlue.UpdateDutyCycle(Duty);

	}
	void TIM2_IRQHandler(void)
	{
		Timer2.IRQ();

	}



void Sort_Signed(int16_t A[], uint8_t L)
{
  uint8_t i = 0;
  uint8_t status = 1;

  while(status == 1)
  {
    status = 0;
    for(i = 0; i < L-1; i++)
    {
      if (A[i] > A[i+1])
      {
        A[i]^=A[i+1];
        A[i+1]^=A[i];
        A[i]^=A[i+1];
        status = 1;
      }
    }
  }
}



float gToDegrees(float Vi, float Hi)               // refer to the orientation pic above
{
	float retval;
    float orientation;

  if (Hi == 0.0f) Hi = 0.001f;                         // preventing division by zero
  if (Vi == 0.0f) Vi = 0.001f;                         // preventing division by zero

  if ((Hi > 0.0f) && (Vi > 0.0f)) orientation = 0.0f;
  if ((Hi < 0.0f) && (Vi > 0.0f)) orientation = 90.0f;
  if ((Hi < 0.0f) && (Vi < 0.0f)) orientation = 180.0f;
  if ((Hi > 0.0f) && (Vi < 0.0f)) orientation = 270.0f;

  retval = ((atanf(Vi/Hi)/3.14159f)*180.0f);
  if (retval < 0) retval += 90.0f;
  retval = fabsf(retval) +  orientation;
  return retval;
}

}



#pragma GCC diagnostic pop



// ----------------------------------------------------------------------------
