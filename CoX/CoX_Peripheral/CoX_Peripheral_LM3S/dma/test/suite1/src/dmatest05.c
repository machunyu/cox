//*****************************************************************************
//
//! @page xdma_testcase xcore api test
//!
//! File: @ref dmatest05.c
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
//! \file dmatest05.c
//! \brief xdma test source file
//! \brief xdma test header file <br>
//*****************************************************************************

#include "test.h"
#include "xhw_dma.h"
#include "xhw_uart.h"
#include "xdma.h"
#include "xuart.h"


extern unsigned char ucDMAControlTable[1024];

//
// Install callback function
//
unsigned long UARTDmaCallbackFunc0(void *pvCBData,  unsigned long ulEvent,
                                   unsigned long ulMsgParam, void *pvMsgData)
{
    TestEmitToken('a');
#if 0
    ulMode = uDMAChannelModeGet(xDMA_CHANNEL_8 | UDMA_PRI_SELECT); /* 读取UART0RX的主结构模式      */  
    if(ulMode == UDMA_MODE_STOP)                                   /* 停止模式表示传输结束         */
    {
        uDMAChannelTransferSet(xDMA_CHANNEL_8 | UDMA_PRI_SELECT,
                               UDMA_MODE_PINGPONG,(void*)0x4000C000,
                               (void *)0x4000C000, 
                                8);                /* Reset                    */
   }
   while(uDMAChannelIsEnabled(xDMA_CHANNEL_8)==0)
   {
       uDMAChannelEnable(xDMA_CHANNEL_8);   /* 重新使能UART0 RX通道         */
   } 
#endif	 
   return 0;
}

//*****************************************************************************
//
//! \brief Get the Test description of xdma004 register test.
//!
//! \return the desccription of the xdma004 test.
//
//*****************************************************************************
static char* xDma006GetTest(void)
{
    return "xdma, 006, xdma uart to memory and reprint test";
}

//*****************************************************************************
//
//! \brief something should do before the test execute of xdma004 test.
//!
//! \return None.
//
//*****************************************************************************
static void xDma006Setup(void)
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
static void xDma006TearDown(void)
{   
    //
    // Disable Peripheral uDMA
    //    
    SysCtlPeripheralDisable(SYSCTL_PERIPH_UDMA); 
    SysCtlPeripheralDisable(SYSCTL_PERIPH_GPIOA);
    SysCtlPeripheralReset(SYSCTL_PERIPH_GPIOA);		
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    
    xSPinTypeUART(UART0RX, PA0);
    xSPinTypeUART(UART0TX, PA1);

    xSysCtlPeripheralReset(xSYSCTL_PERIPH_UART0);
    xSysCtlPeripheralEnable(xSYSCTL_PERIPH_UART0);                    

    UARTConfigSetExpClk(UART0_BASE, 115200, (UART_CONFIG_WLEN_8     | 
                                             UART_CONFIG_STOP_1     | 
                                             UART_CONFIG_PAR_NONE));
    UARTEnable(UART0_BASE, (UART_BLOCK_UART | UART_BLOCK_TX | UART_BLOCK_RX));
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
void xdma006_uDMAInit(void)
{  
    unsigned long ulTemp;

    uDMAEnable();
    uDMAControlBaseSet(ucDMAControlTable);
	
    uDMAChannelAttributeDisable(xDMA_CHANNEL_8, UDMA_ATTR_USEBURST      |
	                                            UDMA_ATTR_ALTSELECT     |
	                                            UDMA_ATTR_HIGH_PRIORITY |
	                                            UDMA_ATTR_REQMASK);
	  
    //uDMAChannelAttributeEnable(UDMA_CHANNEL_UART0RX, UDMA_ATTR_ALTSELECT ); 

    ulTemp = UDMA_SIZE_8 | UDMA_SRC_INC_NONE | UDMA_DST_INC_NONE |UDMA_ARB_8;
    uDMAChannelControlSet(xDMA_CHANNEL_8 | UDMA_PRI_SELECT, ulTemp);

    uDMAChannelTransferSet(xDMA_CHANNEL_8 | UDMA_PRI_SELECT, UDMA_MODE_PINGPONG, 
												             (void*)0x4000c000,
												             (void*)0x4000c000, 
												              8);
    uDMAChannelEnable(xDMA_CHANNEL_8);
    UARTDMAEnable(UART0_BASE,UART_DMA_RX | UART_DMA_TX);
    UARTFIFOLevelSet(UART0_BASE,UART_FIFO_TX6_8,UART_FIFO_RX4_8);

    //xDMAChannelIntCallbackInit(xDMA_CHANNEL_8, UARTDmaCallbackFunc0);
    //xIntMasterEnable();
    //xIntEnable(INT_UART0);
}

void Delay(unsigned int t)
{
    while(t--);
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
static void xdma006_uDMATransfer_Test(void)
{
    xdma006_uDMAInit();

    TestAssertQBreak("a", "UART Receive Interrupy  fialed!", 5000000);
}

//*****************************************************************************
//
//! \brief xdma 004 test execute main body.
//!
//! \return None.
//
//*****************************************************************************
static void xDma006Execute(void)
{
    xdma006_uDMATransfer_Test();
}

//
// xdma register test case struct.
//
const tTestCase sTestXDma006 = {
    xDma006GetTest,
    xDma006Setup,
    xDma006TearDown,
    xDma006Execute
};

//
// Xdma test suits.
//
const tTestCase * const psPatternXdma05[] =
{
    &sTestXDma006,
    0
};
