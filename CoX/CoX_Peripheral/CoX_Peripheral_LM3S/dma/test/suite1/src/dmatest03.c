//*****************************************************************************
//
//! @page xdma_testcase xcore api test
//!
//! File: @ref dmatest03.c
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
//! \file dmatest03.c
//! \brief xdma test source file
//! \brief xdma test header file <br>
//*****************************************************************************

#include "test.h"
#include "xhw_dma.h"
#include "xdma.h"
#include "absacc.h"

static unsigned long ulSrcTemp[64] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,
                                      0x11121314, 0x15161718, 0x191A1B1C, 0x1D1E1F20,
                                      0x21222324, 0x25262728, 0x292A2B2C, 0x2D2E2F30,
                                      0x31323334, 0x35363738, 0x393A3B3C, 0x3D3E3F40,
                                      0x41424344, 0x45464748, 0x494A4B4C, 0x4D4E4F50,
                                      0x51525354, 0x55565758, 0x595A5B5C, 0x5D5E5F60,
                                      0x61626364, 0x65666768, 0x696A6B6C, 0x6D6E6F70,
                                      0x71727374, 0x75767778, 0x797A7B7C, 0x7D7E7F80};

static unsigned long ulDestTemp[64];
extern unsigned char ucDMAControlTable[1024];

//
// Install callback function
//
unsigned long DmaChannel0Callback(void *pvCBData,  unsigned long ulEvent,
                                       unsigned long ulMsgParam,
                                       void *pvMsgData)
{
     TestEmitToken('a');
     return 0;
}
unsigned long DmaChannel1Callback(void *pvCBData,  unsigned long ulEvent,
                                       unsigned long ulMsgParam,
                                       void *pvMsgData)
{
     TestEmitToken('b');
     return 0;
}
unsigned long DmaChannel2Callback(void *pvCBData,  unsigned long ulEvent,
                                       unsigned long ulMsgParam,
                                       void *pvMsgData)
{
     TestEmitToken('c');
     return 0;
}
unsigned long DmaChannel3Callback(void *pvCBData,  unsigned long ulEvent,
                                       unsigned long ulMsgParam,
                                       void *pvMsgData)
{
     TestEmitToken('d');
     return 0;
}

unsigned long DmaChannel4Callback(void *pvCBData,  unsigned long ulEvent,
                                       unsigned long ulMsgParam,
                                       void *pvMsgData)
{
     TestEmitToken('e');
     return 0;
}
unsigned long DmaChannel5Callback(void *pvCBData,  unsigned long ulEvent,
                                       unsigned long ulMsgParam,
                                       void *pvMsgData)
{
     TestEmitToken('f');
     return 0;
}

unsigned long DmaChannel6Callback(void *pvCBData,  unsigned long ulEvent,
                                       unsigned long ulMsgParam,
                                       void *pvMsgData)
{
     TestEmitToken('g');
     return 0;
}

unsigned long DmaChannel7Callback(void *pvCBData,  unsigned long ulEvent,
                                       unsigned long ulMsgParam,
                                       void *pvMsgData)
{
     TestEmitToken('h');
     return 0;
}

unsigned long DmaChannel8Callback(void *pvCBData,  unsigned long ulEvent,
                                       unsigned long ulMsgParam,
                                       void *pvMsgData)
{
     TestEmitToken('i');
     return 0;
}
//
// Callback function
//
xtEventCallback DmaCallbackFunc[9] = {DmaChannel0Callback,
                                      DmaChannel1Callback,
                                      DmaChannel2Callback,
                                      DmaChannel3Callback,
                                      DmaChannel4Callback,
                                      DmaChannel5Callback,
                                      DmaChannel6Callback,
                                      DmaChannel7Callback,
                                      DmaChannel8Callback};
//*****************************************************************************
//
//! \brief Get the Test description of xdma004 register test.
//!
//! \return the desccription of the xdma004 test.
//
//*****************************************************************************
static char* xDma004GetTest(void)
{
    return "xdma, 004, xdma memory to memory and intrrupt test";
}

