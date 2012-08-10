//*****************************************************************************
//
//! \file xtimer.c
//! \brief Driver for the Timer
//! \version V2.1.1.1
//! \date 7/14/2012
//! \author CooCox
//! \copy
//!
//! Copyright (c)  2011, CooCox 
//! All rights reserved.
//! 
//! Redistribution and use in source and binary forms, with or without 
//! modification, are permitted provided that the following conditions 
//! are met: 
//! 
//!     * Redistributions of source code must retain the above copyright 
//! notice, this list of conditions and the following disclaimer. 
//!     * Redistributions in binary form must reproduce the above copyright
//! notice, this list of conditions and the following disclaimer in the
//! documentation and/or other materials provided with the distribution. 
//!     * Neither the name of the <ORGANIZATION> nor the names of its 
//! contributors may be used to endorse or promote products derived 
//! from this software without specific prior written permission. 
//! 
//! THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
//! AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
//! IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
//! ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE 
//! LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR 
//! CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF 
//! SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
//! INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN 
//! CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
//! ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF 
//! THE POSSIBILITY OF SUCH DAMAGE.
//
//*****************************************************************************

#include "xhw_types.h"
#include "xhw_ints.h"
#include "xhw_memmap.h"
#include "xhw_nvic.h"
#include "xhw_sysctl.h"
#include "xhw_timer.h"
#include "xdebug.h"
#include "xcore.h"
#include "xsysctl.h"
#include "xtimer.h"

//*****************************************************************************
//
// An array is Timer Callback function point
//
//*****************************************************************************
static xtEventCallback g_pfnTimerHandlerCallbacks[8]={0};



//*****************************************************************************
//
//! \brief The Timer 0 subtimer A default IRQ, declared in start up code. 
//!
//! \param None.
//!
//! This function is to give a default Timer IRQ service.
//!
//! \note None
//!
//! \return None.
//
//*****************************************************************************
void 
TIMER0AIntHandler(void)
{
    unsigned long ulBase = TIMER0_BASE;
    unsigned long ulTemp;
    //
    //! Clear the Timer INT Flag
    //
    ulTemp = xHWREG(ulBase + TIMER_0_GPTMMIS) & 0x0000001F;
    xHWREG(ulBase + TIMER_0_GPTMICR) = ulTemp;     

    if (g_pfnTimerHandlerCallbacks[0] != 0)        
    {
        g_pfnTimerHandlerCallbacks[0](0, 0, ulTemp, 0);
    }
}

//*****************************************************************************
//
//! \brief The Timer 0 subtimer B default IRQ, declared in start up code. 
//!
//! \param None.
//!
//! This function is to give a default Timer IRQ service.
//!
//! \note None
//!
//! \return None.
//
//*****************************************************************************
void 
TIMER0BIntHandler(void)
{
    unsigned long ulBase = TIMER0_BASE;
    unsigned long ulTemp;
    //
    //! Clear the Timer INT Flag
    //
    ulTemp = xHWREG(ulBase + TIMER_0_GPTMMIS) & 0x00000F00;
    xHWREG(ulBase + TIMER_0_GPTMICR) = ulTemp;     

    if (g_pfnTimerHandlerCallbacks[1] != 0)        
    {
        g_pfnTimerHandlerCallbacks[1](0, 0, ulTemp, 0);
    }
}

//*****************************************************************************
//
//! \brief The Timer 1 subtimer A default IRQ, declared in start up code. 
//!
//! \param None.
//!
//! This function is to give a default Timer IRQ service.
//!
//! \note None
//!
//! \return None.
//
//*****************************************************************************
void 
TIMER1AIntHandler(void)
{
    unsigned long ulBase = TIMER1_BASE;
    unsigned long ulTemp;
    //
    //! Clear the Timer INT Flag
    //
    ulTemp = xHWREG(ulBase + TIMER_0_GPTMMIS) & 0x0000001F;
    xHWREG(ulBase + TIMER_0_GPTMICR) = ulTemp;

    if (g_pfnTimerHandlerCallbacks[2] != 0)        
    {
        g_pfnTimerHandlerCallbacks[2](0, 0, ulTemp, 0);
    }
}

//*****************************************************************************
//
//! \brief The Timer 1 subtimer B default IRQ, declared in start up code. 
//!
//! \param None.
//!
//! This function is to give a default Timer IRQ service.
//!
//! \note None
//!
//! \return None.
//
//*****************************************************************************
void 
TIMER1BIntHandler(void)
{
    unsigned long ulBase = TIMER1_BASE;
    unsigned long ulTemp;
    //
    //! Clear the Timer INT Flag
    //
    ulTemp = xHWREG(ulBase + TIMER_0_GPTMMIS) & 0x00000F00;
    xHWREG(ulBase + TIMER_0_GPTMICR) = ulTemp;

    if (g_pfnTimerHandlerCallbacks[3] != 0)        
    {
        g_pfnTimerHandlerCallbacks[3](0, 0, ulTemp, 0);
    }
}

//*****************************************************************************
//
//! \brief The Timer 2 subtimer A default IRQ, declared in start up code. 
//!
//! \param None.
//!
//! This function is to give a default Timer IRQ service.
//!
//! \note None
//!
//! \return None.
//
//*****************************************************************************
void 
TIMER2AIntHandler(void)
{
    unsigned long ulBase = TIMER2_BASE;
    unsigned long ulTemp;
    //
    //! Clear the Timer INT Flag
    //
    ulTemp = xHWREG(ulBase + TIMER_0_GPTMMIS) & 0x0000001F;
    xHWREG(ulBase + TIMER_0_GPTMICR) = ulTemp;

    if (g_pfnTimerHandlerCallbacks[4] != 0)        
    {
        g_pfnTimerHandlerCallbacks[4](0, 0, ulTemp, 0);
    }
}

//*****************************************************************************
//
//! \brief The Timer 2 subtimer B default IRQ, declared in start up code. 
//!
//! \param None.
//!
//! This function is to give a default Timer IRQ service.
//!
//! \note None
//!
//! \return None.
//
//*****************************************************************************
void 
TIMER2BIntHandler(void)
{
    unsigned long ulBase = TIMER2_BASE;
    unsigned long ulTemp;
    //
    //! Clear the Timer INT Flag
    //
    ulTemp = xHWREG(ulBase + TIMER_0_GPTMMIS) & 0x00000F00;
    xHWREG(ulBase + TIMER_0_GPTMICR) = ulTemp;

    if (g_pfnTimerHandlerCallbacks[5] != 0)        
    {
        g_pfnTimerHandlerCallbacks[5](0, 0, ulTemp, 0);
    }
}

