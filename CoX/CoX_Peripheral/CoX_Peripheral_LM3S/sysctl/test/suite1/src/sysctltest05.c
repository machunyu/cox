//*****************************************************************************
//
//! @page xsysctl_testcase xcore register test
//!
//! File: @ref xsysctltest05.c
//!
//! <h2>Description</h2>
//! This module implements the test sequence for the xsysctl sub component.<br><br>
//! - \p Board: M051 <br><br>
//! - \p Last-Time(about): 0.5s <br><br>
//! - \p Phenomenon: Success or failure information will be printed on the UART. <br><br>
//! .
//!
//! <h2>Preconditions</h2>
//! The module requires the following options:<br><br>
//! - \p Option-define:
//! <br>(1)None.<br><br>
//! - \p Option-hardware:
//! <br>(1)Connect an USB cable to the development board.<br><br>
//! - \p Option-OtherModule:
//! <br>Connect an COM cable to the development board.<br>
//! .
//! In case some of the required options are not enabled then some or all tests
//! may be skipped or result FAILED.<br>
//!
//! <h2>Test Cases</h2>
//! The module contain those sub tests:<br><br>
//! - \subpage test_xsysctl_register
//! .
//! \file xsysctltest05.c
//! \brief xsysctl test source file
//! \brief xsysctl test header file <br>
//
//*****************************************************************************

#include "test.h"
#include "xhw_memmap.h"

//*****************************************************************************
//
//!\page test_xsysctl_register test_xsysctl_register
//!
//!<h2>Description</h2>
//!Test xsysctl register. <br>
//!
//
//*****************************************************************************
static unsigned long ulPeriprerAddr[] = {xUART0_BASE, xUART1_BASE};

static unsigned long ulGPIOBaseAddr[] = {xGPIO_PORTA_BASE, xGPIO_PORTB_BASE, 
xGPIO_PORTC_BASE, xGPIO_PORTD_BASE, xGPIO_PORTE_BASE, xGPIO_PORTF_BASE, xGPIO_PORTG_BASE};

//*****************************************************************************
//
//! \brief Get the Test description of xsysctl001 register test.
//!
//! \return the desccription of the xcore001 test.
//
//*****************************************************************************
static char* xSysctl006GetTest(void)
{
    return "xsysctl, 006, xsysctl peripheral enable and disable test";
}

//*****************************************************************************
//
//! \brief something should do before the test execute of xsysctl001 test.
//!
//! \return None.
//
//*****************************************************************************
static void xSysctl006Setup(void)
{
    unsigned long ulTemp;
    ulTemp = SYSCTL_SYSDIV_1|SYSCTL_XTAL_8MHZ|SYSCTL_OSC_MAIN | SYSCTL_USE_OSC;
    SysCtlClockSet(ulTemp);
}

//*****************************************************************************
//
//! \brief something should do after the test execute of xsysctl001 test.
//!
//! \return None.
//
//*****************************************************************************
static void xSysctl006TearDown(void)
{   
    unsigned long ulTemp;
    ulTemp = SYSCTL_SYSDIV_1|SYSCTL_XTAL_8MHZ|SYSCTL_OSC_MAIN | SYSCTL_USE_OSC;
    SysCtlClockSet(ulTemp);
    
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    
    xSPinTypeUART(UART0RX, PA0);
    xSPinTypeUART(UART0TX, PA1);
    
    xSysCtlPeripheralReset(xSYSCTL_PERIPH_UART0);
    xSysCtlPeripheralEnable(xSYSCTL_PERIPH_UART0);                    
    
    UARTConfigSetExpClk(UART0_BASE, 115200, (UART_CONFIG_WLEN_8     | 
                                             UART_CONFIG_STOP_1     | 
                                             UART_CONFIG_PAR_NONE));
    UARTEnable(UART0_BASE, (UART_BLOCK_UART | UART_BLOCK_TX | UART_BLOCK_RX));
}

//*****************************************************************************
//
//! \brief xsysctl 006 test of Peripheral Disable test .
//!
//! \return None.
//
//*****************************************************************************
static void xsysctl_xSysCtlPeripheralDisable2_test(void)
{
    unsigned long ulRegVal, ulTemp, i;
    
    for(i = 0; i < 2; i++)
    {
        xSysCtlPeripheralDisable2(ulPeriprerAddr[i]);                
        ulRegVal = xHWREG(SYSCTL_RCGC1);
        ulTemp = 1 << i;
        TestAssert((ulRegVal & ulTemp) == 0, "xsysctl API error!");        
    }
    for(i = 0; i < 7; i++)
    {
        xSysCtlPeripheralDisable2(ulGPIOBaseAddr[i]);                
        ulRegVal = xHWREG(SYSCTL_RCGC2);
        ulTemp = 1 << i;
        TestAssert((ulRegVal & ulTemp) == 0, "xsysctl API error!");        
    }
}
//*****************************************************************************
//
//! \brief xsysctl 006 test of Peripheral reset test .
//!
//! \return None.
//
//*****************************************************************************
static void xsysctl_xSysCtlPeripheralReset2_test(void)
{
    unsigned long i;
    
    for(i = 0; i < 2; i++)
    {
        xSysCtlPeripheralReset2(ulPeriprerAddr[i]);
        TestAssert( (0 == xHWREG(SYSCTL_SRCR0))&&(0 == xHWREG(SYSCTL_SRCR1))&&(0 == xHWREG(SYSCTL_SRCR2)), 
                                                          "xsysctl API error!");
    }
    for(i = 0; i < 7; i++)
    {
        xSysCtlPeripheralReset2(ulGPIOBaseAddr[i]);
        TestAssert( (0 == xHWREG(SYSCTL_SRCR0))&&(0 == xHWREG(SYSCTL_SRCR1))&&(0 == xHWREG(SYSCTL_SRCR2)), 
                                                          "xsysctl API error!");
    }
}

//*****************************************************************************
//
//! \brief xsysctl 006 test of Peripheral Enable test .
//!
//! \return None.
//
//*****************************************************************************
static void xsysctl_xSysCtlPeripheralEnable2_test(void)
{
    unsigned long ulRegVal, ulTemp, i;

    for(i = 0; i < 2; i++)
    {
        xSysCtlPeripheralEnable2(ulPeriprerAddr[i]);
        ulRegVal = xHWREG(SYSCTL_RCGC1);
        ulTemp = 1 << i;
        TestAssert((ulTemp == (ulRegVal & ulTemp)), "xsysctl API error!");  
    }
    for(i = 0; i < 7; i++)
    {
        xSysCtlPeripheralEnable2(ulGPIOBaseAddr[i]);
        ulRegVal = xHWREG(SYSCTL_RCGC2);
        ulTemp = 1 << i;
        TestAssert((ulTemp == (ulRegVal & ulTemp)), "xsysctl API error!");  
    }
}

//*****************************************************************************
//
//! \brief xsysctl 006 test execute main body.
//!
//! \return None.
//
//*****************************************************************************
static void xSysctl006Execute(void)
{
    xsysctl_xSysCtlPeripheralEnable2_test();
    xsysctl_xSysCtlPeripheralDisable2_test();   
    xsysctl_xSysCtlPeripheralReset2_test();
}

//
// xsysctl register test case struct.
//
const tTestCase sTestXSysctl006Register = {
    xSysctl006GetTest,
    xSysctl006Setup,
    xSysctl006TearDown,
    xSysctl006Execute
};

//
// Xsysctl test suits.
//
const tTestCase * const psPatternXsysctl05[] =
{
    &sTestXSysctl006Register,
    0
};
