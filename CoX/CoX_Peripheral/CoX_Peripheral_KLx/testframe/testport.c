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
    xSysCtlClockSet(48000000, xSYSCTL_OSC_MAIN | xSYSCTL_XTAL_8MHZ);
    SysCtlDelay(10000);

//    xSPinTypeUART(UART0RX,PB0);
//    xSPinTypeUART(UART0TX,PB1);

//    xSysCtlPeripheralEnable(xSYSCTL_PERIPH_UART0);
//    SysCtlPeripheralClockSourceSet(SYSCTL_PERIPH_UART_S_EXT12M);

//    UARTConfigSetExpClk(UART0_BASE, 115200, (UART_CONFIG_WLEN_8 | 
//                                             UART_CONFIG_STOP_ONE | 
//                                               UART_CONFIG_PAR_NONE));

//    UARTEnable(UART0_BASE, (UART_BLOCK_UART | UART_BLOCK_TX | UART_BLOCK_RX));
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
TestIOPut(char ch)
{
    uint8_t c;
    c = ch;
    //while((xHWREG(UART0_BASE + UART_012_S1) & (0x20)) == 0x20);
    //
    // Write this character to the transmit FIFO.
    //
    //xHWREG(UART0_BASE + UART_012_D) = c;
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

