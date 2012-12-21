//*****************************************************************************
//
//! @page xsysctl_testcase xcore register test
//!
//! File: @ref xsysctltest.c
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
//! \file xsysctltest.c
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

static unsigned long ulSleepSYSCTL_PERIPH[] = { 
SYSCTL_PERIPH_WDOG0, SYSCTL_PERIPH_CAN0, SYSCTL_PERIPH_PWM, SYSCTL_PERIPH_ADC0,
SYSCTL_PERIPH_TIMER0, SYSCTL_PERIPH_TIMER1, SYSCTL_PERIPH_TIMER2, SYSCTL_PERIPH_TIMER3,
SYSCTL_PERIPH_COMP0, SYSCTL_PERIPH_I2C0, SYSCTL_PERIPH_QEI0, SYSCTL_PERIPH_QEI1,    
SYSCTL_PERIPH_SSI0, SYSCTL_PERIPH_UART0, SYSCTL_PERIPH_UART1, SYSCTL_PERIPH_ETH,
SYSCTL_PERIPH_IEEE1588};

static unsigned long ulDeepSleepSYSCTL_PERIPH[] = { 
SYSCTL_PERIPH_WDOG0, SYSCTL_PERIPH_CAN0, SYSCTL_PERIPH_PWM, SYSCTL_PERIPH_ADC0,
SYSCTL_PERIPH_TIMER0, SYSCTL_PERIPH_TIMER1, SYSCTL_PERIPH_TIMER2, SYSCTL_PERIPH_TIMER3,
SYSCTL_PERIPH_COMP0, SYSCTL_PERIPH_I2C0, SYSCTL_PERIPH_QEI0, SYSCTL_PERIPH_QEI1,    
SYSCTL_PERIPH_SSI0, SYSCTL_PERIPH_UART0, SYSCTL_PERIPH_UART1, SYSCTL_PERIPH_ETH,
SYSCTL_PERIPH_IEEE1588};
//*****************************************************************************
//
//! \brief Get the Test description of xsysctl004 register test.
//!
//! \return the desccription of the xcore001 test.
//
//*****************************************************************************
static char* xSysctl004GetTest(void)
{
    return "xsysctl, 004, xsysctl Peripheral clock source set test";
}

//*****************************************************************************
//
//! \brief something should do before the test execute of xsysctl004 test.
//!
//! \return None.
//
//*****************************************************************************
static void xSysctl004Setup(void)
{
    unsigned long ulTemp;
    ulTemp = SYSCTL_SYSDIV_1 | SYSCTL_XTAL_8MHZ | SYSCTL_OSC_MAIN | SYSCTL_USE_OSC;
    SysCtlClockSet(ulTemp);
}

