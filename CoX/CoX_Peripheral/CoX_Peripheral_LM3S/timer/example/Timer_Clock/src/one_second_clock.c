//*****************************************************************************
//
//! \file one_second_clock.c
//! \brief Use the timer to make a one second clock.
//! \date 7/14/2012
//! \author CooCox
//! 
//! The timer source select external 8M hz crystal oscillator.
//! 
//! \copy
//
//*****************************************************************************
#include "xhw_types.h"
#include "xcore.h"
#include "xhw_gpio.h"
#include "xhw_ints.h"
#include "xhw_memmap.h"
#include "xhw_nvic.h"
#include "xhw_sysctl.h"
#include "xhw_timer.h"
#include "xhw_uart.h"
#include "xgpio.h"
#include "xsysctl.h"
#include "xtimer.h"
#include "xuart.h"

//*****************************************************************************
//
//! \biref function declaration
//!
//! \return  none
//
//*****************************************************************************
void Print(char *pcMsg);
void UART0Configuration(void);

//*****************************************************************************
//
//! \biref The main example function
//!
//! \return  none
//
//*****************************************************************************
void OneSecondClock(void)
{
    //
    //Set the external 8MHZ clock as system clock 
    //
		SysCtlClockSet(	SYSCTL_SYSDIV_1 	| 	/* 时钟1分频 			*/
										SYSCTL_USE_OSC	 	|		/* 使用用户时钟 	*/
										SYSCTL_XTAL_16MHZ	|  	/* 使用外部8M晶振 */
										SYSCTL_OSC_MAIN);			/* 使用主时钟 		*/
    
    UART0Configuration();
    
    // 
    // Enable tiemr0
    // 
    xSysCtlPeripheralEnable(xSYSCTL_PERIPH_TIMER0);  
    
    //
    // Clear the flag first
    //
    TimerIntClear(TIMER0_BASE, TIMER_BOTH, TIMER_INT_TIMEOUT);
    while(xTimerStatusGet(TIMER0_BASE, TIMER_BOTH, TIMER_INT_TIMEOUT));
    
    // 
    // Config as one shot mode ,T = 1s
    //        
    xTimerInitConfig(TIMER0_BASE, TIMER_BOTH, TIMER_MODE_PERIODIC, 1);
    xTimerIntEnable(TIMER0_BASE, TIMER_BOTH, TIMER_INT_TIMEOUT);
    
    //
    // Start the timer
    //
    xTimerStart(TIMER0_BASE, TIMER_BOTH);
        
    //
    // One shot mode test.
    //
    while(1)
    {       
        //
        // wait until the timer data register reach equel to compare register
        //
        while(!xTimerStatusGet(TIMER0_BASE, TIMER_BOTH, TIMER_INT_TIMEOUT));
        Print("one second has gone...");
        Print("\r\n");
        TimerIntClear(TIMER0_BASE, TIMER_BOTH, TIMER_INT_TIMEOUT);
    }  
    

}

//*****************************************************************************
//
//! \biref uart0 configre 
//!
//! \return  none
//
//*****************************************************************************
void UART0Configuration(void)
{  
		SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);//开启GPIOA时钟
	
		xSPinTypeUART(UART0RX, PA0);
		xSPinTypeUART(UART0TX, PA1);
	
		xSysCtlPeripheralReset(xSYSCTL_PERIPH_UART0);
		xSysCtlPeripheralEnable(xSYSCTL_PERIPH_UART0);					//打开串口0时钟
	
		UARTConfigSetExpClk(UART0_BASE, 115200, (UART_CONFIG_WLEN_8 	| 
                                             UART_CONFIG_STOP_1	 	| 
                                             UART_CONFIG_PAR_NONE));
		UARTEnable(UART0_BASE, (UART_BLOCK_UART | UART_BLOCK_TX | UART_BLOCK_RX));
}

//*****************************************************************************
//
//! \breif uart send function
//
//! \return none
//
//*****************************************************************************
void Print(char *pcMsg)
{
    unsigned char ucData;
    while (*pcMsg != '\0')
    {
        //
        // Put a character in the output buffer.
        //
        ucData = *pcMsg++;

        while(xHWREG(UART0_BASE + UART_FR) & UART_FR_TXFF);
				//
				// Write this character to the transmit FIFO.
				//
				xHWREG(UART0_BASE + UART_DR) = ucData;
    }
}
