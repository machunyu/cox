//*****************************************************************************
//
//! @page xtimer_testcase xtimer mode test
//!
//! File: @ref xtimertest2.c
//!
//! <h2>Description</h2>
//! This module implements the test sequence for the xtimer sub component.<br><br>
//! - \p Board: LM3S9B96 board <br><br>
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
//! - \subpage test_xtimer_mode
//! .
//! \file xtimertest2.c
//! \brief xtimer test source file
//! \brief xtimer test header file <br>
//
//*****************************************************************************

#include "test.h"
#include "xhw_types.h"
#include "xhw_ints.h"
#include "xhw_memmap.h"
#include "xhw_timer.h"
#include "xtimer.h"

//*****************************************************************************
//
//!\page test_xtimer_register test_xtimer_mode
//!
//!<h2>Description</h2>
//!Test xtimer mode. <br>
//!
//
//*****************************************************************************

//*****************************************************************************
//
// Define The 4 timer base address array, and Peripheral ID array.
//
//*****************************************************************************

//
// Timer base array
//
static unsigned long ulTimerBase[4] = {TIMER0_BASE, TIMER1_BASE,
                                       TIMER2_BASE, TIMER3_BASE};

//
// Timer ID array
//
static unsigned long ulTimerID[4] = {xSYSCTL_PERIPH_TIMER0,
                                     xSYSCTL_PERIPH_TIMER1,
                                     xSYSCTL_PERIPH_TIMER2,
                                     xSYSCTL_PERIPH_TIMER3};

//
// Timer interrupt ID
//
static unsigned long ulTimerAIntID[4] = {xINT_TIMER0, xINT_TIMER1, 
                                         xINT_TIMER2, xINT_TIMER3};
static unsigned long ulTimerBIntID[4] = {INT_TIMER0B, INT_TIMER1B,
                                         INT_TIMER2B, INT_TIMER3B};
//
// Global variable
//
//static unsigned long ulTimerIntFlag[4] = {0, 0, 0, 0};
static unsigned char ulCountA[4]={0};
static unsigned char ulCountB[4]={0};

//
// Install callback function
//
unsigned long Timer0ACallback(void *pvCBData,  unsigned long ulEvent,
                             unsigned long ulMsgParam, void *pvMsgData)
{
    //TestEmitToken('A');
    ulCountA[0] ++;
    return 0;
}
unsigned long Timer1ACallback(void *pvCBData,  unsigned long ulEvent,
                             unsigned long ulMsgParam, void *pvMsgData)
{
    //TestEmitToken('A');
    ulCountA[1] ++;
    return 0;
}
unsigned long Timer2ACallback(void *pvCBData,  unsigned long ulEvent,
                             unsigned long ulMsgParam, void *pvMsgData)
{
    TestEmitToken('A');
    ulCountA[2] ++;
    return 0;
}
unsigned long Timer3ACallback(void *pvCBData,  unsigned long ulEvent,
                             unsigned long ulMsgParam, void *pvMsgData)
{
    TestEmitToken('A');
    ulCountA[3] ++;
    return 0;
}

unsigned long Timer0BCallback(void *pvCBData,  unsigned long ulEvent,
                             unsigned long ulMsgParam, void *pvMsgData)
{
    //TestEmitToken('B');
    ulCountB[0] ++;
    return 0;
}
unsigned long Timer1BCallback(void *pvCBData,  unsigned long ulEvent,
                             unsigned long ulMsgParam, void *pvMsgData)
{
    //TestEmitToken('B');
    ulCountB[1] ++;
    return 0;
}
unsigned long Timer2BCallback(void *pvCBData,  unsigned long ulEvent,
                             unsigned long ulMsgParam, void *pvMsgData)
{
    //TestEmitToken('B');
    ulCountB[2] ++;
    return 0;
}
unsigned long Timer3BCallback(void *pvCBData,  unsigned long ulEvent,
                             unsigned long ulMsgParam, void *pvMsgData)
{
    //TestEmitToken('B');
    ulCountB[3] ++;
    return 0;
}

//
// Callback function
//
xtEventCallback TimerACallbackFunc[4] = {Timer0ACallback,Timer1ACallback,
                                         Timer2ACallback,Timer3ACallback};                                     
xtEventCallback TimerBCallbackFunc[4] = {Timer0BCallback,Timer1BCallback,
                                         Timer2BCallback,Timer3BCallback};


//*****************************************************************************
//
//! \brief Get the Test description of xtimer001 register test.
//!
//! \return the desccription of the xtimer001 test.
//
//*****************************************************************************
static char* xTimer002GetTest(void)
{
    return "xTimer [002]: xtimer mode test";
}

//*****************************************************************************
//
//! \brief something should do before the test execute of xtimer001 test.
//!
//! \return None.
//
//*****************************************************************************
static void xTimer002Setup(void)
{
        unsigned char i;
        //
    // Enable the tiemr0-3 peripheral
    //
    for(i = 0; i < 4; i++)
    { 
        xSysCtlPeripheralReset(ulTimerID[i]);
        xSysCtlPeripheralEnable(ulTimerID[i]);        
    }
}