//*****************************************************************************
//
//! \brief something should do after the test execute of xsysctl004 test.
//!
//! \return None.
//
//*****************************************************************************
static void xSysctl004TearDown(void)
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
//! \brief xsysctl 004 test of Peripheral Sleep Mode test .
//!
//! \return None.
//
//*****************************************************************************
void xsysctl_SysCtlPeripheralSleepMode_test()
{
    unsigned long ulRegVal, ulTemp, i;
        
    // enter the sleep mode
    xHWREG(SYSCTL_RCC) &= ~SYSCTL_RCC_ACG;
        
    //
    //     Enable sleep mode
    //
    for(i = 0;i < 4;i++)
    {
        ulTemp = ulSleepSYSCTL_PERIPH[i];
        SysCtlPeripheralSleepEnable(ulTemp);
        ulRegVal = xHWREG(SYSCTL_SCGC0);
        if(ulTemp & 0x00100000)
        {
            ulTemp = ulTemp << 16;
        }
        else
        {
            ulTemp = ulTemp & 0x0FFFFFFF;
        }
        TestAssert((ulTemp == (ulRegVal & ulTemp)), "xsysctl API error!"); 
    }
    for(i = 4;i < 15;i++)
    {
        ulTemp = ulSleepSYSCTL_PERIPH[i];
        SysCtlPeripheralSleepEnable(ulTemp);
        ulRegVal = xHWREG(SYSCTL_SCGC1);
        if(ulTemp & 0x00100000)
        {
            ulTemp = ulTemp << 16;
        }
        else
        {
            ulTemp = ulTemp & 0x0FFFFFFF;
        }
        TestAssert((ulTemp == (ulRegVal & ulTemp)), "xsysctl API error!"); 
    }
    for(i = 15;i < 17;i++)
    {
        ulTemp = ulSleepSYSCTL_PERIPH[i];
        SysCtlPeripheralSleepEnable(ulTemp);
        ulRegVal = xHWREG(SYSCTL_SCGC2);
        if(ulTemp & 0x00100000)
        {
            ulTemp = ulTemp << 16;
        }
        else
        {
            ulTemp = ulTemp & 0x0FFFFFFF;
        }
        TestAssert((ulTemp == (ulRegVal & ulTemp)), "xsysctl API error!"); 
    }
        
    //
    // Disable sleep mode
    //
    for(i = 0;i < 4;i++)
    {
        ulTemp = xHWREG(SYSCTL_SCGC0);
        SysCtlPeripheralSleepDisable(ulSleepSYSCTL_PERIPH[i]);
        if(ulSleepSYSCTL_PERIPH[i] & 0x00100000)
        {
            ulTemp &= ~(ulSleepSYSCTL_PERIPH[i] << 16);
        }
        else
        {
            ulTemp &= ~(ulSleepSYSCTL_PERIPH[i] & 0x0FFFFFFF);
        }
        ulRegVal = xHWREG(SYSCTL_SCGC0); 
        TestAssert(ulRegVal == ulTemp,"xsysctl scgc0 API error!");
    }
    for(i = 4;i < 15;i++)
    {
        ulTemp = xHWREG(SYSCTL_SCGC1);
        SysCtlPeripheralSleepDisable(ulSleepSYSCTL_PERIPH[i]);
        if(ulSleepSYSCTL_PERIPH[i] & 0x00100000)
        {
            ulTemp &= ~(ulSleepSYSCTL_PERIPH[i] << 16);
        }
        else
        {
            ulTemp &= ~(ulSleepSYSCTL_PERIPH[i] & 0x0FFFFFFF);
        }
        ulRegVal = xHWREG(SYSCTL_SCGC1); 
        TestAssert(ulRegVal == ulTemp,"xsysctl scgc1 API error!");
    }
    for(i = 15;i < 17;i++)
    {
        ulTemp = xHWREG(SYSCTL_SCGC2);
        SysCtlPeripheralSleepDisable(ulSleepSYSCTL_PERIPH[i]);
        if(ulSleepSYSCTL_PERIPH[i] & 0x00100000)
        {
            ulTemp &= ~(ulSleepSYSCTL_PERIPH[i] << 16);
        }
        else
        {
            ulTemp &= ~(ulSleepSYSCTL_PERIPH[i] & 0x0FFFFFFF);
        }
        ulRegVal = xHWREG(SYSCTL_SCGC2); 
        TestAssert(ulRegVal == ulTemp,"xsysctl scgc2 API error!"); 
    }
}

