//
// This file is part of the GNU ARM Eclipse distribution.
// Copyright (c) 2014 Liviu Ionescu.
//

// ----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include "diag/Trace.h"

#include "Seconde.h"
#include "Gpio.h"
#include "Usart.h"
#include "Uart.h"
#include "timer.h"
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
timer Timer2(TIM2,42000 - 1,TIM_COUNTERMODE_UP,1000 - 1,TIM_CLOCKDIVISION_DIV1,0);

Gpio Ledred(GPIOD,GPIO_PIN_14,GPIO_MODE_OUTPUT_PP,0,GPIO_SPEED_FAST,GPIO_NOPULL);


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

  // At this stage the system clock should have already been configured
  // at high speed.
  trace_printf("System clock: %uHz\n", SystemCoreClock);

  Seconde timerSeconde;
  timerSeconde.start();



  //Preparation de la CLock
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  /* Enable USART1 clock */
  __UART4_CLK_ENABLE();

  /* Enable TIMER clock */
  __TIM2_CLK_ENABLE();


  uint8_t Message2[7];
  uint8_t Message[] = "Hello\n\0";
  uint16_t size 	= 7;


  //GPIO de LED
  Gpio Ledblue(GPIOD,GPIO_PIN_15,GPIO_MODE_OUTPUT_PP,0,GPIO_SPEED_FAST,GPIO_NOPULL);
  Gpio Ledgreen(GPIOD,GPIO_PIN_12,GPIO_MODE_OUTPUT_PP,0,GPIO_SPEED_FAST,GPIO_NOPULL);
  Gpio Ledorange(GPIOD,GPIO_PIN_13,GPIO_MODE_OUTPUT_PP,0,GPIO_SPEED_FAST,GPIO_NOPULL);


  // Pramétrage de L'uart
  Gpio TX(GPIOC,GPIO_PIN_10,GPIO_MODE_AF_PP,GPIO_AF8_UART4,GPIO_SPEED_FAST,GPIO_PULLUP);
  Gpio RX(GPIOC,GPIO_PIN_11,GPIO_MODE_AF_PP,GPIO_AF8_UART4,GPIO_SPEED_FAST,GPIO_PULLUP);
  Uart4.SetGpio(&TX,&RX);


  // Perform all necessary initialisations
  Ledgreen.Init();
  Ledblue.Init();
  Ledred.Init();
  Ledorange.Init();
  Uart4.Init();
  Timer2.Init();

  Uart4.Active(ENABLE);
  Timer2.Active(ENABLE);


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

	  Ledorange.WriteBit(GPIO_PIN_SET);
      Ledblue.WriteBit(GPIO_PIN_SET);
    //  Ledred.WriteBit(GPIO_PIN_SET);
      Ledgreen.WriteBit(GPIO_PIN_SET);
      //envoie du message
      //Uart4.Send(Message,size,999);


      timerSeconde.sleep(BLINK_ON_TICKS);


	  Ledorange.WriteBit(GPIO_PIN_RESET);
      Ledblue.WriteBit(GPIO_PIN_RESET);
    //  Ledred.WriteBit(GPIO_PIN_RESET);
      Ledgreen.WriteBit(GPIO_PIN_RESET);
      timerSeconde.sleep(BLINK_OFF_TICKS);
      ++seconds;

      // Count seconds on the trace device.
      trace_printf("Second %u\n", seconds);
    }
  // Infinite loop, never return.
}
extern "C"
{
	void UART4_IRQHandler(void)
	{
		Uart4.IRQ();

	}
	void TIM2_IRQHandler(void)
	{
		Timer2.IRQ();

	}
}

#pragma GCC diagnostic pop



// ----------------------------------------------------------------------------
