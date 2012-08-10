//*****************************************************************************
//
//! \file xhw_timer.h
//! \brief Macros and defines used when accessing the TIMER hardware.
//! \version V2.1.1.1
//! \date 7/14/2012
//! \author CooCox
//! \copy
//!
//! Copyright (c)  2012, CooCox 
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
//****************************************************************************
#ifndef __XHW_TIMER_H__
#define __XHW_TIMER_H__

//*****************************************************************************
//
//! \addtogroup CoX_Peripheral_Lib
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup TIMER
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup Stellaris_TIMER_Register 
//! \brief Here are the detailed info of TIMER registers. 
//!
//! it contains:
//! - Register offset.
//! - detailed bit-field of the registers.
//! - Enum and mask of the registers.
//! .
//! Users can read or write the registers through xHWREG().
//!
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup Stellaris_TIMER_Register_Map TIMER Register Map(Address)
//! \brief Here is the TIMER register offset, users can get the register address
//! through <b>TIMER_BASE + offset</b>.
//! @{
//
//*****************************************************************************

//
//! GPTM Configuration Register (GPTMCFG)
//
#define TIMER_0_GPTMCFG					0x00000000

//
//! GPTM Timer A Mode Register (GPTMTAMR)
//
#define TIMER_0_GPTMTAMR				0x00000004

//
//! GPTM Timer B Mode Register (GPTMTBMR)
//
#define TIMER_0_GPTMTBMR				0x00000008

//
//! GPTM Control Register (GPTMCTL)
//
#define TIMER_0_GPTMCTL					0x0000000C

//
//! GPTM Interrupt Mask Register (GPTMIMR)
//
#define TIMER_0_GPTMIMR					0x00000018

//
//! GPTM Raw Interrupt Status Register (GPTMRIS)
//
#define TIMER_0_GPTMRIS					0x0000001C

//
//! GPTM Masked Interrupt Status Register (GPTMMIS)
//
#define TIMER_0_GPTMMIS					0x00000020


//
//! GPTM Interrupt Clear Register (GPTMICR)
//
#define TIMER_0_GPTMICR					0x00000024


//
//! GPTM Timer A Interval Load Register (GPTMTAILR)
//
#define TIMER_0_GPTMTAILR				0x00000028

//
//! GPTM Timer B Interval Load Register (GPTMTBILR)
//
#define TIMER_0_GPTMTBILR				0x0000002C

//
//! GPTM Timer A Match Register (GPTMTAMATCHR)
//
#define TIMER_0_GPTMTAMATCHR		0x00000030

//
//! GPTM Timer B Match Register (GPTMTBMATCHR)
//
#define TIMER_0_GPTMTBMATCHR		0x00000034

//
//! GPTM Timer A Prescale Register (GPTMTAPR)
//
#define TIMER_0_GPTMTAPR				0x00000038

//
//! GPTM Timer B Prescale Register (GPTMTBPR)
//
#define TIMER_0_GPTMTBPR				0x0000003C

//
//! GPTM Timer A Prescale Match Register (GPTMTAPMR)
//
#define TIMER_0_GPTMTAPMR				0x00000040

//
//! GPTM Timer B Prescale Match Register (GPTMTBPMR)
//
#define TIMER_0_GPTMTBPMR				0x00000044

//
//! GPTM Timer A Register (GPTMTAR)
//
#define TIMER_0_GPTMTAR					0x00000048

//
//! GPTM Timer B Register (GPTMTBR)
//
#define TIMER_0_GPTMTBR					0x0000004C

//
//! GPTM Timer A Value Register (GPTMTAV)
//
#define TIMER_0_GPTMTAV					0x00000050

//
//! GPTM Timer B Value Register (GPTMTBV)
//
#define TIMER_0_GPTMTBV					0x00000054

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup Stellaris_Register_TIMER_0_GPTMCFG TIMER_0_GPTMCFG
//! @{
//
//*****************************************************************************

//
//! GPTM Configuration mask
//
#define TIMER_GPTMCFG_CFG_M     0x00000007
//
//! 32-bit timer configuration
//
#define TIMER_GPTMCFG_CFG_32BIT	0x00000000

//
//! 32-bit real-time clock(RTC) counter configuration
//
#define TIMER_GPTMCFG_CFG_RTC		0x00000001

//
//! 16-bit timer configuration. The function is controlled by bit 1:0 
//!		of GPTMTAMP and GPTMTBMR
//
#define TIMER_GPTMCFG_CFG_16BIT	0x00000004