//*****************************************************************************
//
//! \brief The Timer 3 subtimer A default IRQ, declared in start up code. 
//!
//! \param None.
//!
//! This function is to give a default Timer IRQ service.
//!
//! \note None
//!
//! \return None.
//
//*****************************************************************************
void 
TIMER3AIntHandler(void)
{
    unsigned long ulBase = TIMER3_BASE;
    unsigned long ulTemp;
    //
    //! Clear the Timer INT Flag
    //
    ulTemp = xHWREG(ulBase + TIMER_0_GPTMMIS) & 0x0000001F;
    xHWREG(ulBase + TIMER_0_GPTMICR) = ulTemp;

    if (g_pfnTimerHandlerCallbacks[6] != 0)        
    {
        g_pfnTimerHandlerCallbacks[6](0, 0, ulTemp, 0);
    }
}

//*****************************************************************************
//
//! \brief The Timer 3 subtimer B default IRQ, declared in start up code. 
//!
//! \param None.
//!
//! This function is to give a default Timer IRQ service.
//!
//! \note None
//!
//! \return None.
//
//*****************************************************************************
void 
TIMER3BIntHandler(void)
{
    unsigned long ulBase = TIMER3_BASE;
    unsigned long ulTemp;
    //
    //! Clear the Timer INT Flag
    //
    ulTemp = xHWREG(ulBase + TIMER_0_GPTMMIS) & 0x00000F00;
    xHWREG(ulBase + TIMER_0_GPTMICR) = ulTemp;

    if (g_pfnTimerHandlerCallbacks[7] != 0)        
    {
        g_pfnTimerHandlerCallbacks[7](0, 0, ulTemp, 0);
    }
}

//*****************************************************************************
//
//! \internal
//! \brief The function is used to get timer clock.
//!
//! \param ulBase is the base address of the timer port.
//!
//! This function gets the timer clock
//! when set the tick frequency of timer.
//!
//! \return Returns the Current timer Clock.
//
//*****************************************************************************
static unsigned long
TimerClockGet(unsigned long ulBase)
{
    unsigned long ulFreq;
    ulFreq = SysCtlClockGet();
    return ulFreq;
}

//*****************************************************************************
//
//! \brief Configurate The Timer's mode and tick frequency. 
//!
//! \param ulBase is the base address of the Timer port.
//! \param ulConfig is the mode Configuratation of the Timer port.
//! \param ulTickFreq is the tick frequency of the Timer port.
//!
//! This function is to configurate The Timer's mode and tick frequency.
//!
//! The \e ulConfig parameter can be one of the values:
//! \b TIMER_MODE_ONESHOT, \b TIMER_MODE_PERIODIC, \b TIMER_MODE_TOGGLE and
//! \b TIMER_MODE_CAPTURE.
//!
//! The \e ulTickFreq parameter is the the timer tick frequency.It can be any
//! values but ulTickFreq > 0 and ulTickFreq < timer clock source.
//!
//! \note None
//!
//! \return None.
//
//*****************************************************************************
void 
TimerInitConfig(unsigned long ulBase, unsigned long ulChannel, 
                unsigned long ulConfig, unsigned long ulTickFreq)
{    
    unsigned long ulPreScale;
    unsigned long ulTCMPRValue;
    //
    // Check the arguments.
    //
    xASSERT((ulBase == TIMER3_BASE) || (ulBase == TIMER2_BASE) ||
            (ulBase == TIMER1_BASE) || (ulBase == TIMER0_BASE));
    
    xASSERT((ulChannel == TIMER_A) || (ulChannel == TIMER_B) ||
           (ulChannel == TIMER_BOTH) || (ulChannel == TIMER_RTC));
        
    xASSERT((ulConfig == TIMER_MODE_PERIODIC) ||
            (ulConfig == TIMER_MODE_ONESHOT)  ||
            (ulConfig == TIMER_MODE_PWM)      ||
            (ulConfig == TIMER_MODE_TOGGLE)   ||
            (ulConfig == TIMER_MODE_CAPTURE));

    xASSERT(ulTickFreq > 0);
        
    for (ulPreScale=1; ulPreScale<256; ulPreScale++)
    {
        ulTCMPRValue = TimerClockGet(ulBase) / (ulTickFreq * ulPreScale);

        /* The TCMPR value must > 1 */
        if ((ulTCMPRValue > 1) && (ulTCMPRValue < 0x10000))
            break;
    }
    switch(ulChannel)
    {
        case TIMER_A:
        {
            xHWREG(ulBase + TIMER_0_GPTMCTL) &= ~TIMER_GPTMCTL_TAEN;
            xHWREG(ulBase + TIMER_0_GPTMCFG) = 0x00000004;
            xHWREG(ulBase + TIMER_0_GPTMTAMR) = ulConfig & 0x000000FF;
            if((ulConfig == TIMER_MODE_PERIODIC) || 
               (ulConfig == TIMER_MODE_ONESHOT))
            {
                xHWREG(ulBase + TIMER_0_GPTMTAILR) = ulTCMPRValue;
                xHWREG(ulBase + TIMER_0_GPTMTAPR) = ulPreScale;
            }
            if(ulConfig == TIMER_MODE_PWM)
                xHWREG(ulBase + TIMER_0_GPTMTAILR) = TimerClockGet(ulBase) / ulTickFreq;
        }
        break;
        
        case TIMER_B:
        {
            xHWREG(ulBase + TIMER_0_GPTMCTL) &= ~TIMER_GPTMCTL_TBEN;
            xHWREG(ulBase + TIMER_0_GPTMCFG) = 0x00000004;
            xHWREG(ulBase + TIMER_0_GPTMTBMR) = ulConfig & 0x000000FF;
            if((ulConfig == TIMER_MODE_ONESHOT) || 
               (ulConfig == TIMER_MODE_PERIODIC))
            {
                xHWREG(ulBase + TIMER_0_GPTMTBILR) = ulTCMPRValue;
                xHWREG(ulBase + TIMER_0_GPTMTBPR) = ulPreScale;
            }
            if(ulConfig == TIMER_MODE_PWM)
                xHWREG(ulBase + TIMER_0_GPTMTBILR) = TimerClockGet(ulBase) / ulTickFreq;
        }            
        break;
                
        case TIMER_BOTH:
        {
            xHWREG(ulBase + TIMER_0_GPTMCTL) &= ~TIMER_GPTMCTL_TAEN;
            xHWREG(ulBase + TIMER_0_GPTMCFG) = 0x00000000;
            xHWREG(ulBase + TIMER_0_GPTMTAMR) = ulConfig & 0x000000FF;
            if((ulConfig == TIMER_MODE_ONESHOT) || 
               (ulConfig == TIMER_MODE_PERIODIC))
            {
                xHWREG(ulBase + TIMER_0_GPTMTAILR) = TimerClockGet(ulBase) / ulTickFreq;
            }
        }    
        break;                
        
        case TIMER_RTC:
        {
            xHWREG(ulBase + TIMER_0_GPTMCTL) &= ~TIMER_GPTMCTL_TAEN;
            xHWREG(ulBase + TIMER_0_GPTMCFG) = 0x00000001;
            break;
        }
    }
}

