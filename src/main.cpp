//
// This file is part of the GNU ARM Eclipse distribution.
// Copyright (c) 2014 Liviu Ionescu.
//

// ----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include "diag/Trace.h"
#include "Driver/PWM.h"
#include "Driver/Gpio.h"
#include "Driver/Usart.h"
#include "Driver/Uart.h"
#include "Driver/timer.h"
#include "Driver/Spi.h"
#include "Driver/LIS3DSH.h"
#include "math.h"
#include "../FreeRTOS/Source/CMSIS_RTOS/cmsis_os.h"
#include "ToggleLed.h"
#include "stm32f4xx_hal_rcc.h"

#include "cortexm/ExceptionHandlers.h"
///* Private variables ---------------------------------------------------------*/
osThreadId firstTaskHandle;
osThreadId secondTaskHandle;
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
int16_t Xg, Zg;                                 // 16-bit values from accelerometer
int16_t x_array[100];                           // 100 samples for X-axis
int16_t z_array[100];                           // 100 samples for Z-axis
float x_average;                                // x average of samples
float z_average;                                // z average of samples
float zx_theta;                                 // degrees between Z and X planes
char print_buffer[20];                          // printing the values in Putty



//GPIO de LED
  Gpio Ledgreen(GPIOD,GPIO_PIN_12,GPIO_MODE_OUTPUT_PP,0,GPIO_SPEED_FAST,GPIO_NOPULL);
  Gpio Ledorange(GPIOD,GPIO_PIN_13,GPIO_MODE_OUTPUT_PP,0,GPIO_SPEED_FAST,GPIO_NOPULL);
  Gpio Ledred(GPIOD,GPIO_PIN_14,GPIO_MODE_OUTPUT_PP,0,GPIO_SPEED_FAST,GPIO_NOPULL);
  Gpio Ledblue(GPIOD,GPIO_PIN_15,GPIO_MODE_OUTPUT_PP,0,GPIO_SPEED_FAST,GPIO_NOPULL);
  interruption SuperIT;
  //Usart Usart6(USART6,(uint32_t) 9600,USART_LASTBIT_DISABLE,USART_PHASE_1EDGE,USART_POLARITY_LOW,USART_MODE_TX_RX,USART_PARITY_NONE, USART_STOPBITS_1, USART_WORDLENGTH_8B);
  Uart Uart4(UART4,(uint32_t) 9600,UART_MODE_TX_RX,UART_PARITY_NONE, UART_STOPBITS_1, UART_WORDLENGTH_8B,UART_HWCONTROL_NONE,UART_OVERSAMPLING_8);
  // Pramétrage du Timer
  timer Timer2(TIM2,42000 - 1,TIM_COUNTERMODE_UP,1000 - 1,TIM_CLOCKDIVISION_DIV1,0,HAL_TIM_ACTIVE_CHANNEL_CLEARED);


  uint32_t Duty;

extern "C"
{
	void Sort_Signed(int16_t A[], uint8_t L);       // Bubble sort min to max, input: Array/Length
float  gToDegrees(float V, float H);             // output: degrees between two planes, input: Vertical/Horizontal force

}



// ----- main() ---------------------------------------------------------------

// Sample pragmas to cope with warnings. Please note the related line at
// the end of this function, used to pop the compiler diagnostics status.
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wmissing-declarations"
#pragma GCC diagnostic ignored "-Wreturn-type"






void HAL_UART_RxCpltCallback(UART_HandleTypeDef *UsartHandle)
{
	//Uart4.CallbackInteruption(UsartHandle);
	SuperIT.CallbackInteruption(UsartHandle);

}





int main(int argc, char* argv[])
{
  // Send a greeting to the trace device (skipped on Release).
  trace_puts("Hello ARM World!");

  Duty = 50;

  // At this stage the system clock should have already been configured
  // at high speed.
  trace_printf("System clock: %uHz\n", SystemCoreClock);




  //Preparation de la CLock
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /* Enable USART1 clock */
  __UART4_CLK_ENABLE();


  /* Enable TIMER clock */
  __TIM2_CLK_ENABLE();

  //



  uint8_t Message2[7];
  uint8_t Message[] = "Hello\n\0";
  uint16_t size 	= 7;





  // Paramétrage de L'uart
  Gpio TX(GPIOC,GPIO_PIN_10,GPIO_MODE_AF_PP,GPIO_AF8_UART4,GPIO_SPEED_FAST,GPIO_PULLUP);
  Gpio RX(GPIOC,GPIO_PIN_11,GPIO_MODE_AF_PP,GPIO_AF8_UART4,GPIO_SPEED_FAST,GPIO_PULLUP);
  Uart4.SetGpio(&TX,&RX);



  // Perform all necessary initialisations
  Ledgreen.Init();
 // Ledblue.Init();
  //Ledred.Init();
  Ledorange.Init();

  Uart4.Init();
  Uart4.Active(ENABLE);

  //Preparation de L'IT
  Uart4.InitInteruption(&SuperIT,UART4_IRQn,0,1);
  Uart4.ActiveInteruption(ENABLE);

  Ledorange.WriteBit(GPIO_PIN_SET);
  Ledgreen.WriteBit(GPIO_PIN_RESET);


  uint32_t seconds = 0;

  /* USER CODE BEGIN RTOS_MUTEX */
   /* add mutexes, ... */
   /* USER CODE END RTOS_MUTEX */

   /* USER CODE BEGIN RTOS_SEMAPHORES */
   /* add semaphores, ... */
   /* USER CODE END RTOS_SEMAPHORES */

   /* USER CODE BEGIN RTOS_TIMERS */
   /* start timers, add new ones, ... */
   /* USER CODE END RTOS_TIMERS */

   /* Create the thread(s) */
   /* definition and creation of defaultTask */
//  osThreadDef(firstTask, StartFirstTask, osPriorityNormal, 1, 128);
//  firstTaskHandle = osThreadCreate(osThread(firstTask), NULL);

//  osThreadDef(secondTask, StartSecondTask, osPriorityNormal, 1, 128);
 // secondTaskHandle = osThreadCreate(osThread(secondTask), NULL);

   /* USER CODE BEGIN RTOS_THREADS */
   /* add threads, ... */
   /* USER CODE END RTOS_THREADS */

   /* USER CODE BEGIN RTOS_QUEUES */
   /* add queues, ... */
   /* USER CODE END RTOS_QUEUES */


  ToggleLed TaskLedRedBlue("RED_BLUE");
  ToggleLed TaskLedGreenOrange("GREEN_ORANGE");

  TaskLedRedBlue.Init(&Ledred,&Ledblue,1000);
  TaskLedGreenOrange.Init(&Ledgreen,&Ledorange,2000);


   /* Start scheduler */
   osKernelStart();

   /* We should never get here as control is now taken by the scheduler */

   /* Infinite loop */
   /* USER CODE BEGIN WHILE */
   while (1)
   {
   /* USER CODE END WHILE */
	   Duty = 0;
   /* USER CODE BEGIN 3 */

   }
   /* USER CODE END 3 */

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

	}
	void TIM2_IRQHandler(void)
	{
		Timer2.IRQ();

	}

}




void SysTick_Handler(void)
{
  osSystickHandler();

}


#pragma GCC diagnostic pop



// ----------------------------------------------------------------------------