//
//! GPTM Configuration shift
//
#define TIMER_GPTMCFG_CFG_S     0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup Stellaris_Register_TIMER_0_GPTMTAMP TIMER_0_GPTMTAMP
//! @{
//
//*****************************************************************************

//
//! GPTM Timer A Snap-Shot Mode
//
#define TIMER_GPTMTAMR_TASNAPS	0x00000080

//
//! GPTM Timer A Wait-on-Trigger 
//
#define TIMER_GPTMTAMR_TAWOT		0x00000040

//
//! GPTM Timer A Match Interrupt Enable
//
#define TIMER_GPTMTAMR_TAMIE		0x00000020

//
//! GPTM Timer A Count Upward Direction, The timer starts from a value of 0x0
//!  in one-shot or periodic mode.
//
#define TIMER_GPTMTAMR_TACDIR_UP \
																0x00000010

//
//! GPTM Timer A Count Downward Direction
//
#define TIMER_GPTMTAMR_TACDIR_DOWN \
																0x00000000
								
//
//! GPTM Timer A Alternate PWM Mode 
//
#define TIMER_GPTMTAMR_TAAMS_PWM  \
																0x00000008

//
//! GPTM Timer A Alternate Capture Mode 
//
#define TIMER_GPTMTAMR_TAAMS_CAP \
																0x00000000

//
//! GPTM Timer A Capture Edge-Time Mode 
//
#define TIMER_GPTMTAMR_TACMR_TMR \
																0x00000004	

//
//! GPTM Timer A Capture Edge-Count Mode 
//								
#define TIMER_GPTMTAMR_TACMR_CNT \
																0x00000000

//
//! GPTM Timer A Mode mask
//
#define TIMER_GPTMTAMR_TAMR_M  	0x00000003

//
//! GPTM Timer A is operating at the one-shot mode.
//
#define TIMER_GPTMTAMR_TAMR_ONESHOT \
																0x00000001

//
//! GPTM Timer A is operating at the one-shot mode.
//
#define TIMER_GPTMTAMR_TAMR_PERIODIC \
																0x00000002

//
//! GPTM Timer A is operating at the one-shot mode.
//
#define TIMER_GPTMTAMR_TAMR_CAPTURE \
																0x00000003
								
//
//! GPTM Timer A  Mode shift
//
#define TIMER_GPTMTAMR_TAMR_S   0 

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup Stellaris_Register_TIMER_0_GPTMTBMR TIMER_0_GPTMTBMR
//! @{
//
//*****************************************************************************

//
//! GPTM Timer B Snap-Shot Mode
//
#define TIMER_GPTMTBMR_TBSNAPS  0x00000080

//
//! GPTM Timer B Wait-on-Trigger 
//
#define TIMER_GPTMTBMR_TBWOT		0x00000040

//
//! GPTM Timer B Match Interrupt Enable
//
#define TIMER_GPTMTBMR_TBMIE		0x00000020

//
//! GPTM Timer B Count Upward Direction, The timer starts from a value of 0x0
//!  in one-shot or periodic mode.
//
#define TIMER_GPTMTBMR_TBCDIR_UP \
																0x00000010

//
//! GPTM Timer B Count Downward Direction
//
#define TIMER_GPTMTBMR_TBCDIR_DOWN \
																0x00000000
								
//
//! GPTM Timer B Alternate PWM Mode 
//
#define TIMER_GPTMTBMR_TBAMS_PWM \
																0x00000008

//
//! GPTM Timer B Alternate Capture Mode 
//
#define TIMER_GPTMTBMR_TBAMS_CAP \
																0x00000000

//
//! GPTM Timer B Capture Edge-Time Mode 
//
#define TIMER_GPTMTBMR_TBCMR_TMR \
																0x00000004	

//
//! GPTM Timer B Capture Edge-Count Mode 
//								
#define TIMER_GPTMTBMR_TBCMR_CNT \
																0x00000000

//
//! GPTM Timer B Mode mask
//
#define TIMER_GPTMTBMR_TBMR_M   0x00000003

//
//! GPTM Timer B is operating at the one-shot mode.
//
#define TIMER_GPTMTBMR_TBMR_ONESHOT \
																0x00000001

//
//! GPTM Timer B is operating at the one-shot mode.
//
#define TIMER_GPTMTBMR_TBMR_PERIODIC \
																0x00000002

//
//! GPTM Timer B is operating at the one-shot mode.
//
#define TIMER_GPTMTBMR_TBMR_CAPTURE \
																0x00000003
								