//*****************************************************************************
//
//! \brief Start The Timer counter. 
//!
//! \param ulBase is the base address of the Timer port.
//! \param ulChannel is the specifies the timer(s) to enable; must be one  
//!        of \b TIMER_A,\b TIMER_B, \b TIMER_BOTH or \b TIMER_RTC.
//!
//! This function is to start The Timer counter.
//!
//! \note None
//!
//! \return None.
//
//*****************************************************************************
void 
TimerStart(unsigned long ulBase, unsigned long ulChannel)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == TIMER3_BASE) || (ulBase == TIMER2_BASE) ||
            (ulBase == TIMER1_BASE) || (ulBase == TIMER0_BASE));
            
    xASSERT((ulChannel == TIMER_A) || (ulChannel == TIMER_B) ||
            (ulChannel == TIMER_BOTH) || (ulChannel == TIMER_RTC));

    //
    // Enable the timer(s) module.
    //
    if(ulChannel == TIMER_RTC)
	{
        xHWREG(ulBase + TIMER_0_GPTMCTL) |= (ulChannel & (TIMER_GPTMCTL_TAEN | 
                                                          TIMER_GPTMCTL_RTCEN));
    }
    else
    {
        xHWREG(ulBase + TIMER_0_GPTMCTL) &= ~TIMER_GPTMCTL_RTCEN;
        xHWREG(ulBase + TIMER_0_GPTMCTL) |= (ulChannel & (TIMER_GPTMCTL_TAEN | 
                                                          TIMER_GPTMCTL_TBEN));    
    }
}

//*****************************************************************************
//
//! \brief Stop The Timer counter. 
//!
//! \param ulBase is the base address of the Timer port.
//! \param ulChannel is the specifies the timer(s) to enable; must be one  
//!        of \b TIMER_A,\b TIMER_B, \b TIMER_BOTH or \b TIMER_RTC.
//!
//! This function is to stop The Timer counter.
//!
//! \note None
//!
//! \return None.
//
//*****************************************************************************
void 
TimerStop(unsigned long ulBase, unsigned long ulChannel)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == TIMER3_BASE) || (ulBase == TIMER2_BASE) ||
            (ulBase == TIMER1_BASE) || (ulBase == TIMER0_BASE));
            
    xASSERT((ulChannel == TIMER_A)     || (ulChannel == TIMER_B) ||
            (ulChannel == TIMER_BOTH) || (ulChannel == TIMER_RTC));

    //
    // Enable the timer(s) module.
    //
    if(ulChannel == TIMER_RTC)
	{
        xHWREG(ulBase + TIMER_0_GPTMCTL) &= ~(ulChannel & (TIMER_GPTMCTL_TAEN |                                                                                                 
                                                           TIMER_GPTMCTL_RTCEN));
    }
    else
    {    
        xHWREG(ulBase + TIMER_0_GPTMCTL) &= ~(ulChannel & (TIMER_GPTMCTL_TAEN | 
                                                           TIMER_GPTMCTL_TBEN));
    }
}

//*****************************************************************************
//
//! \brief Enable The Timer counter as a counter. 
//!
//! \param ulBase is the base address of the Timer port.
//!
//! This function is to enable The Timer counter as a counter.
//!
//! \note None
//!
//! \return None.
//
//*****************************************************************************
void 
TimerCounterEnable(unsigned long ulBase, unsigned long ulChannel)
{

}

//*****************************************************************************
//
//! \brief Disable The Timer counter as a counter. 
//!
//! \param ulBase is the base address of the Timer port.
//!
//! This function is to disable The Timer counter as a counter.
//!
//! \note None
//!
//! \return None.
//
//*****************************************************************************
void 
TimerCounterDisable(unsigned long ulBase, unsigned long ulChannel)
{
    
}

//*****************************************************************************
//
//! \brief Enable The Timer counter as a capture. 
//!
//! \param ulBase is the base address of the Timer port.
//! \param ulCapMode is the capture mode of the Timer port.Which can be the 
//! values: \b TIMER_CAP_COUNT, \b TIMER_CAP_TIME.
//!
//! This function is to enable The Timer counter as a capture.
//!
//! \note None
//!
//! \return None.
//
//*****************************************************************************
void 
TimerCaptureModeSet(unsigned long ulBase, unsigned long ulChannel, 
                    unsigned long ulCapMode)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == TIMER3_BASE) || (ulBase == TIMER2_BASE) ||
            (ulBase == TIMER1_BASE) || (ulBase == TIMER0_BASE));
    
    xASSERT((ulChannel == TIMER_A) || (ulChannel == TIMER_B));
    
    xASSERT((ulCapMode == TIMER_CAP_COUNT) ||
            (ulCapMode == TIMER_CAP_TIME)); 
    if(ulChannel & TIMER_A)    
    {            
        xHWREG(ulBase + TIMER_0_GPTMTAMR) &= ~TIMER_GPTMTAMR_TACMR_TMR;
        xHWREG(ulBase + TIMER_0_GPTMTAMR) |= ulCapMode;
    }
    if(ulChannel & TIMER_B)        
    {
        xHWREG(ulBase + TIMER_0_GPTMTBMR) &= ~TIMER_GPTMTBMR_TBCMR_TMR;
        xHWREG(ulBase + TIMER_0_GPTMTBMR) |= ulCapMode;
    }
}

//*****************************************************************************
//
//! \brief Set The Timer counter Prescale Value. 
//!
//! \param ulBase is the base address of the Timer port.
//! \param ulChannel is the specifies the timer(s) to enable; must be one  
//!        of \b TIMER_A,\b TIMER_B or \b TIMER_BOTH.
//! \param ulValue is the Prescale Value will be set.
//!
//! This function is to Set The Timer counter Prescale Value.
//!
//! \note None
//!
//! \return None.
//
//*****************************************************************************
void
TimerPrescaleSet(unsigned long ulBase, unsigned long ulChannel,
                 unsigned long ulValue)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == TIMER3_BASE) || (ulBase == TIMER2_BASE) ||
            (ulBase == TIMER1_BASE) || (ulBase == TIMER0_BASE));
            
    xASSERT((ulChannel == TIMER_A) || (ulChannel == TIMER_B) ||
            (ulChannel == TIMER_BOTH));
           
    xASSERT(ulValue < 256);

    //
    // Set the timer A prescaler if requested.
    //
    if(ulChannel & TIMER_A)
    {
        xHWREG(ulBase + TIMER_0_GPTMTAPR) = ulValue;
    }

    //
    // Set the timer B prescaler if requested.
    //
    if(ulChannel & TIMER_B)
    {
        xHWREG(ulBase + TIMER_0_GPTMTBPR) = ulValue;
    }
}