//*****************************************************************************
//
//! \brief xsysctl 004 test of Peripheral Deep Sleep Mode test .
//!
//! \return None.
//
//*****************************************************************************
void xsysctl_SysCtlPeripheralDeepSleepClock_test()
{
        // enter the sleep mode
//        xHWREG(SYSCTL_RCC) &= ~SYSCTL_RCC_ACG;
    
//        xHWREG(SYSCTL_DSLPCLKCFG) |= 
}
//*****************************************************************************
//
//! \brief xsysctl 004 test of Peripheral Deep Sleep Mode test .
//!
//! \return None.
//
//*****************************************************************************
void xsysctl_SysCtlPeripheralDeepSleepMode_test()
{
    unsigned long ulRegVal, ulTemp, i;
        
    // enter the sleep mode
    xHWREG(SYSCTL_RCC) &= ~SYSCTL_RCC_ACG;
        
    //
    //     Enable deep sleep mode
    //
    for(i = 0;i < 4;i++)
    {
        ulTemp = ulSleepSYSCTL_PERIPH[i];
        SysCtlPeripheralDeepSleepEnable(ulTemp);
        ulRegVal = xHWREG(SYSCTL_DCGC0);
        if(ulTemp & 0x00100000)
        {
            ulTemp = ulTemp << 16;
        }
        else
        {
            ulTemp = ulTemp & 0x0FFFFFFF;
        }
        TestAssert((ulTemp == (ulRegVal & ulTemp)), "xsysctl API error!"); 
    }
    for(i = 4;i < 15;i++)
    {
        ulTemp = ulSleepSYSCTL_PERIPH[i];
        SysCtlPeripheralDeepSleepEnable(ulTemp);
        ulRegVal = xHWREG(SYSCTL_DCGC1);
        if(ulTemp & 0x00100000)
        {
            ulTemp = ulTemp << 16;
        }
        else
        {
            ulTemp = ulTemp & 0x0FFFFFFF;
        }
        TestAssert((ulTemp == (ulRegVal & ulTemp)), "xsysctl API error!"); 
    }
    for(i = 15;i < 17;i++)
    {
        ulTemp = ulSleepSYSCTL_PERIPH[i];
        SysCtlPeripheralDeepSleepEnable(ulTemp);
        ulRegVal = xHWREG(SYSCTL_DCGC2);
        if(ulTemp & 0x00100000)
        {
            ulTemp = ulTemp << 16;
        }
        else
        {
            ulTemp = ulTemp & 0x0FFFFFFF;
        }
        TestAssert((ulTemp == (ulRegVal & ulTemp)), "xsysctl API error!"); 
    }
        
    //
    // Disable deep sleep mode
    //
    for(i = 0;i < 4;i++)
    {
        ulTemp = xHWREG(SYSCTL_DCGC0);
        SysCtlPeripheralDeepSleepDisable(ulDeepSleepSYSCTL_PERIPH[i]);
        if(ulDeepSleepSYSCTL_PERIPH[i] & 0x00100000)
        {
            ulTemp &= ~(ulDeepSleepSYSCTL_PERIPH[i] << 16);
        }
        else
        {
             ulTemp &= ~(ulDeepSleepSYSCTL_PERIPH[i] & 0x0FFFFFFF);
        }
        ulRegVal = xHWREG(SYSCTL_DCGC0);
        TestAssert(ulRegVal == ulTemp, "xsysctl API error!"); 
    }
    for(i = 4;i < 15;i++)
    {
        ulTemp = xHWREG(SYSCTL_DCGC1);
        SysCtlPeripheralDeepSleepDisable(ulDeepSleepSYSCTL_PERIPH[i]);
        if(ulDeepSleepSYSCTL_PERIPH[i] & 0x00100000)
        {
            ulTemp &= ~(ulDeepSleepSYSCTL_PERIPH[i] << 16);
        }
        else
        {
            ulTemp &= ~(ulDeepSleepSYSCTL_PERIPH[i] & 0x0FFFFFFF);
        }
        ulRegVal = xHWREG(SYSCTL_DCGC1);
        TestAssert(ulRegVal == ulTemp, "xsysctl API error!"); 
    }
    for(i = 15;i < 17;i++)
    {
        ulTemp = xHWREG(SYSCTL_DCGC2);
        SysCtlPeripheralDeepSleepDisable(ulDeepSleepSYSCTL_PERIPH[i]);
        if(ulDeepSleepSYSCTL_PERIPH[i] & 0x00100000)
        {
            ulTemp &= ~(ulDeepSleepSYSCTL_PERIPH[i] << 16);
        }
        else
        {
            ulTemp &= ~(ulDeepSleepSYSCTL_PERIPH[i] & 0x0FFFFFFF);
        }
        ulRegVal = xHWREG(SYSCTL_DCGC2);
        TestAssert(ulRegVal == ulTemp, "xsysctl API error!"); 
    }
}
//*****************************************************************************
//
//! \brief xsysctl 004 test execute main body.
//!
//! \return None.
//
//*****************************************************************************
static void xSysctl004Execute(void)
{
    xsysctl_SysCtlPeripheralSleepMode_test();
    xsysctl_SysCtlPeripheralDeepSleepClock_test();
    xsysctl_SysCtlPeripheralDeepSleepMode_test();
}

//
// xsysctl register test case struct.
//
const tTestCase sTestXSysctl004Register = {
    xSysctl004GetTest,
    xSysctl004Setup,
    xSysctl004TearDown,
    xSysctl004Execute
};

//
// Xsysctl test suits.
//
const tTestCase * const psPatternXsysctl03[] =
{
    &sTestXSysctl004Register,
    0
};