//
//! GPTM Timer B  Mode shift
//
#define TIMER_GPTMTBMR_TBMR_S   0 

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup Stellaris_Register_TIMER_0_GPTMCTL TIMER_0_GPTMCTL
//! @{
//
//*****************************************************************************

//
//! GPTM Timer B PWM output level is inverted
//
#define TIMER_GPTMCTL_TBPWML		0x00004000

//
//! GPTM Timer B Output Trigger Enable
//
#define TIMER_GPTMCTL_TBOTE			0x00002000

//
//! GPTM Timer B Event Mode Mask
//
#define TIMER_GPTMCTL_TBEVENT_M	0x00000C00

//
//! GPTM Timer B Event Mode is Positive edge
//
#define TIMER_GPTMCTL_TBEVENT_POSITIVE_EDGE	\
																0x00000000
								
//
//! GPTM Timer B Event Mode is Negative edge
//
#define TIMER_GPTMCTL_TBEVENT_NEGATIVE_EDGE	\
																0x00000400
								
//
//! GPTM Timer B Event Mode is BOTH edge
//
#define TIMER_GPTMCTL_TBEVENT_BOTH_EDGE	\
																0x00000C00

//
//! GPTM Timer B Event Mode shift
//
#define TIMER_GPTMCTL_TBEVENT_S	10

//
//! GPTM Timer B Stall Enable
//
#define TIMER_GPTMCTL_TBSTALL		0x00000200

//
//! GPTM Timer B Enable
//
#define TIMER_GPTMCTL_TBEN			0x00000100

//
//! GPTM Timer A PWM output level is inverted
//
#define TIMER_GPTMCTL_TAPWML		0x00000040

//
//! GPTM Timer A ADC Trigger Enable
//
#define TIMER_GPTMCTL_TAOTE			0x00000020

//
//! GPTM RTC counting Enable
//
#define TIMER_GPTMCTL_RTCEN			0x00000010

//
//! GPTM Timer A Event Mode Mask
//
#define TIMER_GPTMCTL_TAEVENT_M	0x0000000C

//
//! GPTM Timer A Event Mode is Positive edge
//
#define TIMER_GPTMCTL_TAEVENT_POSITIVE_EDGE	\
																0x00000000
								
//
//! GPTM Timer A Event Mode is Negative edge
//
#define TIMER_GPTMCTL_TAEVENT_NEGATIVE_EDGE	\
																0x00000004
								
//
//! GPTM Timer A Event Mode is BOTH edge
//
#define TIMER_GPTMCTL_TAEVENT_BOTH_EDGE	 \
																0x0000000C

//
//! GPTM Timer A Event Mode shift
//
#define TIMER_GPTMCTL_TAEVENT_S	2

//
//! GPTM Timer A Stall Enable
//
#define TIMER_GPTMCTL_TASTALL		0x00000002

//
//! GPTM Timer A Enable
//
#define TIMER_GPTMCTL_TAEN			0x00000001

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup Stellaris_Register_TIMER_0_GPTMIMR TIMER_0_GPTMIMR
//! @{
//
//*****************************************************************************

//
//! GPTM Timer B Mode Match Interrupt Mask Enable
//
#define TIMER_GPTMIMR_TBMIM			0x00000800

//
//! GPTM Capture B EVENT Interrupt Mask Enable
//
#define TIMER_GPTMIMR_CBEIM			0x00000400

//
//! GPTM Capture B MATCH Interrupt Mask Enable
//
#define TIMER_GPTMIMR_CBMIM			0x00000200

//
//! GPTM Timer B Timer-Out Interrupt Mask Enable
//
#define TIMER_GPTMIMR_TBTOIM		0x00000100

//
//! GPTM Timer A Mode Match Interrupt Mask Enable
//
#define TIMER_GPTMIMR_TAMIM			0x00000010

//
//! GPTM RTC Interrupt Mask Enable
//
#define TIMER_GPTMIMR_RTCIM			0x00000008

//
//! GPTM Capture A EVENT Interrupt Mask Enable
//
#define TIMER_GPTMIMR_CAEIM			0x00000004

//
//! GPTM Capture A MATCH Interrupt Mask Enable
//
#define TIMER_GPTMIMR_CAMIM			0x00000002

//
//! GPTM Timer A Timer-Out Interrupt Mask Enable
//
#define TIMER_GPTMIMR_TATOIM		0x00000001

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup Stellaris_Register_TIMER_0_GPTMRIS TIMER_0_GPTMRIS
//! @{
//
//*****************************************************************************