//*****************************************************************************
//
//! \brief Get The Timer counter Prescale Value. 
//!
//! \param ulBase is the base address of the Timer port.
//! \param ulChannel is the channel of the Timer port.
//!
//! This function is to Set The Timer counter Prescale Value.
//!
//! \note None
//!
//! \return None.
//
//*****************************************************************************
unsigned long 
TimerPrescaleGet(unsigned long ulBase, unsigned long ulChannel)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == TIMER3_BASE) || (ulBase == TIMER2_BASE) ||
            (ulBase == TIMER1_BASE) || (ulBase == TIMER0_BASE));
    
     xASSERT((ulChannel == TIMER_A) || (ulChannel == TIMER_B) ||
             (ulChannel == TIMER_BOTH));

    return((ulChannel == TIMER_A) ? xHWREG(ulBase + TIMER_0_GPTMTAPR) :
           xHWREG(ulBase + TIMER_0_GPTMTBPR));
}

//*****************************************************************************
//
//! \brief Set The Timer counter Value. 
//!
//! \param ulBase is the base address of the Timer port.
//! \param ulChannel is the channel of the Timer port.
//! \param ulValue is the Prescale Value will be set.
//!
//! This function is to Set The Timer counter Value.
//!
//! \return None.
//
//*****************************************************************************
void
TimerLoadSet(unsigned long ulBase, unsigned long ulChannel,
             unsigned long ulValue)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == TIMER3_BASE) || (ulBase == TIMER2_BASE) ||
            (ulBase == TIMER1_BASE) || (ulBase == TIMER0_BASE));
            
    xASSERT((ulChannel == TIMER_A) || (ulChannel == TIMER_B) ||
            (ulChannel == TIMER_BOTH));

    //
    // Set the timer A load value if requested.
    //
    if(ulChannel & TIMER_A)
    {
        xHWREG(ulBase + TIMER_0_GPTMTAILR) = ulValue;
    }

    //
    // Set the timer B load value if requested.
    //
    if(ulChannel & TIMER_B)
    {
        xHWREG(ulBase + TIMER_0_GPTMTBILR) = ulValue;
    }
}

//*****************************************************************************
//
//! \brief Get The Timer load Value. 
//!
//! \param ulBase is the base address of the Timer port.
//! \param ulChannel is the channel of the Timer port. must be one of 
//!        \b TIMER_A or \b TIMER_B.  Only \b TIMER_A should be used when the
//!        timer is configured for 32-bit operation.
//!
//! This function gets the currently programmed interval load value for the
//! specified timer.
//!
//! \return the load Value will be get.
//
//*****************************************************************************
unsigned long
TimerLoadGet(unsigned long ulBase, unsigned long ulChannel)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == TIMER3_BASE) || (ulBase == TIMER2_BASE) ||
            (ulBase == TIMER1_BASE) || (ulBase == TIMER0_BASE));
            
    xASSERT((ulChannel == TIMER_A) || (ulChannel == TIMER_B));

    //
    // Return the appropriate load value.
    //
    return((ulChannel == TIMER_A) ? xHWREG(ulBase + TIMER_0_GPTMTAILR) :
           xHWREG(ulBase + TIMER_0_GPTMTBILR));
}

//*****************************************************************************
//
//! \brief Get The Timer counter current up timer or up event counter value. 
//!
//! \param ulBase is the base address of the Timer port.
//! \param ulChannel is the channel of the Timer port, must be one of 
//! \b TIMER_A, \b TIMER_B, \b TIMER_BOTH or \b TIMER_RTC.  Only \b TIMER_A 
//! should be used when the timer is configured for 32-bit operation.
//!
//! This function is to get The Timer counter current up timer or up event
//! counter value.
//!
//! \return current up timer or up event counter value will be set.
//
//*****************************************************************************
unsigned long
TimerValueGet(unsigned long ulBase, unsigned long ulChannel)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == TIMER3_BASE) || (ulBase == TIMER2_BASE) ||
            (ulBase == TIMER1_BASE) || (ulBase == TIMER0_BASE));
            
    xASSERT((ulChannel == TIMER_A) || (ulChannel == TIMER_B) ||
            (ulChannel == TIMER_BOTH) || (ulChannel == TIMER_RTC));

    //
    // Return the appropriate timer value.
    //
    return((ulChannel & TIMER_A) ? xHWREG(ulBase + TIMER_0_GPTMTAR) :             
            xHWREG(ulBase + TIMER_0_GPTMTBR));
}

//*****************************************************************************
//
//! \brief Set The Timer counter Compare Match Value. 
//!
//! \param ulBase is the base address of the Timer port.
//! \param ulChannel is the channel of the Timer port. must be one of 
//! \b TIMER_A, \b TIMER_B, or \b TIMER_RTC.  Only \b TIMER_A should be 
//! used when the timer is configured for 32-bit RTC operation.
//! \param ulValue is Timer counter Compare Match Value.
//!
//! This function is to Set The Timer counter Compare Match Value.
//!
//! \return None.
//
//*****************************************************************************
void
TimerMatchSet(unsigned long ulBase, unsigned long ulChannel,
              unsigned long ulValue)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == TIMER3_BASE) || (ulBase == TIMER2_BASE) ||
            (ulBase == TIMER1_BASE) || (ulBase == TIMER0_BASE));
            
    xASSERT((ulChannel == TIMER_A) || (ulChannel == TIMER_B) ||
            (ulChannel == TIMER_BOTH) || (ulChannel == TIMER_RTC));

    //
    // Set the timer A match value if requested.
    //
    if(ulChannel & TIMER_A)
    {
        xHWREG(ulBase + TIMER_0_GPTMTAMATCHR) = ulValue;
    }

    //
    // Set the timer B match value if requested.
    //
    if(ulChannel & TIMER_B)
    {
        xHWREG(ulBase + TIMER_0_GPTMTBMATCHR) = ulValue;
    }
}

