//*****************************************************************************
//
//! @page xuart_testcase xuart test
//!  
//! File: @ref xuart_testcase.c
//! 
//! <h2>Description</h2>
//! This module implements the test sequence for the xuart sub component.<br><br>
//! - \p Board: LM3S9B96 <br><br>
//! - \p Last-Time(about): 0.5s <br><br>
//! - \p Phenomenon: Success or failure information will be printed on the VCOM UART. <br><br>
//! .
//! 
//! <h2>Preconditions</h2>
//! The module requires the following options:<br><br>
//! - \p Option-define: 
//! <br>(1)None.<br><br>
//! - \p Option-hardware: 
//! <br>(1)Connect an USB cable to the development board.<br><br>
//! - \p Option-OtherModule:         
//! <br>None.<br>
//! .
//! In case some of the required options are not enabled then some or all tests
//! may be skipped or result FAILED.<br>
//! 
//! <h2>Test Cases</h2>
//! The module contain those sub tests:<br><br>
//! - \subpage test_xuart_Config
//! .
//! \file xuart_testcase.c
//! \brief xuart test source file
//! \file xuart_testcase.h
//! \brief xuart test header file <br>
//
//*****************************************************************************

#include "test.h"
#include "testcase.h"
#include "xhw_dma.h"
#include "xdma.h"

//*****************************************************************************
//
//! \page test_xuart_register test_xuart_register
//!
//! <h2>Description</h2>
//! 
//! Test xuart register. <br> 
//!
//
//*****************************************************************************

#define UART_BASE   UART1_BASE
#define xSYSCTL_PERIPH_UART  xSYSCTL_PERIPH_UART1

unsigned long uart0CallbackFunc(void *pvCBData, unsigned long ulEvent,                                       
                                unsigned long ulMsgParam, void *pvMsgData);

#define countof(x) sizeof(x)/sizeof(*x)

//
// uart rx and tx test 
//
char  sendData[] = {'0','1','2','3','4','5','6','7','8','9'};
char  recData[]  = {'0','0','0','0','0','0','0','0','0','0'};
#define dataNum  countof(sendData)
#define InitRecData()  do{                                                    \
                            int i = dataNum - 1;                              \
                            while(i>=0)                                       \
                                recData[i--] = '0';                           \
                          }while(0)

volatile unsigned int sendNum=0, recNum=0;

//
// line config test value
//
unsigned long wordLength[] = {UART_CONFIG_WLEN_8,UART_CONFIG_WLEN_7, 
                              UART_CONFIG_WLEN_6,UART_CONFIG_WLEN_5};

unsigned long parity[] = {UART_CONFIG_PAR_NONE,UART_CONFIG_PAR_EVEN,
                          UART_CONFIG_PAR_ODD, UART_CONFIG_PAR_ONE,
                          UART_CONFIG_PAR_ZERO};

unsigned long stopbit[] = {UART_CONFIG_STOP_1,UART_CONFIG_STOP_2};

unsigned long ulBlock[] = {UART_BLOCK_TX, UART_BLOCK_RX};

//
// FIFO test value
//
unsigned long ulTxLevel[] = {UART_FIFO_TX1_8, UART_FIFO_TX2_8, UART_FIFO_TX4_8,
                             UART_FIFO_TX6_8, UART_FIFO_TX7_8};

unsigned long ulRxLevel[] = {UART_FIFO_RX1_8, UART_FIFO_RX2_8, UART_FIFO_RX4_8,
                             UART_FIFO_RX6_8, UART_FIFO_RX7_8};

#define  fifoLevelNum   countof(ulRxLevel)

//
// UART LIN Control
//
unsigned long LinSyncBreakLength[] = {UART_LIN_SYNC_BREAK_LEN_13, UART_LIN_SYNC_BREAK_LEN_14,
                                      UART_LIN_SYNC_BREAK_LEN_15, UART_LIN_SYNC_BREAK_LEN_16};