//
//! GPTM Timer B Mode Match Raw Interrupt
//
#define TIMER_GPTMRIS_TBMRIS		0x00000800

//
//! GPTM Capture B Event Raw Interrupt 
//
#define TIMER_GPTMRIS_CBERIS		0x00000400

//
//! GPTM Capture B Match Raw Interrupt
//
#define TIMER_GPTMRIS_CBMRIS		0x00000200

//
//! GPTM Timer B Time-Out Raw Interrupt
//
#define TIMER_GPTMRIS_TBTORIS		0x00000100

//
//! GPTM Timer A Mode Match Raw Interrupt
//
#define TIMER_GPTMRIS_TAMRIS		0x00000010

//
//! GPTM RTC Raw Interrupt 
//
#define TIMER_GPTMRIS_RTCRIS		0x00000008

//
//! GPTM Capture A Event Raw Interrupt 
//
#define TIMER_GPTMRIS_CAERIS		0x00000004

//
//! GPTM Capture A Match Raw Interrupt
//
#define TIMER_GPTMRIS_CAMRIS		0x00000002

//
//! GPTM Timer A Time-Out Raw Interrupt
//
#define TIMER_GPTMRIS_TATORIS		0x00000001

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup Stellaris_Register_TIMER_0_GPTMMIS TIMER_0_GPTMMIS
//! @{
//
//*****************************************************************************

//
//! GPTM Timer B Mode Match Masked Interrupt
//
#define TIMER_GPTMMIS_TBMMIS		0x00000800

//
//! GPTM Capture B Event Masked Interrupt 
//
#define TIMER_GPTMMIS_CBEMIS		0x00000400

//
//! GPTM Capture B Match Masked Interrupt
//
#define TIMER_GPTMMIS_CBMMIS		0x00000200

//
//! GPTM Timer B Time-Out Masked Interrupt
//
#define TIMER_GPTMMIS_TBTOMIS		0x00000100

//
//! GPTM Timer A Mode Match Masked Interrupt
//
#define TIMER_GPTMMIS_TAMMIS		0x00000010

//
//! GPTM RTC Masked Interrupt 
//
#define TIMER_GPTMMIS_RTCMIS		0x00000008

//
//! GPTM Capture A Event Masked Interrupt 
//
#define TIMER_GPTMMIS_CAEMIS		0x00000004

//
//! GPTM Capture A Match Masked Interrupt
//
#define TIMER_GPTMMIS_CAMMIS		0x00000002

//
//! GPTM Timer A Time-Out Masked Interrupt
//
#define TIMER_GPTMMIS_TATOMIS		0x00000001

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup Stellaris_Register_TIMER_0_GPTMICR TIMER_0_GPTMICR
//! @{
//
//*****************************************************************************

//
//! GPTM Timer B Mode Match Interrupt Clear
//
#define TIMER_GPTMICR_TBMCINT		0x00000800

//
//! GPTM Capture B Event Interrupt Clear
//
#define TIMER_GPTMICR_CBECINT		0x00000400

//
//! GPTM Capture B Match Interrupt Clear
//
#define TIMER_GPTMICR_CBMCINT		0x00000200

//
//! GPTM Timer B Time-Out Interrupt Clear
//
#define TIMER_GPTMICR_TBTOCINT	0x00000100

//
//! GPTM Timer A Mode Match Interrupt Clear
//
#define TIMER_GPTMICR_TAMCINT		0x00000010

//
//! GPTM RTC Interrupt Clear
//
#define TIMER_GPTMICR_RTCCINT		0x00000008

//
//! GPTM Capture A Event Interrupt Clear
//
#define TIMER_GPTMICR_CAECINT		0x00000004

//
//! GPTM Capture A Match Interrupt Clear
//
#define TIMER_GPTMICR_CAMCINT		0x00000002

//
//! GPTM Timer A Time-Out Interrupt Clear
//
#define TIMER_GPTMICR_TATOCINT	0x00000001

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup Stellaris_Register_TIMER_0_GPTMTAILR TIMER_0_GPTMTAILR
//! @{
//
//*****************************************************************************

//
//! GPTM Timer A Interval Load Register Value mask
//
#define TIMER_GPTMTAILR_M       0xFFFFFFFF