//*****************************************************************************
//
//! \brief Get The Timer counter Compare Match Value. 
//!
//! \param ulBase is the base address of the Timer port.
//! \param ulChannel is the channel of the Timer port. must be one of 
//! \b TIMER_A, \b TIMER_B, or \b TIMER_BOTH.  Only \b TIMER_A should be 
//! used when the timer is configured for 32-bit operation.
//!
//! This function is to get The Timer counter Compare Match Value.
//!
//! \note None
//!
//! \return the Prescale Value will be set.
//
//*****************************************************************************
unsigned long
TimerMatchGet(unsigned long ulBase, unsigned long ulChannel)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == TIMER3_BASE) || (ulBase == TIMER2_BASE) ||
            (ulBase == TIMER1_BASE) || (ulBase == TIMER0_BASE));
            
    xASSERT((ulChannel == TIMER_A) || (ulChannel == TIMER_B) ||
                        (ulChannel == TIMER_RTC));

    //
    // Return the appropriate match value.
    //
    return((ulChannel & TIMER_A) ? xHWREG(ulBase + TIMER_0_GPTMTAMATCHR) :             
            xHWREG(ulBase + TIMER_0_GPTMTBMATCHR));
}

//*****************************************************************************
//
//! \brief Init interrupts callback for the timer.
//!
//! \param ulBase is the base address of the Timer port.
//! \param xtPortCallback is callback for the timer.
//!
//! Init interrupts callback for the timer.
//!
//! \return None.
//
//*****************************************************************************
void 
TimerIntCallbackInit(unsigned long ulBase, unsigned long ulChannel, 
                                            xtEventCallback xtTimerCallback)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == TIMER3_BASE) || (ulBase == TIMER2_BASE) ||
            (ulBase == TIMER1_BASE) || (ulBase == TIMER0_BASE));
    
    xASSERT((ulChannel == TIMER_A) || (ulChannel == TIMER_B) ||
            (ulChannel == TIMER_BOTH));
    
    if (xtTimerCallback != 0)
    {
        switch(ulBase)
        {
            case TIMER0_BASE:
            {
                if(ulChannel & TIMER_A)
                    g_pfnTimerHandlerCallbacks[0] = xtTimerCallback;
                else
                    g_pfnTimerHandlerCallbacks[1] = xtTimerCallback;
                break;
            }
            case TIMER1_BASE:
            {
                if(ulChannel & TIMER_A)
                    g_pfnTimerHandlerCallbacks[2] = xtTimerCallback;
                else
                    g_pfnTimerHandlerCallbacks[3] = xtTimerCallback;
                break;
            }
            case TIMER2_BASE:
            {
                if(ulChannel & TIMER_A)
                    g_pfnTimerHandlerCallbacks[4] = xtTimerCallback;
                else
                    g_pfnTimerHandlerCallbacks[5] = xtTimerCallback;
                break;
            }
            case TIMER3_BASE:
            {
                if(ulChannel & TIMER_A)
                    g_pfnTimerHandlerCallbacks[6] = xtTimerCallback;
                else
                    g_pfnTimerHandlerCallbacks[7] = xtTimerCallback;
                break;
            }
        }
    }
}

//*****************************************************************************
//
//! \brief Enable The Timer counter interrupt. 
//!
//! \param ulBase is the base address of the Timer port.
//! \param ulChannel is the channel of the Timer port.
//! \param ulIntFlags is the interrupt type of the Timer port.
//!
//! This function is to enable The Timer counter interrupt.
//! 
//! The \e ulIntFlags parameter is the OR value of any of the following:
//! - \b TIMER_INT_TIMEMATCH      - Timer match interrupt
//! - \b TIMER_INT_CAP_EVENT      - Capture event interrupt
//! - \b TIMER_INT_CAP_MATCH      - Capture match interrupt
//! - \b TIMER_INT_TIMEOUT          - Timer timeout interrupt
//!
//! \return None.
//
//*****************************************************************************
void 
TimerIntEnable(unsigned long ulBase, unsigned long ulChannel, 
                                unsigned long ulIntFlags)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == TIMER3_BASE) || (ulBase == TIMER2_BASE) ||
            (ulBase == TIMER1_BASE) || (ulBase == TIMER0_BASE));

    xASSERT((ulChannel == TIMER_A) || (ulChannel == TIMER_B) ||
            (ulChannel == TIMER_BOTH) || (ulChannel == TIMER_RTC));
    
    xASSERT(((ulIntFlags & TIMER_INT_TIMEMATCH) == TIMER_INT_TIMEMATCH)     || 
                        ((ulIntFlags & TIMER_INT_CAP_EVENT) == TIMER_INT_CAP_EVENT)  || 
            ((ulIntFlags & TIMER_INT_CAP_MATCH) == TIMER_INT_CAP_MATCH)  ||
                        ((ulIntFlags & TIMER_INT_TIMEOUT)  == TIMER_INT_TIMEOUT));
    
    //
    // Enable the specified interrupts.
    //
    if(ulChannel == TIMER_RTC)
    {
        xHWREG(ulBase + TIMER_0_GPTMIMR) = TIMER_GPTMIMR_RTCIM;
    }
    else
    {
        if(ulChannel & TIMER_A)
        {
            if(ulIntFlags & TIMER_INT_TIMEMATCH)
            {
                xHWREG(ulBase + TIMER_0_GPTMIMR) |= TIMER_GPTMIMR_TAMIM;
                 ulIntFlags &= ~TIMER_INT_TIMEMATCH;
            }
            xHWREG(ulBase + TIMER_0_GPTMIMR) |= (ulIntFlags);
        }
        if(ulChannel == TIMER_B)
        {
            xHWREG(ulBase + TIMER_0_GPTMIMR) |= (ulIntFlags << 8);
        }
    }
}

//*****************************************************************************
//
//! \brief Disable The Timer counter interrupt. 
//!
//! \param ulBase is the base address of the Timer port.
//! \param ulChannel is the channel of the Timer port.
//! \param ulIntFlags is the interrupt type of the Timer port.
//!
//! This function is to enable The Timer counter interrupt.
//! 
//! The \e ulIntFlags parameter is the OR value of any of the following:
//! - \b TIMER_INT_TIMEMATCH      - Timer match interrupt
//! - \b TIMER_INT_CAP_EVENT      - Capture event interrupt
//! - \b TIMER_INT_CAP_MATCH      - Capture match interrupt
//! - \b TIMER_INT_TIMEOUT          - Timer timeout interrupt
//!
//! \return None.
//
//*****************************************************************************
void 
TimerIntDisable(unsigned long ulBase, unsigned long ulChannel, 
                                    unsigned long ulIntFlags)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == TIMER3_BASE) || (ulBase == TIMER2_BASE) ||
            (ulBase == TIMER1_BASE) || (ulBase == TIMER0_BASE));
        
    xASSERT((ulChannel == TIMER_A) || (ulChannel == TIMER_B) ||
            (ulChannel == TIMER_BOTH) || (ulChannel == TIMER_RTC));
    
    xASSERT(((ulIntFlags & TIMER_INT_TIMEMATCH) == TIMER_INT_TIMEMATCH)  || 
            ((ulIntFlags & TIMER_INT_CAP_EVENT) == TIMER_INT_CAP_EVENT)  || 
            ((ulIntFlags & TIMER_INT_CAP_MATCH) == TIMER_INT_CAP_MATCH)  ||
            ((ulIntFlags & TIMER_INT_TIMEOUT)  == TIMER_INT_TIMEOUT));
    
    //
    // Enable the specified interrupts.
    //
    if(ulChannel == TIMER_RTC)
    {
        xHWREG(ulBase + TIMER_0_GPTMIMR) &= ~TIMER_GPTMIMR_RTCIM;
    }
    else
    {
        if(ulChannel & TIMER_A)
        {
            if(ulIntFlags & TIMER_INT_TIMEMATCH)
            {
                xHWREG(ulBase + TIMER_0_GPTMIMR) &= ~TIMER_GPTMIMR_TAMIM;
                ulIntFlags &= ~TIMER_INT_TIMEMATCH;
            }
            xHWREG(ulBase + TIMER_0_GPTMIMR) &= ~(ulIntFlags);
        }
        if(ulChannel == TIMER_B)
        {
            xHWREG(ulBase + TIMER_0_GPTMIMR) &= ~(ulIntFlags << 8);
        }
    }
}