unsigned long LinMode[] = {UART_LIN_MODE_MASTER, UART_LIN_MODE_SLAVE};
//
// flow control test
//
unsigned long ulFlowCtlCfg[] = {UART_FLOWCONTROL_TX, UART_FLOWCONTROL_RX, 
                                (UART_FLOWCONTROL_TX | UART_FLOWCONTROL_RX), 
                                UART_FLOWCONTROL_NONE};

#define  flowCtlNum     countof(ulFlowCtlCfg)

//
// DMA control test
//
unsigned long ulDMAFlag[] = {UART_DMA_RX, UART_DMA_TX, UART_DMA_ERR_RXSTOP};
#define   DMACtlNum     countof(ulDMAFlag)

unsigned long ulModemCfg[] = {UART_OUTPUT_RTS, UART_OUTPUT_DTR};
unsigned long ulModemSt[] = {UART_OUTPUT_RTS, UART_OUTPUT_DTR};

#define  modemStNum     countof(ulModemSt)
#define  modemCfgNum    countof(ulModemCfg)


//*****************************************************************************
//
//! Get the Test description of xuart001  test.
//!
//! \return the desccription of the xuart001 test.
//
//*****************************************************************************
static char* xuart001GetTest(void)
{
    return "xuart [001]: xuart uart Config ,rx,tx and interrupt test";
}

//*****************************************************************************
//
//! Something should do before the test execute of xuart001 test.
//!
//! \return None.
//
//*****************************************************************************
static void xuart001Setup(void)
{
    xSysCtlPeripheralReset(xSYSCTL_PERIPH_UART);
    xSysCtlPeripheralEnable(xSYSCTL_PERIPH_UART);   
}

//*****************************************************************************
//
//! Something should do after the test execute of xuart001 test.
//!
//! \return None.
//
//*****************************************************************************
static void xuart001TearDown(void)
{
    xSysCtlPeripheralDisable(xSYSCTL_PERIPH_UART);   
}

//*****************************************************************************
//
//! !brief xuart 001 test for line config.
//!
//! \return None.
//
//*****************************************************************************
void xuart001Execute_NormalConfig(void)
{
    int w, p, s,w1, p1, s1;
    unsigned long ulBuad, ulConfig, ulTemp1;
    
    w1 = countof(wordLength);
    p1 = countof(parity);
    s1 = countof(stopbit);  

    //
    // the combined test of word length,parity and stop bit.
    //
    for(w=0; w<w1; w++)
    {
        for(p=0; p<p1; p++)
        {   
            UARTParityModeSet(UART_BASE, parity[p]);
            ulTemp1 = UARTParityModeGet(UART_BASE);
            TestAssert(parity[p] == ulTemp1, 
                  "xuart API \"UARTParityModeSet\" or " 
                  "\"UARTParityModeGet\" error!");

            for(s=0; s<s1; s++)
            {
                ulTemp1 = (wordLength[w] | parity[p] | stopbit[s]);
                UARTConfigSetExpClk(UART_BASE, 115200, ulTemp1);     
                UARTConfigGetExpClk(UART_BASE, &ulBuad, &ulConfig);
                TestAssert((ulConfig & ulTemp1) == ulTemp1, 
                   "xuart API \"UARTConfigSetExpClk\" or "
                   "\"UARTConfigGetExpClk\" error!");
            }
        } 
    }
    
    //
    // Break Control test
    //
    UARTBreakCtl(UART_BASE, xtrue);
    ulTemp1 = xHWREG(UART_BASE + UART_LCRH) & UART_LCRH_BRK;
    TestAssert(ulTemp1 == UART_LCRH_BRK, 
                 "xuart API \"UARTBreakCtl\" error!");
    
    UARTBreakCtl(UART_BASE, xfalse);
    ulTemp1 = xHWREG(UART_BASE + UART_LCRH) & UART_LCRH_BRK;
    TestAssert(ulTemp1 == 0, 
                 "xuart API \"UARTBreakCtl\" error!");
}

