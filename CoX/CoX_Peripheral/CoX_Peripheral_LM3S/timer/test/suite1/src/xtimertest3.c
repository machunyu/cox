//*****************************************************************************
//
//! @page xtimer_testcase xtimer event counting and input capture function test
//!
//! File: @ref xtimertest3.c
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
//! - \subpage test_xtimer_EventCount_InputCapture_test
//! .
//! \file xtimertest3.c
//! \brief xtimer test source file
//! \brief xtimer test header file <br>
//
//*****************************************************************************

#include "test.h"
#include "xhw_timer.h"
#include "xtimer.h"

//*****************************************************************************
//
//!\page test_xtimer_EventCount_InputCapture_test test_xtimer_EventCount_InputCapture_test
//!
//!<h2>Description</h2>
//!Test xtimer event counting and input capture test. <br>
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
static unsigned long ulTimerAIntID[8] = {xINT_TIMER0, xINT_TIMER1, 
                                         xINT_TIMER2, xINT_TIMER3};

//
// Install callback function
//
static unsigned long Timer0ACallback(void *pvCBData,  unsigned long ulEvent,
                                    unsigned long ulMsgParam, void *pvMsgData)
{
     TestEmitToken('b');
     return 0;
}
static unsigned long Timer1ACallback(void *pvCBData,  unsigned long ulEvent,
                                    unsigned long ulMsgParam, void *pvMsgData)
{
     TestEmitToken('b'); 
     return 0;
}
static unsigned long Timer2ACallback(void *pvCBData,  unsigned long ulEvent,
                                    unsigned long ulMsgParam, void *pvMsgData)
{
     TestEmitToken('b');
     return 0;
}
static unsigned long Timer3ACallback(void *pvCBData,  unsigned long ulEvent,
                                    unsigned long ulMsgParam, void *pvMsgData)
{
     TestEmitToken('b'); 
     return 0;
}

//
// Callback function
//
static xtEventCallback TimerACallbackFunc[4] = {Timer0ACallback,
                                                Timer1ACallback,
                                                Timer2ACallback,
                                                Timer3ACallback};
//static xtEventCallback TimerBCallbackFunc[4] = {Timer0BCallback,
//                                                Timer1BCallback,
//                                                Timer2BCallback,
//                                                Timer3BCallback};

//*****************************************************************************
//
//! \breif This function is used to generate a falling edge, as the of
//! Timer counting source.
//!
//! \return
//
//*****************************************************************************
void EdgeGenerate(void)                                       
{
    unsigned char i;
    //
    // Set the  pin to high
    //
    xGPIOSPinWrite(PB7, 1);
    
    //
    // Add a small delay
    //
    for(i = 0; i < 10; i++);
    
    //
    // Set the  pin to low
    //
    xGPIOSPinWrite(PB7, 0);
    
    for(i = 0; i < 10; i++);
}

//*****************************************************************************
//
//! \brief gpio init ,Set the GPC12 as gpio output. 
//!
//! \return none
//!
//
//*****************************************************************************
void GPIOInit()
{
    //
    // PB2 used to output falling edge as the timer count source.
    //
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);//¿ªÆôGPIOBÊ±ÖÓ
    xGPIODirModeSet(GPIO_PORTB_BASE, GPIO_PIN_7, GPIO_DIR_MODE_OUT);
    xGPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_7, 1);
}

//*****************************************************************************
//
//! \brief Get the Test description of xtimer001 event counting and input capture test.
//!
//! \return the desccription of the xtimer001 test.
//
//*****************************************************************************
static char* xTimer003GetTest(void)
{
    return "xTimer [003]: xtimer count and capture mode test";
}