//*****************************************************************************
//
//! \brief something should do before the test execute of xdma004 test.
//!
//! \return None.
//
//*****************************************************************************
static void xDma004Setup(void)
{
    //
    // Enable Peripheral uDMA
    //
    SysCtlPeripheralReset(SYSCTL_PERIPH_UDMA);  
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UDMA);
}

//*****************************************************************************
//
//! \brief something should do after the test execute of xdma004 test.
//!
//! \return None.
//
//*****************************************************************************
static void xDma004TearDown(void)
{   
    //
    // Disable Peripheral uDMA
    //    
    SysCtlPeripheralDisable(SYSCTL_PERIPH_UDMA);  
}

//*****************************************************************************
//
//! \brief uDMA Configure and Trig transfer
//!
//! \param None
//!
//! \details This function is to configure uDMA and transfer to mem from mem 
//!           in soft mode.
//!
//! \return None
//
//*****************************************************************************
static void xdma004_uDMATransfer_Test(void)
{
	  unsigned long i, ulTemp;
	
	  uDMAEnable();
 
    uDMAControlBaseSet(ucDMAControlTable);
	
	  //uDMAChannelAttributeDisable(UDMA_CHANNEL_SW, UDMA_CONFIG_ALL);

    ulTemp = (UDMA_SIZE_32 | UDMA_SRC_INC_32 | UDMA_DST_INC_32);
    uDMAChannelControlSet(UDMA_CHANNEL_SW | UDMA_PRI_SELECT, ulTemp);                                                                           																													
    uDMAChannelTransferSet(UDMA_CHANNEL_SW, UDMA_MODE_AUTO, ulSrcTemp, ulDestTemp ,64);
	
	  uDMAChannelEnable(UDMA_CHANNEL_SW);
	  uDMAChannelRequest(UDMA_CHANNEL_SW);
	
	  for(i = 0;i < 64;i++)
		{
				TestAssert((ulSrcTemp[i] == ulDestTemp[i]), "dma API error!");
		}
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
void xdma004_uDMAInit(void)
{

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
static void xdma004_uDMAInterrupt_Test(void)
{
    unsigned int i, ulTemp;
    
	  for(i = 0;i < 64;i++)
			ulDestTemp[i] =0;
	
	  uDMAEnable();

		ulTemp = (UDMA_SIZE_32 | UDMA_SRC_INC_32 | UDMA_DST_INC_32);
    uDMAChannelControlSet(UDMA_CHANNEL_SW | UDMA_PRI_SELECT, ulTemp);  
		uDMAChannelTransferSet(UDMA_CHANNEL_SW, UDMA_MODE_AUTO, ulSrcTemp, ulDestTemp ,64);
 
	  xDMAChannelIntCallbackInit(UDMA_CHANNEL_SW, DmaCallbackFunc[0]);
	
		uDMAChannelEnable(UDMA_CHANNEL_SW);
	  xIntEnable(INT_UDMA);    
    xIntPrioritySet(INT_UDMA, 1);
	
	  uDMAChannelRequest(UDMA_CHANNEL_SW);

    TestAssertQBreak("a", "Transfer Over Interrupy fialed!", 5000000);
}

//*****************************************************************************
//
//! \brief xdma 004 test execute main body.
//!
//! \return None.
//
//*****************************************************************************
static void xDma004Execute(void)
{
    xdma004_uDMATransfer_Test();
	  xdma004_uDMAInterrupt_Test();
}

//
// xdma register test case struct.
//
const tTestCase sTestXDma004 = {
    xDma004GetTest,
    xDma004Setup,
    xDma004TearDown,
    xDma004Execute
};

//
// Xdma test suits.
//
const tTestCase * const psPatternXdma03[] =
{
    &sTestXDma004,
    0
};