//*****************************************************************************
//
//! !brief callback function of uart0 interrupt handler.
//!
//! \return None.
//
//*****************************************************************************
unsigned long uart0CallbackFunc(void *pvCBData, unsigned long ulEvent,
                                unsigned long ulMsgParam, void *pvMsgData)                                                                                  
{
    if(ulEvent == xUART_INT_TX)
    {
    }
    if(ulEvent == xUART_INT_RX)
    {
        recData[recNum++] = UARTCharGet(UART0_BASE);                              
        return 0; 
    }
    return 0;
}

void xuart001Execute_uartInt(void)
{
    int i;
    unsigned char info[] = "Please input(0123456789) : ";
    recNum = 0;
    
    //
    // Initialize recData[] to '0'
    //
    InitRecData();

    //
    // Register the uart0 interrupt handler, Enable uart0 receive interrupt.
    //
    xUARTIntCallbackInit(UART0_BASE, uart0CallbackFunc);
    UARTIntEnable(UART0_BASE, UART_INT_RX);
    xIntEnable(INT_UART0);
    xIntMasterEnable();

    for(i = 0; i < countof(info); i++)
    {
        UARTCharPut(UART0_BASE, info[i]);
    }
            
    //
    // wait the hyperterminal to transmit data "0123456789"
    //
    while(recData[dataNum-1] != '9');

    //
    // Check the data received.
    //
    for(i=0; i<dataNum; i++)
    {
        TestAssert(recData[i] == ('0' + i), 
                    "xuart API \"receive\" or \"interrupt\" error!");      
    }
        
    UARTIntDisable(UART0_BASE, UART_INT_RX);
}

//*****************************************************************************
//
//! xuart001 test execute main body.
//
//! \return None.
//
//*****************************************************************************
static void xuart001Execute(void)
{
    //
    // Line configuration test
    //
    xuart001Execute_NormalConfig();
    
    //
    // rx,tx and interrupt test
    //
#if !(xUART_CONFIG_DMA_INT)
    xuart001Execute_uartInt(); 
#endif    
}

//
// xuart Config test case struct.
//
const tTestCase sTestxuart001UART = {
    xuart001GetTest,
    xuart001Setup,
    xuart001TearDown,
    xuart001Execute
};

//*****************************************************************************
//
//! Get the Test description of xuart002  test.
//!
//! \return the desccription of the xuart002 test.
//
//*****************************************************************************
static char* xuart002GetTest(void)
{
    return "xuart [002]: xuart FIFO test";
}

//*****************************************************************************
//
//! Something should do before the test execute of xuart002 test.
//!
//! \return None.
//
//*****************************************************************************
static void xuart002Setup(void)
{
    SysCtlPeripheralEnable(xSYSCTL_PERIPH_UART);
}

//*****************************************************************************
//
//! Something should do after the test execute of xuart002 test.
//!
//! \return None.
//
//*****************************************************************************
static void xuart002TearDown(void)
{
    xSysCtlPeripheralDisable(xSYSCTL_PERIPH_GPIOC);
    xSysCtlPeripheralDisable(xSYSCTL_PERIPH_UART);
}

void xuart002Execute_FIFOConfig(void)
{
    unsigned long ulTemp1, ulTemp2, i;
        
    UARTFIFOEnable(UART_BASE);
    ulTemp1 = xHWREG(UART_BASE + UART_LCRH) & UART_LCRH_FEN;
    TestAssert(ulTemp1 == UART_LCRH_FEN, 
                 "xuart API \"UARTFIFOEnable\" error!");
    //
    // test for rx trigger level config
    //
    for(i=0; i<fifoLevelNum; i++)
    {
        UARTFIFOLevelSet(UART_BASE, ulTxLevel[i], ulRxLevel[i]); 
        UARTFIFOLevelGet(UART_BASE, &ulTemp1, &ulTemp2);
        TestAssert((ulTemp1 == ulTxLevel[i]) || (ulTemp2 == ulRxLevel[i]), 
           "xuart API \"UARTFIFOLevelSet\" or "
           "\"UARTFIFOLevelGet\" error!");
    }
        
    UARTFIFODisable(UART_BASE);
    ulTemp1 = xHWREG(UART_BASE + UART_LCRH) & UART_LCRH_FEN;
    TestAssert(ulTemp1 == 0, "xuart API \"UARTFIFOEnable\" error!");
}