//*****************************************************************************
//
//! \brief Get The Timer counter interrupt Status. 
//!
//! \param ulBase is the base address of the Timer port.
//! \param ulChannel is the channel of the Timer port.
//! \param ulIntFlags is the interrupt type of the Timer port.
//!
//! This function is to get The Timer counter masked interrupt status.
//! 
//! The \e ulIntFlags parameter can be one of the values:
//! \b TIMER_INT_TIMEMATCH, \b TIMER_INT_CAP_EVENT,
//! \b TIMER_INT_CAP_MATCH,  \b TIMER_INT_TIMEOUT,
//!
//! \note When use this API ,the ulIntFlags parameter one of the interrupt event
//!
//! \return the Status of The Timer counter interrupt.
//
//*****************************************************************************
xtBoolean
TimerIntMaskStatus(unsigned long ulBase, unsigned long ulChannel, 
                                        unsigned long ulIntFlags)
{

    //
    // Check the arguments.
    //
    xASSERT((ulBase == TIMER3_BASE) || (ulBase == TIMER2_BASE) ||
            (ulBase == TIMER1_BASE) || (ulBase == TIMER0_BASE));
    
    xASSERT((ulChannel == TIMER_A)    || (ulChannel == TIMER_B) ||
            (ulChannel == TIMER_BOTH) || (ulChannel == TIMER_RTC));
    
    xASSERT((ulIntFlags == TIMER_INT_TIMEMATCH)  || 
            (ulIntFlags == TIMER_INT_CAP_EVENT)  || 
            (ulIntFlags == TIMER_INT_CAP_MATCH)  ||
            (ulIntFlags == TIMER_INT_TIMEOUT));
    
    //
    // Return the masked interrupt status as requested. 
    //  
    if(ulChannel == TIMER_RTC)
    {
        return ((xHWREG(ulBase + TIMER_0_GPTMMIS) & TIMER_GPTMMIS_RTCMIS) ? xtrue : xfalse);
    }
    if((ulChannel & TIMER_A) && (ulIntFlags == TIMER_INT_TIMEMATCH))
    {
        return ((xHWREG(ulBase + TIMER_0_GPTMMIS) & TIMER_GPTMMIS_TAMMIS) ? xtrue : xfalse);
    }
    else
    {
        if(ulChannel & TIMER_B)
        {
            ulIntFlags <<= 8;
        }       
        return ((xHWREG(ulBase + TIMER_0_GPTMMIS) & ulIntFlags) ? xtrue : xfalse);
    }
}

//*****************************************************************************
//
//! \brief Get The Timer counter interrupt Status. 
//!
//! \param ulBase is the base address of the Timer port.
//! \param ulChannel is the channel of the Timer port.
//! \param ulIntFlags is the interrupt type of the Timer port.
//!
//! This function is to get The Timer counter raw interrupt status.
//! 
//! The \e ulIntFlags parameter can be one of the values:
//! \b TIMER_INT_TIMEMATCH, \b TIMER_INT_CAP_EVENT,
//! \b TIMER_INT_CAP_MATCH,  \b TIMER_INT_TIMEOUT.
//!
//! \note When use this API ,the ulIntFlags parameter one of the interrupt event
//!
//! \return the Status of The Timer counter interrupt.
//
//*****************************************************************************
xtBoolean
TimerIntRawStatus(unsigned long ulBase, unsigned long ulChannel,
                                    unsigned long ulIntFlags)
{

    //
    // Check the arguments.
    //
    xASSERT((ulBase == TIMER3_BASE) || (ulBase == TIMER2_BASE) ||
            (ulBase == TIMER1_BASE) || (ulBase == TIMER0_BASE));
        
    xASSERT((ulChannel == TIMER_A)    || (ulChannel == TIMER_B) ||
            (ulChannel == TIMER_BOTH) || (ulChannel == TIMER_RTC));
    
    xASSERT((ulIntFlags == TIMER_INT_TIMEMATCH)  || 
            (ulIntFlags == TIMER_INT_CAP_EVENT)  || 
            (ulIntFlags == TIMER_INT_CAP_MATCH)  ||
            (ulIntFlags == TIMER_INT_TIMEOUT));
    
    //
    // Return the raw interrupt status as requested.
    //  
    if(ulChannel == TIMER_RTC)
    {
        return ((xHWREG(ulBase + TIMER_0_GPTMRIS) & TIMER_GPTMRIS_RTCRIS) ? xtrue : xfalse);
    }
    if((ulChannel & TIMER_A) && (ulIntFlags == TIMER_INT_TIMEMATCH))
    {
        return ((xHWREG(ulBase + TIMER_0_GPTMRIS) & TIMER_GPTMRIS_TAMRIS) ? xtrue : xfalse);
    }
    else
    {
        if(ulChannel & TIMER_B)
        {
                        ulIntFlags <<= 8;
        }						
        return ((xHWREG(ulBase + TIMER_0_GPTMRIS) & ulIntFlags) ? xtrue : xfalse);
    }
}

