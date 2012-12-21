//*****************************************************************************
//
//! @page xdma_testcase xcore register test
//!
//! File: @ref dmatest00.c
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
//! - \subpage test_xdma_register
//! .
//! \file dmatest00.c
//! \brief xdma test source file
//! \brief xdma test header file <br>
//
//*****************************************************************************

#include "test.h"
#include "xhw_dma.h"
#include "xhw_spi.h"
#include "xdma.h"
#include "xspi.h"

//*****************************************************************************
//
//!\page test_xdma_register
//!
//!<h2>Description</h2>
//!Test xdma register. <br>
//!
//
//*****************************************************************************
//static unsigned long ulSrcArrayTest[64];

//static unsigned long ulDestArrayTest[64];

//
// uDMA Channel IDs Array
//
static unsigned long ulChannelID[] = {
xDMA_CHANNEL_0, xDMA_CHANNEL_1, xDMA_CHANNEL_2, xDMA_CHANNEL_3, xDMA_CHANNEL_4,
xDMA_CHANNEL_5, xDMA_CHANNEL_6, xDMA_CHANNEL_7, xDMA_CHANNEL_8, xDMA_CHANNEL_9, 
xDMA_CHANNEL_10, xDMA_CHANNEL_11, xDMA_CHANNEL_12, xDMA_CHANNEL_13, xDMA_CHANNEL_14, 
xDMA_CHANNEL_15, xDMA_CHANNEL_16, xDMA_CHANNEL_17, xDMA_CHANNEL_18, xDMA_CHANNEL_19, 
xDMA_CHANNEL_20, xDMA_CHANNEL_21, xDMA_CHANNEL_22, xDMA_CHANNEL_23, xDMA_CHANNEL_24, 
xDMA_CHANNEL_25, xDMA_CHANNEL_26, xDMA_CHANNEL_27, xDMA_CHANNEL_28, xDMA_CHANNEL_29, 
xDMA_CHANNEL_30, xDMA_CHANNEL_31};

static unsigned long ulDestAddr[] = {
xDMA_REQUEST_UART0_TX, xDMA_REQUEST_UART1_TX, 
xDMA_REQUEST_UART2_TX, xDMA_REQUEST_SPI0_TX,  
xDMA_REQUEST_SPI1_TX,  xDMA_REQUEST_IIS0_TX};

static unsigned long ulSrcAddr[] = {
xDMA_REQUEST_UART0_RX, xDMA_REQUEST_UART1_RX,
xDMA_REQUEST_UART2_RX, xDMA_REQUEST_SPI0_RX,
xDMA_REQUEST_SPI1_RX, xDMA_REQUEST_IIS0_RX};
//*****************************************************************************
//
//! \brief Get the Test description of xdma001 register test.
//!
//! \return the desccription of the xdma001 test.
//
//*****************************************************************************
static char* xDma001GetTest(void)
{
    return "xdma, 001, xdma register test";
}

//*****************************************************************************
//
//! \brief something should do before the test execute of xdma001 test.
//!
//! \return None.
//
//*****************************************************************************
static void xDma001Setup(void)
{
    //
    // Enable Peripheral uDMA
    //
    SysCtlPeripheralReset(SYSCTL_PERIPH_UDMA);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UDMA);
}

//*****************************************************************************
//
//! \brief something should do after the test execute of xdma001 test.
//!
//! \return None.
//
//*****************************************************************************
static void xDma001TearDown(void)
{
    //
    // Disable Peripheral uDMA
    //    
    SysCtlPeripheralDisable(SYSCTL_PERIPH_UDMA);  
}

//*****************************************************************************
//
//! \brief xdma 001 test of uDMA enable test .
//!
//! \return None.
//
//*****************************************************************************
static void xdmaEnableTest(void)
{
    unsigned long i,ulRegVal,ulTemp;

    //
    // Test uDMA Enable
    //
    uDMAEnable();
    ulRegVal = xHWREG(UDMA_CFG);
    TestAssert(ulRegVal = UDMA_CFG_MASTEN, "dma API error!"); 
	
    for(i = 0; i < 32; i++)
    {
        uDMAChannelEnable(ulChannelID[i]);
        ulTemp = 1 << ulChannelID[i];
        ulRegVal = xHWREG(UDMA_ENASET) & ulTemp;      
        TestAssert(ulTemp == ulRegVal, "dma API error!"); 
        ulTemp = uDMAChannelIsEnabled(ulChannelID[i]);
        TestAssert(ulTemp == 1, "dma API error!"); 
    }
}

//*****************************************************************************
//
//! \brief xdma 001 test of uDMA disable test .
//!
//! \return None.
//
//*****************************************************************************
static void xdmaDisableTest(void)
{
    unsigned long i, ulRegVal;
    //
    // Test uDMA Disable
    //
    for(i = 0;i < 32;i++)
    {
        uDMAChannelDisable(ulChannelID[i]); 
        ulRegVal = xHWREG(UDMA_ENASET) & (1 << ulChannelID[i]);
        TestAssert(ulRegVal == 0, "dma API error!");
    }
}

//*****************************************************************************
//
//! \brief xdma 001 test of uDMA Channel Dynamic Assign  test .
//!
//! \return None.
//
//*****************************************************************************
static void xdmaChannelDynamicAssignTest(void)
{
    unsigned long ulRegVal, ulTemp, i;

    //
    // Test uDMA Channel Dynamic Assign
    //
    for(i = 0; i < 6; i++)
    {
        ulRegVal = xDMAChannelDynamicAssign(xDMA_REQUEST_MEM, ulDestAddr[i]);
        ulTemp = xDMAChannelAssignmentGet(ulRegVal);
        TestAssert(ulTemp == 1,"dma API error!");
        xDMAChannelDeAssign(ulRegVal);
    }
    
    for(i = 0; i < 6; i++)
    {
        ulRegVal = xDMAChannelDynamicAssign(ulSrcAddr[i], xDMA_REQUEST_MEM);
        ulTemp = xDMAChannelAssignmentGet(ulRegVal);
        TestAssert(ulTemp == 1,"dma API error!");    
        xDMAChannelDeAssign(ulRegVal);
    }
}

//*****************************************************************************
//
//! \brief xdma 001 test execute main body.
//!
//! \return None.
//
//*****************************************************************************
static void xDma001Execute(void)
{
    xdmaEnableTest();
    xdmaChannelDynamicAssignTest();
    xdmaDisableTest();
}

//
// xdma register test case struct.
//
const tTestCase sTestXDma001Register = {
    xDma001GetTest,
    xDma001Setup,
    xDma001TearDown,
    xDma001Execute
};

//
// Xdma test suits.
//
const tTestCase * const psPatternXdma00[] =
{
    &sTestXDma001Register,
    0
};