//
//! GPTM Timer A Interval Load Register Value shift
//
#define TIMER_GPTMTAILR_S       0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup Stellaris_Register_TIMER_0_GPTMTBILR TIMER_0_GPTMTBILR
//! @{
//
//*****************************************************************************

//
//! GPTM Timer B Interval Load Register Value mask
//
#define TIMER_GPTMTBILR_M       0xFFFFFFFF

//
//! GPTM Timer B Interval Load Register Value shift
//
#define TIMER_GPTMTBILR_S       0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup Stellaris_Register_TIMER_0_GPTMTAMATCHR TIMER_0_GPTMTAMATCHR
//! @{
//
//*****************************************************************************

//
//! GPTM Timer A Match Register Value mask
//
#define TIMER_GPTMTAMATCHR_M    0xFFFFFFFF

//
//! GPTM Timer A Match Register Value shift
//
#define TIMER_GPTMTAMATCHR_S    0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup Stellaris_Register_TIMER_0_GPTMTBMATCHR TIMER_0_GPTMTBMATCHR
//! @{
//
//*****************************************************************************

//
//! GPTM Timer B Match Register Value mask
//
#define TIMER_GPTMTBMATCHR_M    0xFFFFFFFF

//
//! GPTM Timer B Match Register Value shift
//
#define TIMER_GPTMTBMATCHR_S    0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup Stellaris_Register_TIMER_0_GPTMTAPR TIMER_0_GPTMTAPR
//! @{
//
//*****************************************************************************

//
//! GPTM Timer A Prescale Register Value mask
//
#define TIMER_GPTMTAPR_M    		0x000000FF

//
//! GPTM Timer A Prescale Register Value shift
//
#define TIMER_GPTMTAPR_S    		0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup Stellaris_Register_TIMER_0_GPTMTBPR TIMER_0_GPTMTBPR
//! @{
//
//*****************************************************************************

//
//! GPTM Timer B Prescale Register Value mask
//
#define TIMER_GPTMTBPR_M    		0x000000FF

//
//! GPTM Timer B Prescale Register Value shift
//
#define TIMER_GPTMTBPR_S    		0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup Stellaris_Register_TIMER_0_GPTMTAPMR TIMER_0_GPTMTAPMR
//! @{
//
//*****************************************************************************

//
//! GPTM Timer A Prescale Match Register Value mask
//
#define TIMER_GPTMTAPMR_M    		0x000000FF

//
//! GPTM Timer A Prescale MatchRegister Value shift
//
#define TIMER_GPTMTAPMR_S    		0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup Stellaris_Register_TIMER_0_GPTMTBPMR TIMER_0_GPTMTBPMR
//! @{
//
//*****************************************************************************

//
//! GPTM Timer B Prescale Match Register Value mask
//
#define TIMER_GPTMTBPMR_M    		0x000000FF

//
//! GPTM Timer B Prescale Match Register Value shift
//
#define TIMER_GPTMTBPMR_S    		0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup Stellaris_Register_TIMER_0_GPTMTAR TIMER_0_GPTMTAR
//! @{
//
//*****************************************************************************

//
//! GPTM Timer A Register Value mask
//
#define TIMER_GPTMTAR_M    			0xFFFFFFFF

//
//! GPTM Timer A Register Value shift
//
#define TIMER_GPTMTAR_S    			0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup Stellaris_Register_TIMER_0_GPTMTBR TIMER_0_GPTMTBR
//! \brief Defines for the bit fields in the TIMER_0_GPTMTBR register.
//! @{
//
//*****************************************************************************

//
//! GPTM Timer B Register Value mask
//
#define TIMER_GPTMTBR_M    			0xFFFFFFFF

//
//! GPTM Timer B Register Value shift
//
#define TIMER_GPTMTBR_S    			0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup Stellaris_Register_TIMER_0_GPTMTAV TIMER_0_GPTMTAV
//! @{
//
//*****************************************************************************

//
//! GPTM Timer A Value Register Value mask
//
#define TIMER_GPTMTAV_M    			0xFFFFFFFF

//
//! GPTM Timer A Value Register Value shift
//
#define TIMER_GPTMTAV_S    			0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup Stellaris_Register_TIMER_0_GPTMTBV TIMER_0_GPTMTBV
//! @{
//
//*****************************************************************************

//
//! GPTM Timer B Value Register Value mask
//
#define TIMER_GPTMTBV_M    			0xFFFFFFFF

//
//! GPTM Timer B Value Register Value shift
//
#define TIMER_GPTMTBV_S    			0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************



//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

#endif // __XHW_TIMER_H__
