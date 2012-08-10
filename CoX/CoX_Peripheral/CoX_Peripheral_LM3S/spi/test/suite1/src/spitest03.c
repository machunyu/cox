//*****************************************************************************
//
//! @page xspi_testcase xcore register test
//!
//! File: @ref spitest03.c
//!
//! <h2>Description</h2>
//! This module implements the test sequence for the xsysctl sub component.<br><br>
//! - \p Board: LM3S9B96 <br><br>
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
// SPI Group Array
//
static unsigned long ulSPI[2] = {xSPI0_BASE,xSPI1_BASE};

static unsigned long ulSourceData[] = {135, 140, 145, 150,
                                       155, 160, 165, 170};
static unsigned long ulDestData[16];

static unsigned long ulIntFlags[] = {SSI_TXFF, SSI_RXFF, SSI_RXTO, SSI_RXOR};

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
        xSPIIntDisable(xSPI0_BASE, SSI_TXFF|SSI_RXFF);
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
    SysCtlPeripheralReset(SYSCTL_PERIPH_SSI0);
    SysCtlPeripheralReset(SYSCTL_PERIPH_SSI1);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_SSI0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_SSI1);
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
    SysCtlPeripheralDisable(SYSCTL_PERIPH_SSI0);
    SysCtlPeripheralDisable(SYSCTL_PERIPH_SSI1);
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
        for(j = 0;j < 4; j++)
        {
            SSIIntEnable(ulSPI[i],ulIntFlags[j]);
            ulRegVal = xHWREG(ulSPI[i] + SSI_IM) & ulIntFlags[j];
            TestAssert(ulRegVal == ulIntFlags[j], "xspi API error!");
        }    
                
        for(j = 2;j < 4; j++)
        {
            SSIIntClear(ulSPI[i],ulIntFlags[j]);
            ulRegVal = SSIIntStatus(ulSPI[i], 1) & ulIntFlags[j];
            TestAssert(ulRegVal == 0, "xspi API error!");
        }    
                
        for(j = 0;j < 4; j++)
        {
            SSIIntDisable(ulSPI[i],ulIntFlags[j]);
            ulRegVal = xHWREG(ulSPI[i] + SSI_IM) & ulIntFlags[j];
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
    xSPinTypeSPI(SPI0CLK, PA2);
    xSPinTypeSPI(SPI0CS, PA3);
    xSPinTypeSPI(SPI0RX, PA4);
    xSPinTypeSPI(SPI0TX, PA5);    
    
    //
    // Master Mode polarity 0,Rx latched at rising edge Tx changed at rising edge
    // 2000000Hz 8Bits Data windth SPI MSB First
    //  
    xSPIConfigSet(xSPI0_BASE, 20000, xSPI_MOTO_FORMAT_MODE_0     | 
                                     xSPI_MODE_MASTER            |
                                     xSPI_DATA_WIDTH8);
    
    xHWREG(xSPI0_BASE + SSI_CR1) |= SSI_CR1_LBM;
    xSPIEnable(xSPI0_BASE);
    
    xIntEnable(INT_SSI0);   
    xIntPrioritySet(INT_SSI0, 1); 
    xSPIIntCallbackInit(xSPI0_BASE, SPI0Callback);
    xSPIIntEnable(xSPI0_BASE, SSI_TXFF|SSI_RXFF);      
   
    while(!ulFlag);
        
    for(i = 0; i < 8; i++)
    {
        TestAssert((ulSourceData[i] == ulDestData[i]), "xspi API error!");
    }
        
    xHWREG(xSPI0_BASE + SSI_CR1) &= ~SSI_CR1_LBM;
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
    unsigned long i, j;
        
    for(i = 0; i < 2; i++)
    {
        xSPIConfigSet(ulSPI[i], 2000000, xSPI_MOTO_FORMAT_MODE_0     | 
                                         xSPI_MODE_MASTER            |
                                         xSPI_DATA_WIDTH8);
        //
        // make ssi run as loopback test mode
        //
        xHWREG(ulSPI[i] + SSI_CR1) |= SSI_CR1_LBM;
            
        SSIEnable(ulSPI[i]);
                
        for(j = 0; j < 8; j++)
        {
            ulDestData[j] = 0;
         }
                
        for(j = 0; j < 8; j++)
        {
            ulDestData[j] = SSISingleDataReadWrite(ulSPI[i], ulSourceData[j]);
        }    
                
        for(j = 0; j < 8; j++)
        {
            TestAssert((ulSourceData[j] == ulDestData[j]), "xspi API error!");
        }
                
        xHWREG(ulSPI[i] + SSI_CR1) &= ~SSI_CR1_LBM;
    }
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
