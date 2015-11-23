//
// This file is part of the GNU ARM Eclipse distribution.
// Copyright (c) 2014 Liviu Ionescu.
//

#include "Seconde.h"
#include "cortexm/ExceptionHandlers.h"

// ----------------------------------------------------------------------------

volatile Seconde::ticks_t Seconde::ms_delayCount;

// ----------------------------------------------------------------------------

void
Seconde::sleep(ticks_t ticks)
{
  ms_delayCount = ticks;

  // Busy wait until the SysTick decrements the counter to zero.
  while (ms_delayCount != 0u)
    ;
}

// ----- SysTick_Handler() ----------------------------------------------------

extern "C" void
SysTick_Handler(void)
{
	Seconde::tick();
}

// ----------------------------------------------------------------------------
