#include "test.h"

//*****************************************************************************
//
//! \brief Init uart to print.
//!
//! \param None
//!
//! \details uart config as (115200, 8 data bit, 1 stop bit , no partiy)
//!
//! \return None.
//
//*****************************************************************************

void 
TestIOInit(void)
{
		SysCtlClockSet(	SYSCTL_SYSDIV_1 	| 	/* 时钟1分频 			*/
										SYSCTL_USE_OSC	 	|		/* 使用用户时钟 	*/
										SYSCTL_XTAL_16MHZ	|  	/* 使用外部8M晶振 */
										SYSCTL_OSC_MAIN);			/* 使用主时钟 		*/
	
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
//! \brief print a char.
//!
//! \param None
//!
//! \return None.
//
//*****************************************************************************
void 
TestIOPut(char ucData)
{
    while(xHWREG(UART0_BASE + UART_FR) & UART_FR_TXFF);
    //
    // Write this character to the transmit FIFO.
    //
		xHWREG(UART0_BASE + UART_DR) = ucData;
}

//*****************************************************************************
//
//! \brief Enable IRQ.
//!
//! \param None
//!
//! \return None.
//
//*****************************************************************************
void TestEnableIRQ(void)
{
    xCPUcpsie();
}

//*****************************************************************************
//
//! \brief Disable IRQ.
//!
//! \param None
//!
//! \return None.
//
//*****************************************************************************
void TestDisableIRQ(void)
{
    xCPUcpsid();
}

//*****************************************************************************
//
// The error routine that is called if the driver library encounters an error.(COX)
//
//*****************************************************************************
//#ifdef xDEBUG
//void
//__xerror__(char *pcFilename, unsigned long ulLine)
//{
//    while(1);
//}
//#endif

