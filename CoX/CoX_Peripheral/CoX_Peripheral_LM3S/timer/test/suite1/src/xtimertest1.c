//*****************************************************************************
//
//! @page xtimer_testcase xtimer register test
//!
//! File: @ref xtimertest1.c
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
//! - \subpage test_xtimer_register
//! .
//! \file xtimertest1.c
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
//!\page test_xtimer_register test_xtimer_register
//!
//!<h2>Description</h2>
//!Test xtimer register. <br>
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
// Timer mode
//
static unsigned long ulTimerMode[4] = {TIMER_MODE_ONESHOT, TIMER_MODE_PERIODIC,
                                       TIMER_MODE_CAPTURE, TIMER_MODE_PWM};

//
// specifies the timer(s)
//
static unsigned long ulTimers[4]={TIMER_A, TIMER_B, TIMER_BOTH, TIMER_RTC};

//
// Capture mode set
//
static unsigned long ulCaptureMode[6] = {TIMER_CAP_COUNT,
                                         TIMER_CAP_TIME};

//
// Match  value set
//
static unsigned long ulCaptureValue[3] = {2, 100, 4095};

//
// Int stauts
//
static unsigned long ulIntStatus[3]={//TIMER_INT_TIMEMATCH,
                                     TIMER_INT_CAP_EVENT,
                                     TIMER_INT_CAP_MATCH,
                                     TIMER_INT_TIMEOUT};
//
// Count detecte phase
//
static unsigned long ulCountPhase[2] = {xTIMER_COUNTER_RISING,
                                        xTIMER_COUNTER_FALLING};

//
// Capture edge set
//
static unsigned long ulCaptureEdge[3] = {TIMER_CAP_POSEDGE,
                                         TIMER_CAP_NEGEDGE,
                                         xTIMER_CAP_BOTH};

//*****************************************************************************
//
//! \brief Get the Test description of xtimer001 register test.
//!
//! \return the desccription of the xtimer001 test.
//
//*****************************************************************************
static char* xTimer001GetTest(void)
{
    return "xTimer [001]: xtimer register read and write test";
}

