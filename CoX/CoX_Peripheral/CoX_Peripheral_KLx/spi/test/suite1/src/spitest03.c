//*****************************************************************************
//
//! @page xspi_testcase xcore register test
//!
//! File: @ref spitest03.c
//!
//! <h2>Description</h2>
//! This module implements the test sequence for the xsysctl sub component.<br><br>
//! - \p Board: KL25Z128 <br><br>
//! - \p Last-Time(about): 0.5s <br><br>
//! - \p Phenomenon: Success or failure information will be printed on the UART. 
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
//! \file spitest03.c
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
// SPI Group Array
//
static unsigned long ulSPI[2] = {xSPI0_BASE, xSPI1_BASE};

static unsigned long ulSourceData[] = {135, 140, 145, 150,
                                       155, 160, 165, 170};
static unsigned long ulDestData[16];

static unsigned long ulIntFlags[] = {SPI_SPRF, SPI_MODF, SPI_SPTEF, SPI_SPMF, SPI_SPLPF};

static unsigned long Rx_Idx=0, Tx_Idx = 0, ulFlag = 0;
//*****************************************************************************
//
//! !brief callback function of SPI0 interrupt handler.
//!
//! \return None.
//
//*****************************************************************************
unsigned long SPI0Callback(void *pvCBData, unsigned long ulEvent,
                                                    unsigned long ulMsgParam, void *pvMsgData)
{                                      
    ulDestData[Rx_Idx++] = xSPISingleDataReadWrite(xSPI0_BASE, ulSourceData[Tx_Idx++]); 
    if(Tx_Idx == 8)
    {
        ulFlag = 1;
        xSPIIntDisable(xSPI0_BASE, xSPI_INT_RX_FIFO|xSPI_INT_TX_FIFO);
    }
    return 0;
}

//*****************************************************************************
//
//! \brief Get the Test description of xSPI004 register test.
//!
//! \return the desccription of the xSPI001 test.
//
//*****************************************************************************
static char* xSPI004GetTest(void)
{
    return "xspi, 004, xspi loopback and interrupt test";
}

//*****************************************************************************
//
//! \brief something should do before the test execute of xSPI001 test.
//!
//! \return None.
//
//*****************************************************************************
static void xSPI004Setup(void)
{   
    SysCtlPeripheralEnable(SYSCTL_PERIPH_SPI0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_SPI1);
}

//*****************************************************************************
//
//! \brief something should do after the test execute of xSPI001 test.
//!
//! \return None.
//
//*****************************************************************************
static void xSPI004TearDown(void)
{      
    SysCtlPeripheralDisable(SYSCTL_PERIPH_SPI0);
    SysCtlPeripheralDisable(SYSCTL_PERIPH_SPI1);
}

//*****************************************************************************
//
//! \brief xspi 004 test of SPI interrupt register.
//!
//! \return None.
//
//*****************************************************************************
static void xspi004_IntRegister_test(void)
{
    unsigned long i, j, ulRegVal;
    
    for(i = 0; i < 2; i++)
    {
        for(j = 0;j < 3; j++)
        {
            SPIIntEnable(ulSPI[i],ulIntFlags[j]);
            ulRegVal = xHWREG(ulSPI[i] + SPI_C1) & (ulIntFlags[j] << 4);
            TestAssert(ulRegVal == (ulIntFlags[j] << 4), "xspi API error!");
        }                  
        for(j = 3;j < 5; j++)
        {
            SPIIntEnable(ulSPI[i], ulIntFlags[j]);
            ulRegVal = xHWREG(ulSPI[i] + SPI_C2) & (ulIntFlags[j] << 4);
            TestAssert(ulRegVal == (ulIntFlags[j] << 4), "xspi API error!");
        }    
                
        for(j = 0;j < 3; j++)
        {
            SPIIntDisable(ulSPI[i],ulIntFlags[j]);
            ulRegVal = xHWREG(ulSPI[i] + SPI_C1) & (ulIntFlags[j] << 4);
            TestAssert(ulRegVal == 0, "xspi API error!");
        }
	for(j = 3;j < 5; j++)
        {
            SPIIntDisable(ulSPI[i],ulIntFlags[j]);
            ulRegVal = xHWREG(ulSPI[i] + SPI_C2) & (ulIntFlags[j] << 4);
            TestAssert(ulRegVal == 0, "xspi API error!");
        }
    }
}

static void xspi004_MasterIntFunction(void)
{
    unsigned long i;
    
    //
    // Configure Some GPIO pins as SPI Mode
    //    
    xSPinTypeSPI(SPI0CLK, PC5);
    xSPinTypeSPI(SPI0CS, PC4);
    xSPinTypeSPI(SPI0MISO, PC7);
    xSPinTypeSPI(SPI0MOSI, PC6);    
    
    //
    // Master Mode polarity 0,Rx latched at rising edge Tx changed at rising edge
    // 2000000Hz 8Bits Data windth SPI MSB First
    //  
    xSPIConfigSet(xSPI0_BASE, 20000, xSPI_MOTO_FORMAT_MODE_0     | 
                                     xSPI_MODE_MASTER            |
                                     xSPI_MSB_FIRST);
    
    xSPIEnable(xSPI0_BASE);
    
    xIntEnable(INT_SPI0);   
    xIntPrioritySet(INT_SPI0, 1); 
    xSPIIntCallbackInit(xSPI0_BASE, SPI0Callback);
    xSPIIntEnable(xSPI0_BASE, SPI_SPTEF);      
   
    while(!ulFlag);
        
    for(i = 0; i < 8; i++)
    {
        TestAssert((ulSourceData[i] == ulDestData[i]), "xspi API error!");
    }
}
//*****************************************************************************
//
//! \brief xspi 004 test of SPI0 interrupt function.
//!
//! \return None.
//
//*****************************************************************************
static void xspi004_MasterInt_test(void)
{
    xspi004_MasterIntFunction();    
}

//*****************************************************************************
//
//! \brief xspi 004 test of SPI Loopback between SPI0MISO and SPI0MOSI.
//!
//! \return None.
//
//*****************************************************************************
static void xspi004_SpiLoopback_test(void)
{
    
}

//*****************************************************************************
//
//! \brief xspi 004 test execute main body.
//!
//! \return None.
//
//*****************************************************************************
static void xSPI004Execute(void)
{
    xspi004_IntRegister_test();
    xspi004_SpiLoopback_test();
    xspi004_MasterInt_test();  
}


//
// xspi register test case struct.
//
const tTestCase sTestXSPI004Register = {
    xSPI004GetTest,
    xSPI004Setup,
    xSPI004TearDown,
    xSPI004Execute
};

//
// Xspi test suits.
//
const tTestCase * const psPatternXspi03[] =
{
    &sTestXSPI004Register,
    0
};
