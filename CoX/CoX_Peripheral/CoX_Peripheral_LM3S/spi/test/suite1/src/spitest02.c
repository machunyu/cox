//*****************************************************************************
//
//! @page xspi_testcase xcore register test
//!
//! File: @ref spitest02.c
//!
//! <h2>Description</h2>
//! This module implements the test sequence for the xsysctl sub component.<br><br>
//! - \p Board: LM3S9B96 <br><br>
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
//! - \subpage test_xspi_register
//! .
//! \file spitest.c
//! \brief xspi test source file
//! \brief xspi test header file <br>
//
//*****************************************************************************
#include "test.h"
#include "xhw_spi.h"
#include "xspi.h"

//*****************************************************************************
//
//!\page test_xspi_register test_xsysctl_register
//!
//!<h2>Description</h2>
//!Test xspi register. <br>
//!
//
//*****************************************************************************
//
// SPI Base Address Group Array
//
static unsigned long ulSPI[2] = {SSI0_BASE,SSI1_BASE};

//
// SPI DMA Array
//
static unsigned long ulDMAFlags[] = {SSI_DMA_RX, SSI_DMA_TX};
//*****************************************************************************
//
//! \brief Get the Test description of xspi003 register test.
//!
//! \return the desccription of the xspi003 test.
//
//*****************************************************************************
static char* xSpi003GetTest(void)
{
    return "xspi, 003, xspi DMA test";
}

//*****************************************************************************
//
//! \brief something should do before the test execute of xspi003 test.
//!
//! \return None.
//
//*****************************************************************************
static void xSpi003Setup(void)
{
    //
    // Enable Peripheral SPI0 and SPI1.
    //
    SysCtlPeripheralReset(SYSCTL_PERIPH_SSI0);
    SysCtlPeripheralReset(SYSCTL_PERIPH_SSI1);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_SSI0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_SSI1);
}

//*****************************************************************************
//
//! \brief something should do after the test execute of xspi003 test.
//!
//! \return None.
//
//*****************************************************************************
static void xSpi003TearDown(void)
{      
    SysCtlPeripheralDisable(SYSCTL_PERIPH_SSI0);
    SysCtlPeripheralDisable(SYSCTL_PERIPH_SSI1); 
}

//*****************************************************************************
//
//! \brief xspi 003 test execute main body.
//!
//! \return None.
//
//*****************************************************************************
static void xSpi003Execute(void)
{
    unsigned long i, j, ulRegVal;
    for(i = 0;i < 2;i ++)
    {
        for(j = 0;j < 2;j ++)
         {
            SSIDMAEnable(ulSPI[i],ulDMAFlags[j]);
            ulRegVal = xHWREG(ulSPI[i] + SSI_DMACTL) & ulDMAFlags[j];
            TestAssert(ulRegVal == ulDMAFlags[j], "xspi API error!");                                                

            SSIDMADisable(ulSPI[i],ulDMAFlags[j]);
            ulRegVal = xHWREG(ulSPI[i] + SSI_DMACTL) & ulDMAFlags[j];
            TestAssert(ulRegVal == 0, "xspi API error!");    
        }
    }
}

//
// xspi register test case struct.
//
const tTestCase sTestXSpi003Register = {
    xSpi003GetTest,
    xSpi003Setup,
    xSpi003TearDown,
    xSpi003Execute
};

//
// Xspi test suits.
//
const tTestCase * const psPatternXspi02[] =
{
    &sTestXSpi003Register,
    0
};