//*****************************************************************************
//
//! \brief something should do after the test execute of xtimer001 test.
//!
//! \return None.
//
//*****************************************************************************
static void xTimer002TearDown(void)
{
    unsigned char i;
    //
    // Disable the tiemr0-3 peripheral
    //
    for(i = 0; i < 4; i++)
    {
        xSysCtlPeripheralDisable(ulTimerID[i]);  
    }
}

//*****************************************************************************
//
//! \brief xtimer 001 test execute main body.
//!
//! \return None.
//
//*****************************************************************************
static void xTimer002Execute(void)
{
    unsigned long ulTemp;
    unsigned long ulBase;
    unsigned char i, j ;
    
    //
    // 32 bit Timer one shot mode test
    //
    for(i = 0; i < 4; i++)
    {
        ulBase = ulTimerBase[i];
            
        TimerInitConfig(ulBase, TIMER_BOTH, TIMER_MODE_ONESHOT, 10);
                
        TimerIntEnable(ulBase, TIMER_BOTH, TIMER_INT_TIMEOUT);
        xIntEnable(ulTimerAIntID[i]);
        TimerIntCallbackInit(ulBase, TIMER_BOTH, TimerACallbackFunc[i]); 
        TimerStart(ulBase,TIMER_BOTH);
        while(ulCountA[i] < 1);
        //
        // wait until the timer data register reach equel to compare register
        //
        //TestAssertQBreak("B","One shot mode Intterrupt test fail", 1);
        xIntDisable(ulTimerAIntID[i]);
    }
        
    //
    // 32 bit RTC mode 
    //
    for(i = 0; i < 4; i++)
    {
        ulBase = ulTimerBase[i];
            
        TimerInitConfig(ulBase, TIMER_RTC, 0, 0);
                
        //
        // interrupt period is 10s 
        //
        TimerMatchSet(ulBase, TIMER_RTC, 10);            
                
        TimerIntEnable(ulBase, TIMER_RTC, 0);
        xIntEnable(ulTimerAIntID[i]);
        TimerIntCallbackInit(ulBase, TIMER_RTC, TimerACallbackFunc[i]); 
        ulCountA[i] = 0;
        TimerStart(ulBase, TIMER_RTC);
        while(ulCountA[i] < 2);            
        xIntDisable(ulTimerAIntID[i]);
    }

    //
    // 16 bit Timer B One shot mode test.
    //
    for(i = 0; i < 4; i++)
    {
        ulBase = ulTimerBase[i];
        
        //
        // Clear the flag first
        //
        TimerIntClear(ulBase, TIMER_B, TIMER_INT_TIMEOUT);
        
        // 
        // Config Timer B as One shot mode
        //        
        TimerInitConfig(ulBase, TIMER_B, TIMER_MODE_ONESHOT, 10);
        
        TimerIntEnable(ulBase, TIMER_B, TIMER_INT_TIMEOUT);
        xIntEnable(ulTimerBIntID[i]);
        TimerIntCallbackInit(ulBase, TIMER_B, TimerBCallbackFunc[i]); 
                ulCountB[i] = 0;
        TimerStart(ulBase,TIMER_B);
        while(ulCountB[i] < 1);
        //
        // wait until the timer data register reach equel to compare register
        //
        //TestAssertQBreak("B","One shot mode Intterrupt test fail", 1);
        xIntDisable(ulTimerBIntID[i]);
    }  
        
    //
    // 16-bit Timer A Periodic mode
    //
    for(i = 0; i < 4; i++)
    {
        ulBase = ulTimerBase[i];
        ulTemp = 0;
        
        //
        // Clear the flag first
        //
        TimerIntClear(ulBase, TIMER_A, TIMER_INT_TIMEOUT);
        
        //
        // Config as periodic mode
        //
        TimerInitConfig(ulBase, TIMER_A, TIMER_MODE_PERIODIC, 10); 
        TimerIntEnable(ulBase, TIMER_A, TIMER_INT_TIMEOUT);
        TimerStart(ulBase, TIMER_A);
        
        // 
        // wait the periodic repeat 5 times 
        //
        for (j = 0; j < 5; j++)
        {
            while(!TimerIntMaskStatus(ulBase, TIMER_A, TIMER_INT_TIMEOUT));      
            ulTemp++;
            if(ulTemp == 5)
            {
                break;
            }
            TimerIntClear(ulBase, TIMER_A, TIMER_INT_TIMEOUT);
        }
        TestAssert(ulTemp == 5,
                   "xtimer mode \" periodic test\" error!");
        TimerStop(ulBase, TIMER_A);       
    }
}

//
// xtimer register test case struct.
//
const tTestCase sTestxTimer002Mode = {
    xTimer002GetTest,
    xTimer002Setup,
    xTimer002TearDown,
    xTimer002Execute
};

//
// xtimer test suits.
//
const tTestCase * const psPatternXtimer002[] =
{
    &sTestxTimer002Mode,
    0
};

