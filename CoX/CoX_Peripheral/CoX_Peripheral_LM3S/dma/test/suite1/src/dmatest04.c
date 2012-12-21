//*****************************************************************************
//
//! @page xdma_testcase xcore api test
//!
//! File: @ref dmatest04.c
//!
//! <h2>Description</h2>
//! This module implements the test sequence for the xdma sub component.<br><br>
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
//! - \subpage test_xdma_api
//! .
//! \file dmatest04.c
//! \brief xdma test source file
//! \brief xdma test header file <br>
//*****************************************************************************

#include "test.h"
#include "xhw_dma.h"
#include "xdma.h"
#include "xhw_spi.h"
#include "xspi.h"

unsigned long ulSrcMem[28] = {0x11121314, 0x15161718, 0x191A1B1C, 0x1D1E1F20,
                              0x21222324, 0x25262728, 0x292A2B2C, 0x2D2E2F30,
                              0x31323334, 0x35363738, 0x393A3B3C, 0x3D3E3F40,
                              0x41424344, 0x45464748, 0x494A4B4C, 0x4D4E4F50,
                              0x51525354, 0x55565758, 0x595A5B5C, 0x5D5E5F60,
                              0x61626364, 0x65666768, 0x696A6B6C, 0x6D6E6F70,
                              0x71727374, 0x75767778, 0x797A7B7C, 0x7D7E7F80};

unsigned long ulDestSPI[28];
unsigned long ulAssignChannelNum;
extern unsigned char ucDMAControlTable[1024];

//*****************************************************************************
//
//! \brief Get the Test description of xdma003 register test.
//!
//! \return the desccription of the xdma003 test.
//
//*****************************************************************************
static char* xDma005GetTest(void)
{
    return "xdma, 005, xdma memory to SPI";
}

//*****************************************************************************
//
//! \brief something should do before the test execute of xdma005 test.
//!
//! \return None.
//
//*****************************************************************************
static void xDma005Setup(void)
{
    //
    // Enable Peripheral uDMA
    //
    SysCtlPeripheralReset(SYSCTL_PERIPH_UDMA);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UDMA);
}

//*****************************************************************************
//
//! \brief something should do after the test execute of xdma003 test.
//!
//! \return None.
//
//*****************************************************************************
static void xDma005TearDown(void)
{   
    //
    // Disable Peripheral uDMA
    //    
    SysCtlPeripheralDisable(SYSCTL_PERIPH_UDMA);  
}

//*****************************************************************************
//
//! \brief Ininite the uDMA case which is needed
//!
//! \param None
//!
//! \details This function is to ininite the uDMA including clock source and 
//!  enable uDMA 
//!
//! \return none
//
//*****************************************************************************
void xdma005_uDMAChannelInit(void)
{
    unsigned long ulTemp;

    uDMAEnable();
    uDMAControlBaseSet(ucDMAControlTable);

    ulAssignChannelNum = xDMAChannelDynamicAssign(xDMA_REQUEST_MEM, 
									  xDMA_REQUEST_SPI0_TX);

    ulTemp = (UDMA_ATTR_USEBURST | UDMA_ATTR_ALTSELECT | UDMA_ATTR_REQMASK);
    uDMAChannelAttributeDisable(ulAssignChannelNum, ulTemp);
    uDMAChannelAttributeEnable(ulAssignChannelNum, UDMA_ATTR_HIGH_PRIORITY);
    //
    // Set Channel control  parameter
    //
    ulTemp = (UDMA_SIZE_32 | UDMA_SRC_INC_32 | xDMA_DST_INC_NONE |  UDMA_ARB_1);
    uDMAChannelControlSet(ulAssignChannelNum | UDMA_PRI_SELECT, ulTemp);

    //
    // 目的地址为SSI0的数据寄存器
    //
    ulTemp = xSPI0_BASE + SSI_DR;// SPI_TX0;
    uDMAChannelTransferSet(ulAssignChannelNum | UDMA_PRI_SELECT, UDMA_MODE_BASIC, ulSrcMem, (void *)ulTemp, 8);
		
    uDMAChannelEnable(ulAssignChannelNum);
}

//*****************************************************************************
//
//! \brief xdma 005 test of SPI0 initialization.
//!
//! \return None.
//
//*****************************************************************************
static void xdma005_uDMASPIInit(void)
{
    unsigned long ulTemp;

    SysCtlPeripheralReset(SYSCTL_PERIPH_SSI0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_SSI0);
    //
    // Configure Some GPIO pins as SPI Mode
    //
    xSPinTypeSPI(SPI0CLK, PA2);
    xSPinTypeSPI(SPI0CS, PA3);
    xSPinTypeSPI(SPI0RX, PA4);
    xSPinTypeSPI(SPI0TX, PA5);
       
    //
    // Master Mode polarity 0,Rx latched at rising edge Tx changed at rising edge
    // 200000Hz 8Bits Data windth  SPI MSB First
    //
    ulTemp = (xSPI_MOTO_FORMAT_MODE_0 | xSPI_MODE_MASTER | xSPI_DATA_WIDTH8);
    xSPIConfigSet(xSPI0_BASE, 2000000, ulTemp);
	  
    //
    // make ssi run as loopback test mode
    //
    xHWREG(xSPI0_BASE + SSI_CR1) |= SSI_CR1_LBM;
				
    SSIEnable(xSPI0_BASE);
    
    SSIDMAEnable(xSPI0_BASE, SSI_DMA_TX | SSI_DMA_RX);
}
//*****************************************************************************
//
//! \brief uDMA Configure and Trig transfer
//!
//! \param None
//!
//! \details This function is to configure uDMA and Trig transfer.
//!
//! \return None
//
//*****************************************************************************
static void xdma005_uDMATransferMtoPTest(void)
{
    unsigned long i;
    
    xdma005_uDMAChannelInit();
    xdma005_uDMASPIInit();   
    
    //
    // Trig uDMA Transfer
    //
    for(i = 0; i < 8; i++)
    {
        uDMAChannelRequest(ulAssignChannelNum);
        while(SSIBusy(xSPI0_BASE));
        SSIDataGet(xSPI0_BASE, &ulDestSPI[i]);
    }

    for(i = 0;i < 8;i++)
    {
        TestAssert((0x00 != ulDestSPI[i]), "dma API error!");
    }
}

//*****************************************************************************
//
//! \brief xdma 005 test execute main body.
//!
//! \return None.
//
//*****************************************************************************
static void xDma005Execute(void)
{
    xdma005_uDMATransferMtoPTest();
}

//
// xdma register test case struct.
//
const tTestCase sTestXDma005 = {
    xDma005GetTest,
    xDma005Setup,
    xDma005TearDown,
    xDma005Execute
};

//
// Xdma test suits.
//
const tTestCase * const psPatternXdma04[] =
{
    &sTestXDma005,
    0
};