void xuart002Execute_SmartCard_Register(void)
{
    unsigned long ulRegVal;
    UARTSmartCardEnable(UART_BASE);
    ulRegVal = xHWREG(UART_BASE + UART_CTL) & UART_CTL_SMART;
    TestAssert(ulRegVal == UART_CTL_SMART, 
                  "xuart API \"UARTSmartCardEnable\" error!");
    
    UARTSmartCardDisable(UART_BASE);
    ulRegVal = xHWREG(UART_BASE + UART_CTL) & UART_CTL_SMART;
    TestAssert(ulRegVal == 0, "xuart API \"UARTSmartCardEnable\" error!");
}

void xuart002Execute_SmartCard_Function(void)
{
    //
    // enable smartcard 
    //
    UARTSmartCardEnable(UART_BASE);
    
    //
    // The uart is configed as smartcard, the UnTx signal is used as a bit clock,
    // and the UnRx signal is used as the half-duplex communication line 
    // connected to the smartcard.
    //
    UARTSmartCardConfig(UART_BASE, 115200);
    
    //
    // a gpio signal pin is used to generate the reset singnal to the smartcard
    //
    xSysCtlPeripheralEnable(xSYSCTL_PERIPH_GPIOC);
    xGPIOSPinTypeGPIOOutput(PC4);
    
        
}
void xuart002Execute_SmartCard(void)
{
    xuart002Execute_SmartCard_Register();
    xuart002Execute_SmartCard_Function();
}
//*****************************************************************************
//
//! xuart002 test execute main body.
//! \return None.
//
//*****************************************************************************
static void xuart002Execute(void)
{
    //
    // FIFO config
    //
    xuart002Execute_FIFOConfig();
        
    //
    // SmartCard config
    //
    xuart002Execute_SmartCard();        
}

//
// xuart FIFO test case struct.
//
const tTestCase sTestxuart002FIFO = {
    xuart002GetTest,
    xuart002Setup,
    xuart002TearDown,
    xuart002Execute
};

//*****************************************************************************
//
//! Get the Test description of xuart003  test.
//!
//! \return the desccription of the xuart003 test.
//
//*****************************************************************************
static char* xuart003GetTest(void)
{
    return "xuart [003]: xuart IrDA test";
}

//*****************************************************************************
//
//! Something should do before the test execute of xuart003 test.
//!
//! \return None.
//
//*****************************************************************************
static void xuart003Setup(void)
{
    xSysCtlPeripheralReset(xSYSCTL_PERIPH_UART);
    xSysCtlPeripheralEnable(xSYSCTL_PERIPH_UART);
}

//*****************************************************************************
//
//! Something should do after the test execute of xuart003 test.
//!
//! \return None.
//
//*****************************************************************************
static void xuart003TearDown(void)
{
    xSysCtlPeripheralDisable(xSYSCTL_PERIPH_UART);
}