//*****************************************************************************
//
//! \brief Clear The Timer counter interrupt flag. 
//!
//! \param ulBase is the base address of the Timer port.
//! \param ulChannel is the channel of the Timer port.
//! \param ulIntFlags is the interrupt type of the Timer port.
//!
//! This function is to clear The Timer counter interrupt flag.
//! 
//! The \e ulIntFlags parameter can be one of the values:
//! \b TIMER_INT_TIMEMATCH, \b TIMER_INT_CAP_EVENT,
//! \b TIMER_INT_CAP_MATCH,  \b TIMER_INT_TIMEOUT.
//!
//! \note None
//!
//! \return None.
//
//*****************************************************************************
void 
TimerIntClear(unsigned long ulBase, unsigned long ulChannel, 
                            unsigned long ulIntFlags)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == TIMER3_BASE) || (ulBase == TIMER2_BASE) ||
            (ulBase == TIMER1_BASE) || (ulBase == TIMER0_BASE));
        
    xASSERT((ulChannel == TIMER_A)    || (ulChannel == TIMER_B) ||
            (ulChannel == TIMER_BOTH) || (ulChannel == TIMER_RTC));
    
    xASSERT((ulIntFlags == TIMER_INT_TIMEMATCH)     || 
            (ulIntFlags == TIMER_INT_CAP_EVENT)  || 
            (ulIntFlags == TIMER_INT_CAP_MATCH)  ||
            (ulIntFlags == TIMER_INT_TIMEOUT));
    
    if(ulChannel == TIMER_RTC)
    {
        xHWREG(ulBase + TIMER_0_GPTMICR) = TIMER_GPTMIMR_RTCIM;
    }
    else
    {
        if(ulChannel & TIMER_A)
        {
            if(ulIntFlags & TIMER_INT_TIMEMATCH)
            {
                xHWREG(ulBase + TIMER_0_GPTMICR) |= TIMER_GPTMICR_TAMCINT;
                ulIntFlags &= ~TIMER_INT_TIMEMATCH;
            }
            xHWREG(ulBase + TIMER_0_GPTMICR) |= (ulIntFlags);
        }
        if(ulChannel == TIMER_B)
        {
            xHWREG(ulBase + TIMER_0_GPTMICR) |= (ulIntFlags << 8);
        }
    }
}

//*****************************************************************************
//
//! \brief Select The Timer counter detect phase. 
//!
//! \param ulBase is the base address of the Timer port.
//! \param ulChannel is the channel of the Timer port. must be one of 
//! \b TIMER_A, \b TIMER_B, or \b TIMER_BOTH.  Only \b TIMER_A should be 
//! used when the timer is configured for 32-bit operation.
//! \param ulPhase is the counter detect phase of the Timer port.
//!
//! This function is to select The Timer counter detect phase.
//! 
//! The \e ulPhase parameter can be one of the values:
//! \b TIMER_COUNTER_RISING, \b TIMER_COUNTER_FALLING.
//!
//! \note None
//!
//! \return None.
//
//*****************************************************************************
void
TimerCounterDetectPhaseSelect(unsigned long ulBase, unsigned long ulChannel, 
                                                            unsigned long ulPhase)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == TIMER3_BASE) || (ulBase == TIMER2_BASE) ||
            (ulBase == TIMER1_BASE) || (ulBase == TIMER0_BASE));
    
    xASSERT((ulChannel == TIMER_A) || (ulChannel == TIMER_B) || 
            (ulChannel == TIMER_BOTH));
    
    xASSERT((ulPhase == TIMER_COUNTER_RISING) || 
            (ulPhase == TIMER_COUNTER_FALLING));

    if(ulChannel & TIMER_A)  
    {
        xHWREG(ulBase + TIMER_0_GPTMTAMR) &= ~TIMER_GPTMTAMR_TACDIR_UP;
        xHWREG(ulBase + TIMER_0_GPTMTAMR) |= ulPhase;
    }
    if(ulChannel & TIMER_B)  
    {
        xHWREG(ulBase + TIMER_0_GPTMTBMR) &= ~TIMER_GPTMTBMR_TBCDIR_UP;
        xHWREG(ulBase + TIMER_0_GPTMTBMR) |= ulPhase;
    }
}

//*****************************************************************************
//
//! \brief Select The Timer counter capture detect edge. 
//!
//! \param ulBase is the base address of the Timer port.
//! \param ulChannel is the channel of the Timer port. must be one of 
//! \b TIMER_A or \b TIMER_B.  
//! \param ulEdge is the capture detect edge of the Timer port.
//!
//! This function is to select The Timer counter capture detect edge.
//! 
//! The \e ulPhase parameter can be one of the values:
//! \b TIMER_CAP_NEGEDGE, \b TIMER_CAP_POSEDGE, \b TIMER_CAP_BOTH.
//!
//! \note None
//!
//! \return None.
//
//*****************************************************************************
void 
TimerCaptureEdgeSelect(unsigned long ulBase, unsigned long ulChannel,
                                             unsigned long ulEdge)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == TIMER3_BASE) || (ulBase == TIMER2_BASE) ||
            (ulBase == TIMER1_BASE) || (ulBase == TIMER0_BASE));
            
    xASSERT((ulChannel == TIMER_A) || (ulChannel == TIMER_B));

    xASSERT((ulEdge == TIMER_CAP_NEGEDGE) || (ulEdge == TIMER_CAP_BOTH) || 
            (ulEdge == TIMER_CAP_POSEDGE));

    if(ulChannel & TIMER_A)
    {
        xHWREG(ulBase + TIMER_0_GPTMCTL) &= ~TIMER_GPTMCTL_TAEVENT_M;
        xHWREG(ulBase + TIMER_0_GPTMCTL) |= ulEdge;
    }
    if(ulChannel & TIMER_B)
    {
        xHWREG(ulBase + TIMER_0_GPTMCTL) &= ~TIMER_GPTMCTL_TBEVENT_M;
        xHWREG(ulBase + TIMER_0_GPTMCTL) |= (ulEdge << 8);
    }   
}

//*****************************************************************************
//
//! Controls the output level.
//!
//! \param ulBase is the base address of the timer module.
//! \param ulChannel specifies the timer(s) to adjust; must be one of \b TIMER_A,
//! \b TIMER_B, or \b TIMER_BOTH.
//! \param bInvert specifies the output level.
//!
//! This function sets the PWM output level for the specified timer.  If the
//! \e bInvert parameter is \b true, then the timer's output will be made
//! active low; otherwise, it will be made active high.
//!
//! \return None.
//
//*****************************************************************************
void
TimerControlLevel(unsigned long ulBase, unsigned long ulChannel,
                  xtBoolean bInvert)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == TIMER3_BASE) || (ulBase == TIMER2_BASE) ||
            (ulBase == TIMER1_BASE) || (ulBase == TIMER0_BASE));
            
    xASSERT((ulChannel == TIMER_A) || (ulChannel == TIMER_B) ||
           (ulChannel == TIMER_BOTH));

    //
    // Set the output levels as requested.
    //
    ulChannel &= TIMER_GPTMCTL_TAPWML | TIMER_GPTMCTL_TBPWML;
    xHWREG(ulBase + TIMER_0_GPTMCTL) = (bInvert ?
                                   (xHWREG(ulBase + TIMER_0_GPTMCTL) | ulChannel) :
                                   (xHWREG(ulBase + TIMER_0_GPTMCTL) & ~(ulChannel)));
}

