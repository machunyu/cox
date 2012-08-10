//*****************************************************************************
//
//! @page xsysctl_testcase xcore register test
//!
//! File: @ref xsysctltest.c
//!
//! <h2>Description</h2>
//! This module implements the test sequence for the xsysctl sub component.<br><br>
//! - \p Board: LM3S8962 <br><br>
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

//
// The value of clock which will be set in the test of "xSysCtlClockSet()"
//
unsigned long ulSYSCTL_CLKSET1[] = {12, 13, 14, 15, 16, 18, 20, 22, 25, 28, 33, 40, 50};
unsigned long ulSYSCTL_CLKSET2[] = {1250, 1333, 1429, 1538, 1667, 1818, 20, 2222, 25, 2857, 3333, 40, 50};

#define xSYSCTL_INT_12MHZ       0x00000000  // Internal main clock is 16MHz

//*****************************************************************************
//
//! \brief Get the Test description of xsysctl001 register test.
//!
//! \return the desccription of the xcore001 test.
//
//*****************************************************************************
static char* xSysctl001GetTest(void)
{
    return "xsysctl, 001, xsysctl Clock set and get test";
}


//*****************************************************************************
//
//! \brief something should do before the test execute of xsysctl001 test.
//!
//! \return None.
//
//*****************************************************************************
static void xSysctl001Setup(void)
{   
    //
    // Enable external 8 MHz high speed crystal
    //
    xHWREG(SYSCTL_RCC) &= ~SYSCTL_RCC_MOSCDIS;
    
    //
    // Enable internal  high speed oscillator
    //
    xHWREG(SYSCTL_RCC) &= ~SYSCTL_RCC_IOSCDIS;
    
    //
    // PLL FOUT enable
    //
    xHWREG(SYSCTL_RCC) &= ~SYSCTL_RCC_PWRDN;
    
    //
    // PLL: input 8MHz , output 50MHz
    //
    xHWREG(SYSCTL_RCC) &= ~SYSCTL_RCC_SYSDIV_M;
    xHWREG(SYSCTL_RCC) &= ~SYSCTL_RCC_XTAL_M;
    xHWREG(SYSCTL_RCC) |= SYSCTL_RCC_XTAL_8MHZ;
    xHWREG(SYSCTL_RCC) |= SYSCTL_RCC_SYSDIV_4;
}


//*****************************************************************************
//
//! \brief something should do after the test execute of xsysctl001 test.
//!
//! \return None.
//
//*****************************************************************************
static void xSysctl001TearDown(void)
{   

}
void delay(void)
{
        unsigned int t = 8000;
        while(t--);
}
//*****************************************************************************
//
//! \brief xsysctl 001 test of set and get HCLK test .
//!
//! \return None.
//
//*****************************************************************************
static void xsysctl_SetHCLK_test(void)
{
    unsigned long ulTemp,i;
#if 0
    for(i = 1; i <= 16; i++)
    {
        xHWREG(SYSCTL_RCC) |= (SYSCTL_RCC_BYPASS | SYSCTL_RCC_USESYSDIV);
        SysCtlClockSet((i<<23) | SYSCTL_XTAL_8MHZ | SYSCTL_USE_OSC | SYSCTL_OSC_MAIN );                           
        ulTemp = SysCtlClockGet();
        //TestAssert(ulTemp == 8000000/(i+1), "xsysctl API error!");
    }
#endif        
    for(i=3;i<16;i++)
    {
        xHWREG(SYSCTL_RCC) &= ~SYSCTL_RCC_BYPASS;
        SysCtlClockSet((i << 23) | SYSCTL_XTAL_8MHZ | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN);
        delay();                                       
        ulTemp = SysCtlClockGet()/1000000;
        TestAssert(ulTemp == ulSYSCTL_CLKSET1[15 - i], "xsysctl API error!");
    }
#if 0
    //
    // Clock Set Test Source from Extern_8MHz
    //
    for(i=0;i<13;i++)
    {   
        unsigned long ulTempClk;
        ulTempClk = 10000*ulSYSCTL_CLKSET2[i];
        xSysCtlClockSet(ulTempClk, xSYSCTL_OSC_MAIN | SYSCTL_USE_PLL | xSYSCTL_XTAL_8MHZ);
        ulTemp = xSysCtlClockGet()/10000;
        TestAssert(ulTemp == ulSYSCTL_CLKSET2[i],"xsysctl API error!");
    }
#endif
#if 1
    //
    // Clock Set Test Source from Inter_30KHz
    //
    xSysCtlClockSet(30000, xSYSCTL_OSC_INTSL | xSYSCTL_INTSL_30KHZ | SYSCTL_MAIN_OSC_DIS);
    ulTemp = xSysCtlClockGet();
    TestAssert(ulTemp == 30000, "xsysctl API error!");
        
        //
    // Clock Set Test Source from Inter_12MHz
    //
    xSysCtlClockSet(12000000, xSYSCTL_OSC_INT | xSYSCTL_INT_12MHZ | SYSCTL_MAIN_OSC_DIS);
    ulTemp = xSysCtlClockGet();
    TestAssert(ulTemp == 12000000, "xsysctl API error!");
#endif
}

//*****************************************************************************
//
//! \brief xsysctl 001 test execute main body.
//!
//! \return None.
//
//*****************************************************************************
static void xSysctl001Execute(void)
{
    xsysctl_SetHCLK_test();
}

//
// xsysctl register test case struct.
//
const tTestCase sTestXSysctl001Register = {
    xSysctl001GetTest,
    xSysctl001Setup,
    xSysctl001TearDown,
    xSysctl001Execute
};

//
// xsysctl test suits.
//
const tTestCase * const psPatternXsysctl00[] =
{
    &sTestXSysctl001Register,
    0
};
