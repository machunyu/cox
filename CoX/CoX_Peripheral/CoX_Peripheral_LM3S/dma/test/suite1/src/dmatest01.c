//*****************************************************************************
//
//! @page xdma_testcase xcore api test
//!
//! File: @ref dmatest01.c
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
//! \file dmatest01.c
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
//!\page test_xdma_api
//!
//!<h2>Description</h2>
//!Test xdma api. <br>
//!
//
//*****************************************************************************

static unsigned long ulDMAChannelID[] = {
xDMA_CHANNEL_0, xDMA_CHANNEL_1, xDMA_CHANNEL_2, xDMA_CHANNEL_3, xDMA_CHANNEL_4,
xDMA_CHANNEL_5, xDMA_CHANNEL_6, xDMA_CHANNEL_7, xDMA_CHANNEL_8, xDMA_CHANNEL_9, 
xDMA_CHANNEL_10, xDMA_CHANNEL_11, xDMA_CHANNEL_12, xDMA_CHANNEL_13, xDMA_CHANNEL_14, 
xDMA_CHANNEL_15, xDMA_CHANNEL_16, xDMA_CHANNEL_17, xDMA_CHANNEL_18, xDMA_CHANNEL_19, 
xDMA_CHANNEL_20, xDMA_CHANNEL_21, xDMA_CHANNEL_22, xDMA_CHANNEL_23, xDMA_CHANNEL_24, 
xDMA_CHANNEL_25, xDMA_CHANNEL_26, xDMA_CHANNEL_27, xDMA_CHANNEL_28, xDMA_CHANNEL_29, 
xDMA_CHANNEL_30, xDMA_CHANNEL_31};

static unsigned long ulDstDataWidth[] = {xDMA_DST_SIZE_8, xDMA_DST_SIZE_16,
                                         xDMA_DST_SIZE_32};
static unsigned long ulSrcDataWidth[] = {xDMA_SRC_SIZE_8, xDMA_SRC_SIZE_16,
                                         xDMA_SRC_SIZE_32};
static unsigned long ulDstInc[] = {xDMA_DST_INC_8, xDMA_DST_INC_16,
                                   xDMA_DST_INC_32, xDMA_DST_INC_NONE};
static unsigned long ulSrcInc[] = {xDMA_SRC_INC_8, xDMA_SRC_INC_16,
                                   xDMA_SRC_INC_32, xDMA_SRC_INC_NONE};

//
// 应用必须分配通道控制表，这是所有模式和通道的完整表。
//
unsigned char ucDMAControlTable[1024] __at(0x20001c00);

//*****************************************************************************
//
//! \brief Get the Test description of xdma002 api test.
//!
//! \return the desccription of the xdma002 test.
//
//*****************************************************************************
static char* xDma002GetTest(void)
{
    return "xdma, 002, uDMA Channel Control Set Test";
}

//*****************************************************************************
//
//! \brief something should do before the test execute of xdma002 test.
//!
//! \return None.
//
//*****************************************************************************
static void xDma002Setup(void)
{
    //
    // Enable Peripheral uDMA
    //
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UDMA);
}

//*****************************************************************************
//
//! \brief something should do after the test execute of xdma002 test.
//!
//! \return None.
//
//*****************************************************************************
static void xDma002TearDown(void)
{   
    SysCtlPeripheralReset(SYSCTL_PERIPH_UDMA);
    //
    // Disable Peripheral uDMA
    //    
    SysCtlPeripheralDisable(SYSCTL_PERIPH_UDMA);  
}

//*****************************************************************************
//
//! \brief xdma 003 test of uDMA Channel Control Set test .
//!
//! \return None.
//
//*****************************************************************************
static void xdma002_uDMAChannelControlSet_Test(void)
{
	unsigned long i, j, k, m, n, ulTemp1, ulTemp2;
	tDMAControlTable *pList;
	//
	// 设置通道控制表的基地址
	//
	uDMAControlBaseSet(ucDMAControlTable);

	//
	// Channel Control Set Test
	//
	for(i = 0;i < 32;i++)
	{
		for(j = 0; j < 3; j++)
		{
			for(k = 0; k < 3; k++)
			{
				for(m = 0; m < 4; m++)
				{
					for(n = 0; n< 4; n++)
					{
						ulTemp1 = ulDstDataWidth[j] | ulSrcDataWidth[k] | ulDstInc[m] | ulSrcInc[n];
						ulTemp2 = ulDMAChannelID[i] | UDMA_PRI_SELECT;
						uDMAChannelControlSet(ulTemp2, ulTemp1);
						pList = (tDMAControlTable *)xHWREG(UDMA_CTLBASE);
						TestAssert(pList[ulTemp2].ulControl == ulTemp1, "dma API error!");
					}
				}
			}
		}
	}
	
	for(i = 0;i < 32;i++)
	{
		for(j = 0; j < 3; j++)
		{
			for(k = 0; k < 3; k++)
			{
				for(m = 0; m < 4; m++)
				{
					for(n = 0; n< 4; n++)
					{
						ulTemp1 = ulDstDataWidth[j] | ulSrcDataWidth[k] | ulDstInc[m] | ulSrcInc[n];
						ulTemp2 = ulDMAChannelID[i] | UDMA_ALT_SELECT;
						uDMAChannelControlSet(ulTemp2, ulTemp1);
						pList = (tDMAControlTable *)xHWREG(UDMA_CTLBASE);
						TestAssert(pList[ulTemp2].ulControl == ulTemp1, "dma API error!");
					}
				}
			}
		}
	}
}

//*****************************************************************************
//
//! \brief xdma 002 test execute main body.
//!
//! \return None.
//
//*****************************************************************************
static void xDma002Execute(void)
{
    xdma002_uDMAChannelControlSet_Test();
}

//
// xdma register test case struct.
//
const tTestCase sTestXDma002Api = {
    xDma002GetTest,
    xDma002Setup,
    xDma002TearDown,
    xDma002Execute
};

//
// Xdma test suits.
//
const tTestCase * const psPatternXdma01[] =
{
    &sTestXDma002Api,
    0
};
