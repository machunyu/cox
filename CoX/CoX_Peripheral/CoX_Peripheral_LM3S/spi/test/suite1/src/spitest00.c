//*****************************************************************************
//
//! @page xspi_testcase xcore register test
//!
//! File: @ref spitest00.c
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
#include "xhw_spi.h"
#include "test.h"
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

//
// SPI Operation Mode
//
static unsigned long ulSSIOperationMode[] = {SSI_MODE_MASTER, SSI_MODE_SLAVE};

//
// SPI Transfers And Receives Data WIDTH
//
static unsigned long ulDataWidthTable[] = { 
xSPI_DATA_WIDTH4, xSPI_DATA_WIDTH5, xSPI_DATA_WIDTH6, xSPI_DATA_WIDTH7,
xSPI_DATA_WIDTH8, xSPI_DATA_WIDTH9, xSPI_DATA_WIDTH10, xSPI_DATA_WIDTH11,
xSPI_DATA_WIDTH12, xSPI_DATA_WIDTH13, xSPI_DATA_WIDTH14, xSPI_DATA_WIDTH15,
xSPI_DATA_WIDTH16};


//
// SPI SPI_FORMAT_MODE Array
//
static unsigned long ulSpiFormatMode[] = {
xSPI_MOTO_FORMAT_MODE_0, xSPI_MOTO_FORMAT_MODE_1, xSPI_MOTO_FORMAT_MODE_2,
xSPI_MOTO_FORMAT_MODE_3, xSPI_TI_FORMAT_MODE, xSPI_NMW_FORMAT_MODE};


//*****************************************************************************
//
//! \brief Get the Test description of xspi001 register.
//!
//! \return the desccription of the xspi001 test.
//
//*****************************************************************************
static char* xSpi001GetTest(void)
{
    return "xspi, 001, xspi register test";
}

//*****************************************************************************
//
//! \brief something should do before the test execute of xspi001 test.
//!
//! \return None.
//
//*****************************************************************************
static void xSpi001Setup(void)
{
    // Enable Peripheral SPI0 and SPI1.
		SysCtlPeripheralReset(SYSCTL_PERIPH_SSI0);
    SysCtlPeripheralReset(SYSCTL_PERIPH_SSI1);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_SSI0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_SSI1);  
}

//*****************************************************************************
//
//! \brief something should do after the test execute of xspi001 test.
//!
//! \return None.
//
//*****************************************************************************
static void xSpi001TearDown(void)
{   
    SysCtlPeripheralDisable(SYSCTL_PERIPH_SSI0);
    SysCtlPeripheralDisable(SYSCTL_PERIPH_SSI1);
}

//*****************************************************************************
//
//! \brief xspi 001 test of SPI MASTER/SLAVE Mode Slect.
//!
//! \return None.
//
//*****************************************************************************
static void xspi001_SpiMasterSlaveModeSelect_test(void)
{
	unsigned long i, j,ulRegVal, ulTemp;

	//
	// Test Seting MCU as MASTER/SLAVE Mode
	//
	for(i = 0; i < 2; i++)
	{
		for(j = 0; j < 2; j++)
		{
			//xHWREG(ulSPI[i] + SSI_CR1) &= ~SSI_CR1_SSE;
			ulTemp = (xSPI_MOTO_FORMAT_MODE_0 | (ulSSIOperationMode[j] << 8) | xSPI_DATA_WIDTH8);
			xSPIConfigSet(ulSPI[i], 120000, ulTemp);
			ulRegVal = xHWREG(ulSPI[i] + SSI_CR1);
			TestAssert(((ulRegVal >> 2) & ulSSIOperationMode[j]) == ulSSIOperationMode[j], 
												"xspi API error!");
		}
	}
}

//*****************************************************************************
//
//! \brief xspi 001 test of Data Width.
//!
//! \return None.
//
//*****************************************************************************
static void xspi001_SpiDataWidthSet_test(void)
{
    unsigned long i, j, ulTemp, ulRegVal;
    
		//
		// SPI DataWidth Set Test
		// 
		for(j = 0; j < 2; j++)
		{
				for(i = 0; i < 13; i++)
				{
						ulTemp = (xSPI_MOTO_FORMAT_MODE_0 | xSPI_MODE_SLAVE | ulDataWidthTable[i]);
						xSPIConfigSet(ulSPI[j], 120000, ulTemp);
						ulRegVal = xSPIBitLengthGet(ulSPI[j]) & 0x1f;
						TestAssert((ulDataWidthTable[i] == ulRegVal), "xspi API error!");
				}
		}
}

//*****************************************************************************
//
//! \brief xspi 001 test of format mode of SPI Set.
//!
//! \return None.
//
//*****************************************************************************
static void xspi001_SpiFormatModeSet_test(void)
{
    unsigned long i, j, ulTemp, ulRegVal;
		
		//
		// SPI FormatMode Set Test
		// 
		for(j = 0; j < 2; j++)
		{
				for(i = 0;i < 4; i++)
				{
						ulTemp = (ulSpiFormatMode[i] | xSPI_MODE_SLAVE | xSPI_DATA_WIDTH8);
						xSPIConfigSet(ulSPI[j], 120000, ulTemp);
						ulRegVal = xHWREG(ulSPI[j] + SSI_CR0);
						ulTemp = ulRegVal & 0x30;
						TestAssert(ulTemp == 0,"xspi API error!"); 
						ulRegVal >>= 6;
						ulRegVal &= 0x03;						
						TestAssert(ulRegVal == (ulSpiFormatMode[i] >> 16),"xspi API error!"); 
				}
				for(i = 4; i < 6; i++)
				{
						ulTemp = (ulSpiFormatMode[i] | xSPI_MODE_SLAVE | xSPI_DATA_WIDTH8);
						xSPIConfigSet(ulSPI[j], 120000, ulTemp);
						ulRegVal = xHWREG(ulSPI[j] + SSI_CR0);
						ulRegVal &= 0x30;
						TestAssert(ulRegVal  == (ulSpiFormatMode[i] >> 16),"xspi API error!"); 
				}
		}
}

//*****************************************************************************
//
//! \brief xspi 001 test execute main body.
//!
//! \return None.
//
//*****************************************************************************
static void xSpi001Execute(void)
{
		unsigned long i, ulRegVal;
		
		//
		// SPI Enable Test
		// 
		for(i = 0; i < 2; i++)
    {
				SSIEnable(ulSPI[i]);
				ulRegVal = xHWREG(ulSPI[i] + SSI_CR1) & SSI_CR1_SSE;
				TestAssert(ulRegVal == SSI_CR1_SSE, "xspi API error!");
		}																	
    xspi001_SpiMasterSlaveModeSelect_test();
    xspi001_SpiDataWidthSet_test();
    xspi001_SpiFormatModeSet_test();
		
		//
		// SPI Disable Test
		// 
		for(i = 0; i < 2; i++)
    {
				SSIDisable(ulSPI[i]);
				ulRegVal = xHWREG(ulSPI[i] + SSI_CR1) & SSI_CR1_SSE;
				TestAssert(ulRegVal == 0, "xspi API error!");
		}	
}

//
// xspi register test case struct.
//
const tTestCase sTestXSpi001Register = {
    xSpi001GetTest,
    xSpi001Setup,
    xSpi001TearDown,
    xSpi001Execute
};

//
// Xspi test suits.
//
const tTestCase * const psPatternXspi00[] =
{
    &sTestXSpi001Register,
    0
};