//*****************************************************************************
//
//! \brief something should do before the test execute of xtimer001 test.
//!
//! \return None.
//
//*****************************************************************************
static void xTimer001Setup(void)
{
    unsigned char i;
    //
    // Enable the tiemr0-3 peripheral
    //
    for(i = 0; i < 4; i++)
    {          
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
static void xTimer001TearDown(void)
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
static void xTimer001Execute(void)
{
    unsigned long ulTemp;
    unsigned long ulBase;
    unsigned char i, j;
        
    //
    // Test the register write and read.
    //
    for(i = 0; i < 4; i++)
    {
        ulBase = ulTimerBase[i];
            
        // 
        // Mode init set register test
        //
        xTimerInitConfig(ulBase, TIMER_A, TIMER_MODE_PERIODIC, 100);
        ulTemp = xHWREG(ulBase + TIMER_0_GPTMTAMR) & TIMER_GPTMTAMR_TAMR_M;
        TestAssert((TIMER_MODE_PERIODIC & 0x00000003) == ulTemp,
                                     "xtiemr API \"TimerInitConfig\" error!");
        xTimerInitConfig(ulBase, TIMER_B, TIMER_MODE_CAPTURE, 100);
        ulTemp = xHWREG(ulBase + TIMER_0_GPTMTBMR) & TIMER_GPTMTBMR_TBMR_M;
        TestAssert((TIMER_MODE_CAPTURE & 0x00000003) == ulTemp,
                                     "xtiemr API \"TimerInitConfig\" error!");
      
        //
        // Timer A start register test
        //
        xTimerStart(ulBase, TIMER_A);
        ulTemp = xHWREG(ulBase + TIMER_0_GPTMCTL) & TIMER_GPTMCTL_TAEN;
        TestAssert(TIMER_GPTMCTL_TAEN == ulTemp,
                   "xtiemr API \"TimerAStart\" error!");  

        //
        // Timer B start register test
        //
        xTimerStart(ulBase, TIMER_B);
        ulTemp = xHWREG(ulBase + TIMER_0_GPTMCTL) & TIMER_GPTMCTL_TBEN;
        TestAssert(TIMER_GPTMCTL_TBEN == ulTemp,
                   "xtiemr API \"TimerBStart\" error!");  
  
        //
        // RTC start register test
        // 
        xTimerStart(ulBase, TIMER_RTC);
        ulTemp = xHWREG(ulBase + TIMER_0_GPTMCTL) & TIMER_GPTMCTL_RTCEN;
        TestAssert(TIMER_GPTMCTL_RTCEN == ulTemp ,
                   "xtiemr API \"TimerRTCStart\" error!");
        
        //
        // Captuer mode enable register test
        //
        for(j=0; j<3; j++)
        {
            xTimerCaptureModeSet(ulBase, TIMER_A, ulCaptureMode[j]);
            ulTemp = xHWREG(ulBase + TIMER_0_GPTMTAMR) & 0x0000000C;
            TestAssert((ulCaptureMode[j] & 0x0000000C) == ulTemp,
                         "xtiemr API \"TimerACaptureModeSet\" error!");  
        }
        for(j=3;j<6;j++)
        {
            xTimerCaptureModeSet(ulBase, TIMER_B, ulCaptureMode[j]);
            ulTemp = xHWREG(ulBase + TIMER_0_GPTMTBMR) & 0x0000000C;
            TestAssert(((ulCaptureMode[j] >> 8) & 0x0000000C) == ulTemp,
                         "xtiemr API \"TimerACaptureModeSet\" error!");
        }
                
        //
        // Timer prescale  set register test
        //      
        xTimerPrescaleSet(ulBase, TIMER_A,  250);
        ulTemp = xHWREG(ulBase + TIMER_0_GPTMTAPR);
        TestAssert(250 == ulTemp,"xtiemr API \"TimerAPrescaleSet\" error!");  
        xTimerPrescaleSet(ulBase, TIMER_B,  240);
        ulTemp = xHWREG(ulBase + TIMER_0_GPTMTBPR);
        TestAssert(240 == ulTemp,"xtiemr API \"TimerBPrescaleSet\" error!"); 
         
        //
        // Timer match set test
        //
        for(j = 0; j < 3; j++)
        {
            xTimerMatchSet(ulBase, TIMER_A, ulCaptureValue[j]);
            ulTemp = TimerMatchGet(ulBase,TIMER_A);
            TestAssert(ulCaptureValue[j] == ulTemp,
                       "xtiemr API \"TimerAMatchSet\" error!"); 
            xTimerMatchSet(ulBase, TIMER_B, ulCaptureValue[j]);
            ulTemp = TimerMatchGet(ulBase,TIMER_B);
            TestAssert(ulCaptureValue[j] == ulTemp,
                       "xtiemr API \"TimerAMatchSet\" error!");
        }
                
        //
        // Timer Int enable register test
        //
        for(j = 0; j < 3; j ++)
        {
            TimerIntEnable(ulBase, TIMER_B, ulIntStatus[j]);
            ulTemp = (xHWREG(ulBase + TIMER_0_GPTMIMR) >> 8) & ulIntStatus[j];
            TestAssert(ulIntStatus[j] == ulTemp,
                        "xtiemr API \"TimerIntEnable\" error!");       
        }
#if 0                    
        //
        // Int status clear register test
        //
        for(j = 0; j < 3; j ++)
        {
            TimerIntClear(ulBase, TIMER_B, ulIntStatus[j]);
            ulTemp = (xHWREG(ulBase + TIMER_0_GPTMMIS) >> 8) & ulIntStatus[j];
            TestAssert(0 == ulTemp, "xtiemr API \"TimerIntClear\" error!"); 			
        }
#endif                    
        //
        // Timer Int disable register test
        //
        for(j = 0; j < 3; j ++)
        {
            TimerIntDisable(ulBase, TIMER_B, ulIntStatus[j]);
            ulTemp =  (xHWREG(ulBase + TIMER_0_GPTMIMR) >> 8) & ulIntStatus[j];
            TestAssert(0x00000000 == ulTemp,
                             "xtiemr API \"TimerIntDisable\" error!");  
        }
                
#if 0                
        //
        // Counter detect phase register set
        //
        for(j=0; j<2; j++)
        {
            xTimerCounterDetectPhaseSelect(ulBase, TIMER_A, ulCountPhase[j]);
            ulTemp = xHWREG(ulBase + TIMER_0_GPTMTAMR) & ulCountPhase[j];
            TestAssert(ulCountPhase[j] == ulTemp,
                        "xtiemr API \"TimerCounterDetectPhaseSelect\" error!");
            xTimerCounterDetectPhaseSelect(ulBase, TIMER_B, ulCountPhase[j]);
            ulTemp = xHWREG(ulBase + TIMER_0_GPTMTBMR) & ulCountPhase[j];
            TestAssert(ulCountPhase[j] == ulTemp,
                        "xtiemr API \"TimerCounterDetectPhaseSelect\" error!");
        }
#endif            
        //
        // Capture edge register set
        //
        for(j = 0; j < 2; j++)
        {
            xTimerCaptureEdgeSelect(ulBase, TIMER_A,  ulCaptureEdge[j]);
            ulTemp = xHWREG(ulBase + TIMER_0_GPTMCTL) & TIMER_GPTMCTL_TAEVENT_M;
            TestAssert(ulCaptureEdge[j] == ulTemp,
                       "xtiemr API \"TimerACaptureEdgeSelect\" error!");     
            xTimerCaptureEdgeSelect(ulBase, TIMER_B,  ulCaptureEdge[j]);
            ulTemp = (xHWREG(ulBase + TIMER_0_GPTMCTL) & TIMER_GPTMCTL_TBEVENT_M) >> 8;
            TestAssert(ulCaptureEdge[j] == ulTemp,
                       "xtiemr API \"TimerBCaptureEdgeSelect\" error!"); 
        }       
         
        //
        // Timer stop register test
        //
        xTimerStop(ulBase, TIMER_A);
        ulTemp = xHWREG(ulBase + TIMER_0_GPTMCTL) & TIMER_GPTMCTL_TAEN;
        TestAssert(0x00000000 == ulTemp,
                   "xtiemr API \"TimerAStop\" error!");  
        xTimerStop(ulBase, TIMER_B);
        ulTemp = xHWREG(ulBase + TIMER_0_GPTMCTL) & TIMER_GPTMCTL_TBEN;
        TestAssert(0x00000000 == ulTemp,
                   "xtiemr API \"TimerBStop\" error!");
    }
}

//
// xtimer register test case struct.
//
const tTestCase sTestxTimer001Register = {
    xTimer001GetTest,
    xTimer001Setup,
    xTimer001TearDown,
    xTimer001Execute
};

//
// xtimer test suits.
//
const tTestCase * const psPatternXtimer001[] =
{
    &sTestxTimer001Register,
    0
};