//*****************************************************************************
//
//! \brief something should do before the test execute of xtimer001 test.
//!
//! \return None.
//
//*****************************************************************************
static void xTimer003Setup(void)
{
    unsigned char i;
    
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
    //
    // Turn a pin to an GPIO Timer input or output pin.
    //
    xSPinTypeTimer(TIMCCP0, PD4);
    xSPinTypeTimer(TIMCCP1, PA6);
    
    GPIOInit();
    
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
static void xTimer003TearDown(void)
{
        unsigned char i;
    //
    // Enable the tiemr0-3 peripheral
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
static void xTimer003Execute(void)
{
    unsigned long ulBase;
    unsigned char i;
    
    //xtBoolean xbTimerIntStatus;
    
    //
    // Test the event count function test. You should connect the PB7 to the
    // corresponding TM pin as the count source.
    //   
        
    TimerIntClear(TIMER0_BASE, TIMER_B, TIMER_INT_CAP_MATCH);
        
    // 
    // Mode set test
    //
    TimerInitConfig(TIMER0_BASE, TIMER_B, TIMER_MODE_CAPTURE, 10);
    TimerCaptureModeSet(TIMER0_BASE, TIMER_B, TIMER_CAP_COUNT);
    TimerLoadSet(TIMER0_BASE,TIMER_B,10);
    TimerMatchSet(TIMER0_BASE, TIMER_B, 5);
        
    //
    // Select the falling event count phase
    //
    TimerCounterDetectPhaseSelect(TIMER0_BASE, TIMER_B, TIMER_COUNTER_RISING);
        
    TimerIntEnable(TIMER0_BASE, TIMER_B, TIMER_INT_CAP_MATCH);
        
    //
    // Enable event count mode
    //
    TimerStart(TIMER0_BASE, TIMER_B);
        
    while(!xTimerStatusGet(TIMER0_BASE, TIMER_B, TIMER_INT_CAP_MATCH))
    {
        EdgeGenerate();
    }
    TimerIntClear(TIMER0_BASE, TIMER_B, TIMER_INT_CAP_MATCH);
        
    TimerIntDisable(TIMER0_BASE, TIMER_B, TIMER_INT_CAP_MATCH);  
   
    //
    // Input capture time mode function test
    //    
    //for (i = 0; i< 4; i++)
    //{
        ulBase = ulTimerBase[0];
        i = 0;
        
        //
        // Clear the flag first
        //
        TimerIntClear(ulBase, TIMER_A, TIMER_INT_CAP_EVENT);
        while(xTimerStatusGet(ulBase, TIMER_A, TIMER_INT_CAP_EVENT));
        
        TimerInitConfig(ulBase, TIMER_A, TIMER_MODE_CAPTURE, 10);
        TimerCaptureModeSet(ulBase, TIMER_A, TIMER_CAP_TIME);
        //
        // Capture detect edge set both
        //
        xTimerCaptureEdgeSelect(ulBase, TIMER_A, TIMER_CAP_BOTH);
        TimerLoadSet(ulBase, TIMER_A, 0xFFFF);
                
        //
        // Enable the capture Int
        //
        xTimerIntEnable(ulBase, TIMER_A, TIMER_INT_CAP_EVENT);
        xIntEnable(ulTimerAIntID[i]);
        TimerIntCallbackInit(ulBase, TIMER_A, TimerACallbackFunc[i]); 
        
        //
        // Enable the capture mode, Start the timer.
        //
        xTimerStart(ulBase, TIMER_A);
        
        //
        // wait until the timer data register reach equel to compare register
        //
        //TestAssertQBreak("b","One shot mode Intterrupt test fail", 1);
        //xbTimerIntStatus = xTimerStatusGet(ulBase, TIMER_A, TIMER_INT_CAP_EVENT);
                
        TimerIntClear(ulBase, TIMER_A, TIMER_INT_CAP_EVENT);
        TimerIntDisable(ulBase, TIMER_A, TIMER_INT_CAP_EVENT);
        xIntDisable(ulTimerAIntID[i]);
    //}
        
    //
    // PWM mode test
    //    
    //for (i = 0; i< 4; i++)
    //{
        ulBase = ulTimerBase[0];
        
        // T = 1ms, duty cycle = 33%.
        TimerInitConfig(ulBase, TIMER_A, TIMER_MODE_PWM, 1000);
        TimerMatchSet(ulBase, TIMER_A, 2666);
        //
        // Enable the capture mode, Start the timer.
        //
        xTimerStart(ulBase, TIMER_A);            
    //}
}

//
// xtimer register test case struct.
//
const tTestCase sTestxTimer003Function = {
    xTimer003GetTest,
    xTimer003Setup,
    xTimer003TearDown,
    xTimer003Execute
};

//
// xtimer test suits.
//
const tTestCase * const psPatternXtimer003[] =
{
    &sTestxTimer003Function,
    0
};