void xuart003Execute_IrDAConfig(void)
{
    unsigned long ulTemp;   

    UARTIrDAEnable(UART_BASE);
    ulTemp = xHWREG(UART_BASE + UART_CTL) & 0x02;
    TestAssert(ulTemp == 0x02,
                   "xuart API \"UARTEnableIrDA\" error!");
    
    ulTemp = (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_1 | UART_CONFIG_PAR_NONE); 

    UARTIrDAConfig(UART_BASE, 115200, ulTemp, UART_IRDA_MODE_NORMAL);
    ulTemp = xHWREG(UART_BASE + UART_CTL) & UART_CTL_SIRLP;
    TestAssert(ulTemp == 0,
                   "xuart API \"UARTIrDAConfig\" error!");
    UARTIrDAConfig(UART_BASE, 115200, ulTemp, UART_IRDA_MODE_LOW_POWER);
    ulTemp = xHWREG(UART_BASE + UART_CTL) & UART_CTL_SIRLP;
    TestAssert(ulTemp == UART_CTL_SIRLP,
                   "xuart API \"UARTIrDAConfig\" error!");
    
    UARTIrDADisable(UART_BASE);
    ulTemp = xHWREG(UART_BASE + UART_CTL) & 0x02;
    TestAssert(ulTemp == 0,
                   "xuart API \"UARTDisableIrDA\" error!");
}

//*****************************************************************************
//
//! xuart003 test execute main body.
//! \return None.
//
//*****************************************************************************
static void xuart003Execute(void)
{
    //
    // IrDA config
    //
    xuart003Execute_IrDAConfig();
}

//
// xuart IrDA test case struct.
//
const tTestCase sTestxuart003IrDA = {
    xuart003GetTest,
    xuart003Setup,
    xuart003TearDown,
    xuart003Execute
};

//*****************************************************************************
//
//! Get the Test description of xuart004  test.
//!
//! \return the desccription of the xuart004 test.
//
//*****************************************************************************
static char* xuart004GetTest(void)
{
    return "xuart [004]: xuart LIN test";
}

//*****************************************************************************
//
//! Something should do before the test execute of xuart004 test.
//!
//! \return None.
//
//*****************************************************************************
static void xuart004Setup(void)
{
    xSysCtlPeripheralReset(xSYSCTL_PERIPH_UART);
    xSysCtlPeripheralEnable(xSYSCTL_PERIPH_UART);
}

//*****************************************************************************
//
//! Something should do after the test execute of xuart004 test.
//!
//! \return None.
//
//*****************************************************************************
static void xuart004TearDown(void)
{
    xSysCtlPeripheralDisable(xSYSCTL_PERIPH_UART);
}

void xuart004Execute_LinConfig(void)
{
    unsigned long ulTemp, ulRegVal, i, j;    

    UARTLINEnable(UART_BASE);
    ulTemp = xHWREG(UART_BASE + UART_CTL) & 0x40;
    TestAssert(ulTemp == 0x40,
                   "xuart API \"UARTLINEnable\" error!");

    //
    // Enable LIN, Set the LIN Break Field Length and LIN mode
    //
    for(j = 0;j < 2; j++)
    {
        for(i = 0;i < 4; i++)
        {
            ulTemp = LinSyncBreakLength[i] | LinMode[j];
            UARTLINConfig(UART_BASE, 115200, ulTemp);
            ulRegVal = xHWREG(UART_BASE + UART_LCTL) ;
            TestAssert(ulTemp == ulRegVal,
                       "xuart API \"UARTLINConfig\" error!");
        }
    }
    
    //
    // Disable Lin
    //
    UARTLINDisable(UART_BASE);
    ulTemp = xHWREG(UART_BASE + UART_CTL) & 0x40;
    TestAssert(ulTemp == 0, "xuart API \"UARTLINDisable\" error!");                 
}

//*****************************************************************************
//
//! xuart004 test execute main body.
//! \return None.
//
//*****************************************************************************
static void xuart004Execute(void)
{
    //
    // Lin configuration and enable/disable.
    //
    xuart004Execute_LinConfig();   
}

//
// xuart Lin test case struct.
//
const tTestCase sTestxuart004Lin = {
    xuart004GetTest,
    xuart004Setup,
    xuart004TearDown,
    xuart004Execute
};

//*****************************************************************************
//
//! Get the Test description of xuart005  test.
//!
//! \return the desccription of the xuart005 test.
//
//*****************************************************************************
static char* xuart005GetTest(void)
{
    return "xuart [005]: xuart flow control test";
}

