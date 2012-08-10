//*****************************************************************************
//
//! \file sysctlpwr.c
//! \brief An Example Of powerdown and wake up.
//! \version 1.0
//! \date 7/14/2012
//! \author CooCox
//! \copy
//!
//! Copyright (c) 2009-2011 CooCox.  All rights reserved.
//
//*****************************************************************************
#include "xhw_types.h"
#include "xhw_memmap.h"
#include "xcore.h"
#include "xhw_sysctl.h"
#include "xsysctl.h"
#include "xhw_ints.h"
#include "xgpio.h"
#include "xhw_nvic.h"
#include "xhw_gpio.h"

//*****************************************************************************
//
//! Enter Sleep Mode function.
//!
//! \This function will force the processor enter sleep mode,after operating 
//! the action,some clocks will be closed except "Internal 10 kHz low speed 
//! oscillator clock".
//!  
//! \return None
//*****************************************************************************
void PWRCtlStandby(void)
{
    xSysCtlClockSet(50000000, xSYSCTL_XTAL_16MHZ | 
                              xSYSCTL_OSC_MAIN   |
                              xSYSCTL_INT_OSC_DIS);
    
    xSysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOJ);
    
    xSysCtlSleep();
}
 
//*****************************************************************************
//
//! Wake up mcu from sleep mode function.
//!
//! \This function use extern gpio interrupt to wake up mcu from sleep mode 
//!  
//! \return None
//*****************************************************************************
void WakeUpFromPowerDown(void)
{     
    xIntEnable(xINT_GPIOJ);
    xIntPrioritySet(xINT_GPIOJ, 1);
    xGPIOSPinTypeGPIOInput(PJ7);
    xGPIOPinIntEnable(xGPIO_PORTJ_BASE, xGPIO_PIN_7, xGPIO_FALLING_EDGE);
}
