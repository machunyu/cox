//*****************************************************************************
//
//! @page xdma_testcase xcore register test
//!
//! File: @ref dmatest02.c
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
//! \file dmatest02.c
//! \brief xdma test source file
//! \brief xdma test header file <br>
//
//*****************************************************************************

#include "test.h"
#include "xhw_dma.h"
#include "xdma.h"
#include "xhw_spi.h"
#include "xspi.h"
#include "absacc.h"

//*****************************************************************************
//
//!\page test_xdma_register
//!
//!<h2>Description</h2>
//!Test xdma register. <br>
//!
//
//*****************************************************************************

//
// uDMA Channel IDs Array
//
static unsigned long ulDMAChannelID[] = {
xDMA_CHANNEL_0, xDMA_CHANNEL_1, xDMA_CHANNEL_2, xDMA_CHANNEL_3, xDMA_CHANNEL_4,
xDMA_CHANNEL_5, xDMA_CHANNEL_6, xDMA_CHANNEL_7, xDMA_CHANNEL_8, xDMA_CHANNEL_9, 
xDMA_CHANNEL_10, xDMA_CHANNEL_11, xDMA_CHANNEL_12, xDMA_CHANNEL_13, xDMA_CHANNEL_14, 
xDMA_CHANNEL_15, xDMA_CHANNEL_16, xDMA_CHANNEL_17, xDMA_CHANNEL_18, xDMA_CHANNEL_19, 
xDMA_CHANNEL_20, xDMA_CHANNEL_21, xDMA_CHANNEL_22, xDMA_CHANNEL_23, xDMA_CHANNEL_24, 
xDMA_CHANNEL_25, xDMA_CHANNEL_26, xDMA_CHANNEL_27, xDMA_CHANNEL_28, xDMA_CHANNEL_29, 
xDMA_CHANNEL_30, xDMA_CHANNEL_31};

static unsigned long ulSrcArray[64];
static unsigned long ulDestArray[64];
extern unsigned char ucDMAControlTable[1024];

//*****************************************************************************
//
//! \brief Get the Test description of xdma003 register test.
//!
//! \return the desccription of the xdma003 test.
//
//*****************************************************************************
static char* xDma003GetTest(void)
{
    return "xdma, 003, UDMA Channel Transfer Set test";
}

//*****************************************************************************
//
//! \brief something should do before the test execute of xdma003 test.
//!
//! \return None.
//
//*****************************************************************************
static void xDma003Setup(void)
{
    //
    // Enable Peripheral uDMA
    //
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UDMA);
}

//*****************************************************************************
//
//! \brief something should do after the test execute of xdma003 test.
//!
//! \return None.
//
//*****************************************************************************
static void xDma003TearDown(void)
{   
    //
    // Disable Peripheral uDMA
    //    
    SysCtlPeripheralDisable(SYSCTL_PERIPH_UDMA);  
}

//*****************************************************************************
//
//! \brief xdma 003 test of Channel Transfer Set test .
//!
//! \return None.
//
//*****************************************************************************
static void xdma003_uDMAChannelTransferSet_Test(void)
{
    unsigned long i,ulRegVal,ulTemp,ulReg;
	  
	  uDMAEnable();
	
    //
    // Test  Channel Transfer Set
    //
    for(i = 0;i < 32;i++)
    {
        //
        // Enable uDMA channel
        //
        uDMAChannelEnable(ulDMAChannelID[i]);
				 
        uDMAControlBaseSet(ucDMAControlTable);
			
        //
        // uDMA Channel Control Set
        //
        ulTemp = (UDMA_SIZE_32 | UDMA_SRC_INC_8 | UDMA_DST_INC_8);
        uDMAChannelControlSet(ulDMAChannelID[i] | UDMA_PRI_SELECT, ulTemp);                                                                           
                                                                  
        //
        //uDMA Channel Transfer Set
        //
        uDMAChannelTransferSet(ulDMAChannelID[i], UDMA_MODE_AUTO, ulSrcArray, ulDestArray ,64);
        ulRegVal = uDMAChannelModeGet(ulDMAChannelID[i]);
        ulReg = uDMAChannelSizeGet(ulDMAChannelID[i]);
            
        TestAssert((UDMA_MODE_AUTO == ulRegVal), 
                  "xspi API \"uDMAChannelTransferSet(ulDMAChannelID[i])\"error!");
        TestAssert((ulReg == 64), 
                  "xspi API \"uDMAChannelTransferSet(ulDMAChannelID[i])\"error!");
    }
}
//*****************************************************************************
//
//! \brief xdma 003 test execute main body.
//!
//! \return None.
//
//*****************************************************************************
static void xDma003Execute(void)
{
    xdma003_uDMAChannelTransferSet_Test();
}

//
// xdma register test case struct.
//
const tTestCase sTestXDma003 = {
    xDma003GetTest,
    xDma003Setup,
    xDma003TearDown,
    xDma003Execute
};

//
// Xdma test suits.
//
const tTestCase * const psPatternXdma02[] =
{
    &sTestXDma003,
    0
};