//*****************************************************************************
//
//! Something should do before the test execute of xuart005 test.
//!
//! \return None.
//
//*****************************************************************************
static void xuart005Setup(void)
{        
    xSysCtlPeripheralReset(xSYSCTL_PERIPH_UART1);
    xSysCtlPeripheralEnable(xSYSCTL_PERIPH_UART1);
}

//*****************************************************************************
//
//! Something should do after the test execute of xuart005 test.
//!
//! \return None.
//
//*****************************************************************************
static void xuart005TearDown(void)
{
    xSysCtlPeripheralDisable(xSYSCTL_PERIPH_UART1);
}

//*****************************************************************************
//
//! test for flow control config, only uart1 can be configed as this function.
//!
//! \return None.
//
//*****************************************************************************
void xuart005Execute_flowControlConfig(void)
{
    unsigned long ulTemp, i;

    //
    // Enable/Disable RTS and CTS
    //
    for(i=0; i<flowCtlNum; i++)
    {
        UARTFlowControlSet(xUART1_BASE, ulFlowCtlCfg[i]);
        ulTemp = UARTFlowControlGet(xUART1_BASE);
        TestAssert(ulTemp == ulFlowCtlCfg[i],
                   "xuart API \"UARTFlowControlSet\" or "
                   "\"UARTFlowControlGet\" error!");
    }  
}
//*****************************************************************************
//
//! xuart005 test execute flow control main body.
//! \return None.
//
//*****************************************************************************
static void xuart005Execute(void)
{
    //
    // uart flow control config
    //
    xuart005Execute_flowControlConfig();   
}

//
// xuart flow control test case struct.
//
const tTestCase sTestxuart005flowCtl = {
    xuart005GetTest,
    xuart005Setup,
    xuart005TearDown,
    xuart005Execute
};

//*****************************************************************************
//
//! Get the Test description of xuart006  test.
//!
//! \return the desccription of the xuart006 test.
//
//*****************************************************************************
static char* xuart006GetTest(void)
{
    return "xuart [006]: xuart Modem test";
}

//*****************************************************************************
//
//! Something should do before the test execute of xuart006 test.
//!
//! \return None.
//
//*****************************************************************************
static void xuart006Setup(void)
{
    xSysCtlPeripheralReset(xSYSCTL_PERIPH_UART1);
    xSysCtlPeripheralEnable(xSYSCTL_PERIPH_UART1);
}

//*****************************************************************************
//
//! Something should do after the test execute of xuart006 test.
//!
//! \return None.
//
//*****************************************************************************
static void xuart006TearDown(void)
{
    xSysCtlPeripheralDisable(xSYSCTL_PERIPH_UART1);
}

//*****************************************************************************
//
//! test for modem config, only uart1 can be configed as this function.
//!
//! \return None.
//
//*****************************************************************************
void xuart006Execute_ModemConfig(void)
{
    unsigned long ulTemp, i;
       
    //
    // Set RTS Trigger Level
    //
    for(i=0; i<modemCfgNum; i++)
    {
        UARTModemControlSet(xUART1_BASE, ulModemCfg[i]);
        ulTemp = UARTModemControlGet(xUART1_BASE); 
  
        TestAssert(ulTemp == ulModemCfg[i],
                   "xuart API \"UARTModemControlSet\" or "
                   "\"UARTModemControlGet\" error!");   
        
        UARTModemControlClear(xUART1_BASE, ulModemCfg[i]);
        ulTemp = (xHWREG(xUART1_BASE + UART_CTL) & ulModemCfg[i]);
        TestAssert(ulTemp == 0,
                   "xuart API \"UARTModemControlClear\" error!");
            
        UARTModemStatusGet(xUART1_BASE);
    }
}
//*****************************************************************************
//
//! xuart006 test execute main body.
//! \return None.
//
//*****************************************************************************
static void xuart006Execute(void)
{
    //
    // test for modem config
    //
    xuart006Execute_ModemConfig();
}

