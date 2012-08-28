//*****************************************************************************
//
//! @page xspi_testcase xcore register test
//!
//! File: @ref spitest04.c
//!
//! <h2>Description</h2>
//! This module implements the test sequence for the xsysctl sub component.<br><br>
//! - \p Board: KL25Z128 <br><br>
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
//! \file spitest04.c
//! \brief xspi test source file
//! \brief xspi test header file <br>
//
//*****************************************************************************
#include "xhw_memmap.h"
#include "test.h"
#include "xspi.h"
#include "xhw_spi.h"
#include "xsysctl.h"

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
unsigned long ulSPIAddrTemp[4] = {SPI0_BASE,SPI1_BASE};

unsigned long ulSuspendInterval[14] = {2,3,4,5,6,7,8,9,10,11,12,13,14,15};

//*****************************************************************************
//
//! \brief Get the Test description of xspi003 register test.
//!
//! \return the desccription of the xspi003 test.
//
//*****************************************************************************
static char* xSPI005GetTest(void)
{
    return "xspi, 005, xspi FIFO Set test";
}

//*****************************************************************************
//
//! \brief something should do before the test execute of xspi003 test.
//!
//! \return None.
//
//*****************************************************************************
static void xSPI005Setup(void)
{
    //
    // Enable Peripheral SPI0,SPI1,SPI2 And SPI3
    //
    SysCtlPeripheralEnable(SYSCTL_PERIPH_SPI0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_SPI1);  
}

//*****************************************************************************
//
//! \brief something should do after the test execute of xspi003 test.
//!
//! \return None.
//
//*****************************************************************************
static void xSPI005TearDown(void)
{     
    SysCtlPeripheralDisable(SYSCTL_PERIPH_SPI0);
    SysCtlPeripheralDisable(SYSCTL_PERIPH_SPI1);
}

//*****************************************************************************
//
//! \brief xspi 004 test of SPI 3 Wire Function enable.
//!
//! \return None.
//
//*****************************************************************************
static void xspi_SPIFIFOModeSet_test(void)
{
   
}

//*****************************************************************************
//
//! \brief xspi 003 test execute main body.
//!
//! \return None.
//
//*****************************************************************************
static void xSPI005Execute(void)
{
    xspi_SPIFIFOModeSet_test();
}

//
// xspi register test case struct.
//
const tTestCase sTestXSPI005Register = {
    xSPI005GetTest,
    xSPI005Setup,
    xSPI005TearDown,
    xSPI005Execute
};

//
// Xspi test suits.
//
const tTestCase * const psPatternXspi04[] =
{
    &sTestXSPI005Register,
    0
};