//*****************************************************************************
//
//! Enables or disables the trigger output.
//!
//! \param ulBase is the base address of the timer module.
//! \param ulChannel specifies the timer to adjust; must be one of \b TIMER_A,
//! \b TIMER_B, or \b TIMER_BOTH.
//! \param bEnable specifies the desired trigger state.
//!
//! This function controls the trigger output for the specified timer.  If the
//! \e bEnable parameter is \b true, then the timer's output trigger is
//! enabled; otherwise it is disabled.
//!
//! \return None.
//
//*****************************************************************************
void
TimerControlTrigger(unsigned long ulBase, unsigned long ulChannel,
                    xtBoolean bEnable)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == TIMER3_BASE) || (ulBase == TIMER2_BASE) ||
            (ulBase == TIMER1_BASE) || (ulBase == TIMER0_BASE));
            
    xASSERT((ulChannel == TIMER_A) || (ulChannel == TIMER_B) ||
           (ulChannel == TIMER_BOTH));

    //
    // Set the trigger output as requested.
    //
    ulChannel &= TIMER_GPTMCTL_TAOTE | TIMER_GPTMCTL_TBOTE;
    xHWREG(ulBase + TIMER_0_GPTMCTL) = (bEnable ?
                                   (xHWREG(ulBase + TIMER_0_GPTMCTL) | ulChannel) :
                                   (xHWREG(ulBase + TIMER_0_GPTMCTL) & ~(ulChannel)));
}

//*****************************************************************************
//
//! Controls the event type.
//!
//! \param ulBase is the base address of the timer module.
//! \param ulChannel specifies the timer(s) to be adjusted; must be one of
//! \b TIMER_A, \b TIMER_B, or \b TIMER_BOTH.
//! \param ulEvent specifies the type of event; must be one of
//! \b TIMER_EVENT_POS_EDGE, \b TIMER_EVENT_NEG_EDGE, or
//! \b TIMER_EVENT_BOTH_EDGES.
//!
//! This function sets the signal edge(s) that will trigger the timer when in
//! capture mode.
//!
//! \return None.
//
//*****************************************************************************
void
TimerControlEvent(unsigned long ulBase, unsigned long ulChannel,
                  unsigned long ulEvent)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == TIMER3_BASE) || (ulBase == TIMER2_BASE) ||
            (ulBase == TIMER1_BASE) || (ulBase == TIMER0_BASE));
    
    xASSERT((ulChannel == TIMER_A) || (ulChannel == TIMER_B) ||
           (ulChannel == TIMER_BOTH));

    //
    // Set the event type.
    //
    ulEvent &= ulChannel & (TIMER_GPTMCTL_TAEVENT_M | TIMER_GPTMCTL_TBEVENT_M);
    xHWREG(ulBase + TIMER_0_GPTMCTL) = ((xHWREG(ulBase + TIMER_0_GPTMCTL) &
                                        ~(TIMER_GPTMCTL_TAEVENT_M |
                                        TIMER_GPTMCTL_TBEVENT_M)) | ulEvent);
}

//*****************************************************************************
//
//! Controls the stall handling.
//!
//! \param ulBase is the base address of the timer module.
//! \param ulChannel specifies the timer(s) to be adjusted; must be one of
//! \b TIMER_A, \b TIMER_B, or \b TIMER_BOTH.
//! \param bStall specifies the response to a stall signal.
//!
//! This function controls the stall response for the specified timer.  If the
//! \e bStall parameter is \b true, then the timer will stop counting if the
//! processor enters debug mode; otherwise the timer will keep running while in
//! debug mode.
//!
//! \return None.
//
//*****************************************************************************
void
TimerControlStall(unsigned long ulBase, unsigned long ulChannel,
                  xtBoolean  bStall)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == TIMER3_BASE) || (ulBase == TIMER2_BASE) ||
            (ulBase == TIMER1_BASE) || (ulBase == TIMER0_BASE));
            
    xASSERT((ulChannel == TIMER_A) || (ulChannel == TIMER_B) ||
           (ulChannel == TIMER_BOTH));

    //
    // Set the stall mode.
    //
    ulChannel &= TIMER_GPTMCTL_TASTALL | TIMER_GPTMCTL_TBSTALL;
    xHWREG(ulBase + TIMER_0_GPTMCTL) = (bStall ?
                                   (xHWREG(ulBase + TIMER_0_GPTMCTL) | ulChannel) :
                                   (xHWREG(ulBase + TIMER_0_GPTMCTL) & ~(ulChannel)));
}

//*****************************************************************************
//
//! Controls the wait on trigger handling.
//!
//! \param ulBase is the base address of the timer module.
//! \param ulChannel specifies the timer(s) to be adjusted; must be one of
//! \b TIMER_A, \b TIMER_B, or \b TIMER_BOTH.
//! \param bWait specifies if the timer should wait for a trigger input.
//!
//! This function controls whether or not a timer waits for a trigger input to
//! start counting.  When enabled, the previous timer in the trigger chain must
//! count to its timeout in order for this timer to start counting.  Refer to
//! the part's data sheet for a description of the trigger chain.
//!
//! \note This functionality is not available on all parts.
//!
//! \return None.
//
//*****************************************************************************
void
TimerControlWaitOnTrigger(unsigned long ulBase, unsigned long ulChannel,
                          xtBoolean bWait)
{
    //
    // Check the arguments.
    //
    xASSERT((ulBase == TIMER3_BASE) || (ulBase == TIMER2_BASE) ||
            (ulBase == TIMER1_BASE) || (ulBase == TIMER0_BASE));
            
    xASSERT((ulChannel == TIMER_A) || (ulChannel == TIMER_B) ||
           (ulChannel == TIMER_BOTH));

    //
    // Set the wait on trigger mode for timer A.
    //
    if((ulChannel & TIMER_A) != 0)
    {
        if(bWait)
        {
            xHWREG(ulBase + TIMER_0_GPTMTAMR) |= TIMER_GPTMTAMR_TAWOT;
        }
        else
        {
            xHWREG(ulBase + TIMER_0_GPTMTAMR) &= ~(TIMER_GPTMTAMR_TAWOT);
        }
    }

    //
    // Set the wait on trigger mode for timer A.
    //
    if((ulChannel & TIMER_B) != 0)
    {
        if(bWait)
        {
            xHWREG(ulBase + TIMER_0_GPTMTBMR) |= TIMER_GPTMTBMR_TBWOT;
        }
        else
        {
            xHWREG(ulBase + TIMER_0_GPTMTBMR) &= ~(TIMER_GPTMTBMR_TBWOT);
        }
    }
}