//
// xuart Config test case struct.
//
const tTestCase sTestxuart006Modem = {
    xuart006GetTest,
    xuart006Setup,
    xuart006TearDown,
    xuart006Execute
};

//*****************************************************************************
//
//! Get the Test description of xuart007  test.
//!
//! \return the desccription of the xuart007 test.
//
//*****************************************************************************
static char* xuart007GetTest(void)
{
    return "xuart [007]: xuart DMA test";
}

//*****************************************************************************
//
//! Something should do before the test execute of xuart007 test.
//!
//! \return None.
//
//*****************************************************************************
static void xuart007Setup(void)
{
    xSysCtlPeripheralReset(xSYSCTL_PERIPH_UART);
    xSysCtlPeripheralEnable(xSYSCTL_PERIPH_UART);
}

//*****************************************************************************
//
//! Something should do after the test execute of xuart007 test.
//!
//! \return None.
//
//*****************************************************************************
static void xuart007TearDown(void)
{
    xSysCtlPeripheralDisable(xSYSCTL_PERIPH_UART);
}

//*****************************************************************************
//
//! test for DMA register config.
//!
//! \return None.
//
//*****************************************************************************
void xuart007Execute_DMA_Register(void)
{
    unsigned long i, ulTemp;
    
    for(i = 0; i < DMACtlNum; i++)
    {
        UARTDMAEnable(UART_BASE, ulDMAFlag[i]);
        ulTemp = (xHWREG(UART_BASE + UART_DMACTL) & ulDMAFlag[i]);
        TestAssert(ulTemp == ulDMAFlag[i],
                                "xuart API \"UARTDMAEnable\" error!");
    }
        
    for(i = 0; i < DMACtlNum; i++)
    {
        UARTDMADisable(UART_BASE, ulDMAFlag[i]);
        ulTemp = (xHWREG(UART_BASE + UART_DMACTL) & ulDMAFlag[i]);
        TestAssert(ulTemp == 0, "xuart API \"UARTDMADisable\" error!");                                    
    }        
        
    UARTRxErrorClear(UART_BASE);
    ulTemp = UARTRxErrorGet(UART_BASE);
    TestAssert(ulTemp == 0, 
               "xuart API \"UARTRxErrorClear or UARTRxErrorGet\" error!");                                        
}

#if (xUART_CONFIG_DMA_INT)
//*****************************************************************************
//
//! !brief callback function of uart dma  interrupt handler.
//!
//! \return None.
//
//*****************************************************************************
unsigned long UARTDMACallbackFunc(void *pvCBData, unsigned long ulEvent,
                                unsigned long ulMsgParam, void *pvMsgData)                                                                                  
{       
    return 0;
}

//*****************************************************************************
//
//! test for DMA Int function.
//!
//! \return None.
//
//*****************************************************************************
void xuart007Execute_DMAInt_Function(void)
{
    //xSysCtlPeripheralEnable(xSYSCTL_PERIPH_DMA);
    //xDMAEnable();
    //UARTDMAEnable(UART_BASE, UART_DMA_TX);
}
#endif

//*****************************************************************************
//
//! xuart007 test DMA config.
//! \return None.
//
//*****************************************************************************
static void xuart007Execute(void)
{
    xuart007Execute_DMA_Register();
#if (xUART_CONFIG_DMA_INT)
    xuart007Execute_DMAInt_Function();    
#endif
}

//
// xuart Config test case struct.
//
const tTestCase sTestxuart007DMA = {
    xuart007GetTest,
    xuart007Setup,
    xuart007TearDown,
    xuart007Execute
};

//
// xuart test suits.
//
const tTestCase * const psPatternxUART[] =
{
    &sTestxuart001UART,
    &sTestxuart002FIFO,
    &sTestxuart003IrDA,
    &sTestxuart004Lin,
    &sTestxuart005flowCtl,
    &sTestxuart006Modem,
    &sTestxuart007DMA,
    0
};
