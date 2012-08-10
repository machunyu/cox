//*****************************************************************************
//
//! @page xsysctl_testcase xcore register test
//!
//! File: @ref xsysctltest.c
//!
//! <h2>Description</h2>
//! This module implements the test sequence for the xsysctl sub component.<br><br>
//! - \p Board: NUC122 <br><br>
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
//! - \subpage test_xsysctl_register
//! .
//! \file xsysctltest.c
//! \brief xsysctl test source file
//! \brief xsysctl test header file <br>
//
//*****************************************************************************

#include "test.h"
#include "xhw_memmap.h"

//*****************************************************************************
//
//!\page test_xsysctl_register test_xsysctl_register
//!
//!<h2>Description</h2>
//!Test xsysctl register. <br>
//!
//
//*****************************************************************************
//
//! NUC1xx_SysCtl_Peripheral_ID Array
//
#if 0
static unsigned long ulSYSCTL_PERIPH[] = { 
SYSCTL_PERIPH_WDOG0, SYSCTL_PERIPH_WDOG1, SYSCTL_PERIPH_CAN0, SYSCTL_PERIPH_CAN1, 
SYSCTL_PERIPH_PWM, SYSCTL_PERIPH_ADC0, SYSCTL_PERIPH_ADC1, SYSCTL_PERIPH_COMP0, 
SYSCTL_PERIPH_COMP1, SYSCTL_PERIPH_COMP2, SYSCTL_PERIPH_EPI0, SYSCTL_PERIPH_I2S0,
SYSCTL_PERIPH_TIMER0, SYSCTL_PERIPH_TIMER1, SYSCTL_PERIPH_TIMER2,SYSCTL_PERIPH_TIMER3,
SYSCTL_PERIPH_I2C0, SYSCTL_PERIPH_I2C1, SYSCTL_PERIPH_QEI0, SYSCTL_PERIPH_QEI1, 
SYSCTL_PERIPH_SSI0, SYSCTL_PERIPH_SSI1, SYSCTL_PERIPH_UART0, SYSCTL_PERIPH_UART1, 
SYSCTL_PERIPH_UART2, SYSCTL_PERIPH_IEEE1588, SYSCTL_PERIPH_ETH, SYSCTL_PERIPH_USB0, 
SYSCTL_PERIPH_UDMA};

static unsigned long ulRstSYSCTL_PERIPH[] = {
SYSCTL_PERIPH_WDOG0, SYSCTL_PERIPH_WDOG1, SYSCTL_PERIPH_CAN0,SYSCTL_PERIPH_CAN1, 
SYSCTL_PERIPH_PWM, SYSCTL_PERIPH_ADC0, SYSCTL_PERIPH_ADC1, SYSCTL_PERIPH_COMP0, 
SYSCTL_PERIPH_COMP1, SYSCTL_PERIPH_COMP2, SYSCTL_PERIPH_EPI0, SYSCTL_PERIPH_I2S0,
SYSCTL_PERIPH_TIMER0, SYSCTL_PERIPH_TIMER1, SYSCTL_PERIPH_TIMER2,SYSCTL_PERIPH_TIMER3,
SYSCTL_PERIPH_I2C0, SYSCTL_PERIPH_I2C1, SYSCTL_PERIPH_QEI0, SYSCTL_PERIPH_QEI1, 
SYSCTL_PERIPH_SSI0, SYSCTL_PERIPH_SSI1, SYSCTL_PERIPH_UART0, SYSCTL_PERIPH_UART1, 
SYSCTL_PERIPH_UART2, SYSCTL_PERIPH_IEEE1588, SYSCTL_PERIPH_ETH, SYSCTL_PERIPH_USB0, 
SYSCTL_PERIPH_UDMA};

#else

static unsigned long ulSYSCTL_PERIPH[] = { 
SYSCTL_PERIPH_WDOG0, SYSCTL_PERIPH_CAN0, SYSCTL_PERIPH_PWM, SYSCTL_PERIPH_ADC0,
SYSCTL_PERIPH_TIMER0, SYSCTL_PERIPH_TIMER1, SYSCTL_PERIPH_TIMER2, SYSCTL_PERIPH_TIMER3,
SYSCTL_PERIPH_COMP0, SYSCTL_PERIPH_I2C0, SYSCTL_PERIPH_QEI0, SYSCTL_PERIPH_QEI1,	
SYSCTL_PERIPH_SSI0, SYSCTL_PERIPH_UART0, SYSCTL_PERIPH_UART1, SYSCTL_PERIPH_ETH,
SYSCTL_PERIPH_IEEE1588};

static unsigned long ulRstSYSCTL_PERIPH[] = {
SYSCTL_PERIPH_CAN0, SYSCTL_PERIPH_PWM, SYSCTL_PERIPH_ADC0, SYSCTL_PERIPH_WDOG0,
SYSCTL_PERIPH_TIMER0, SYSCTL_PERIPH_TIMER1, SYSCTL_PERIPH_TIMER2, SYSCTL_PERIPH_TIMER3,
SYSCTL_PERIPH_COMP0, SYSCTL_PERIPH_I2C0, SYSCTL_PERIPH_QEI0, SYSCTL_PERIPH_QEI1,	
SYSCTL_PERIPH_SSI0, SYSCTL_PERIPH_UART0, SYSCTL_PERIPH_UART1, SYSCTL_PERIPH_ETH,
SYSCTL_PERIPH_IEEE1588};
#endif
//*****************************************************************************
//
//! \brief Get the Test description of xsysctl002 register test.
//!
//! \return the desccription of the xcore001 test.
//
//*****************************************************************************
static char* xSysctl003GetTest(void)
{
    return "xsysctl, 003, xsysctl api test:Peripheral Control.";
}

//*****************************************************************************
//
//! \brief something should do before the test execute of xsysctl002 test.
//!
//! \return None.
//
//*****************************************************************************
static void xSysctl003Setup(void)
{
    unsigned long ulTemp;
    ulTemp = SYSCTL_SYSDIV_1|SYSCTL_XTAL_8MHZ|SYSCTL_OSC_MAIN | SYSCTL_USE_OSC;
    SysCtlClockSet(ulTemp);
}

//*****************************************************************************
//
//! \brief something should do after the test execute of xsysctl001 test.
//!
//! \return None.
//
//*****************************************************************************
static void xSysctl003TearDown(void)
{   
		unsigned long ulTemp;
    ulTemp = SYSCTL_SYSDIV_1|SYSCTL_XTAL_8MHZ|SYSCTL_OSC_MAIN | SYSCTL_USE_OSC;
    SysCtlClockSet(ulTemp);
	
		SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);//开启GPIOA时钟
	
		xSPinTypeUART(UART0RX, PA0);
		xSPinTypeUART(UART0TX, PA1);
	
		xSysCtlPeripheralReset(xSYSCTL_PERIPH_UART0);
		xSysCtlPeripheralEnable(xSYSCTL_PERIPH_UART0);					//打开串口0时钟
	
		UARTConfigSetExpClk(UART0_BASE, 115200, (UART_CONFIG_WLEN_8 	| 
                                             UART_CONFIG_STOP_1	 	| 
                                             UART_CONFIG_PAR_NONE));
		UARTEnable(UART0_BASE, (UART_BLOCK_UART | UART_BLOCK_TX | UART_BLOCK_RX));
}

//*****************************************************************************
//
//! \brief xsysctl 001 test of Peripheral Disable test .
//!
//! \return None.
//
//*****************************************************************************
static void xsysctl_SysCtlPeripheralDisable_test(void)
{
    unsigned long ulTemp, ulRegVal, i;
    
    for(i = 0; i < 4; i++)
    {
        ulTemp = xHWREG(SYSCTL_RCGC0);				
        SysCtlPeripheralDisable(ulSYSCTL_PERIPH[i]);
				if(ulSYSCTL_PERIPH[i] & 0x00100000)
				{
						ulTemp &= ~(ulSYSCTL_PERIPH[i] << 16);
				}
				else
				{
						ulTemp &= ~(ulSYSCTL_PERIPH[i] & 0x0FFFFFFF);
				}
        ulRegVal = xHWREG(SYSCTL_RCGC0);
        TestAssert(ulRegVal == ulTemp,"xsysctl rcgc0 API error!");
        
    }
    
    for(i = 4; i <= 15; i++)
    {
        ulTemp = xHWREG(SYSCTL_RCGC1);
        SysCtlPeripheralDisable(ulSYSCTL_PERIPH[i]);
				if(ulSYSCTL_PERIPH[i] & 0x00100000)
				{
						ulTemp &= ~(ulSYSCTL_PERIPH[i] << 16);
				}
				else
				{
						ulTemp &= ~(ulSYSCTL_PERIPH[i] & 0x0FFFFFFF);
				}
        ulRegVal = xHWREG(SYSCTL_RCGC1);
        TestAssert(ulRegVal == ulTemp,"xsysctl rcgc1 API error!");       
    }
		
		for(i = 15; i < 17; i++)
		{
				ulTemp = xHWREG(SYSCTL_RCGC2);
        SysCtlPeripheralDisable(ulSYSCTL_PERIPH[i]);
				if(ulSYSCTL_PERIPH[i] & 0x00100000)
				{
						ulTemp &= ~(ulSYSCTL_PERIPH[i] << 16);
				}
				else
				{
						ulTemp &= ~(ulSYSCTL_PERIPH[i] & 0x0FFFFFFF);
				}
        ulRegVal = xHWREG(SYSCTL_RCGC2);
        TestAssert(ulRegVal == ulTemp,"xsysctl rcgc2 API error!");  
		}
}

//*****************************************************************************
//
//! \brief xsysctl 002 test of Peripheral reset test .
//!
//! \return None.
//
//*****************************************************************************
static void xsysctl_SysCtlPeripheralReset_test(void)
{
    unsigned long ulTemp;
    
    for (ulTemp = 0;ulTemp < 17; ulTemp++)
    {
        SysCtlPeripheralReset(ulRstSYSCTL_PERIPH[ulTemp]);
        TestAssert( (0 == xHWREG(SYSCTL_SRCR0))&&(0 == xHWREG(SYSCTL_SRCR1))&&(0 == xHWREG(SYSCTL_SRCR2)),
                                                          "xsysctl reset API error!");
    }
}


//*****************************************************************************
//
//! \brief xsysctl 002 test of Peripheral Enable test .
//!
//! \return None.
//
//*****************************************************************************
static void xsysctl_SysCtlPeripheralEnable_test(void)
{
    unsigned long ulRegVal, ulTemp, i;


    for(i = 0; i < 4; i++)
    {
				ulTemp = ulSYSCTL_PERIPH[i];
        SysCtlPeripheralEnable(ulTemp);
        ulRegVal = xHWREG(SYSCTL_RCGC0);
				if(ulTemp & 0x00100000)
				{
						ulTemp = ulTemp << 16;
				}
				else
				{
						ulTemp = ulTemp & 0x0FFFFFFF;
				}
        TestAssert((ulTemp == (ulRegVal & ulTemp)), "xsysctl API error!");        
    }
    
    for(i = 4; i < 15; i++)
    {
				ulTemp = ulSYSCTL_PERIPH[i];
        SysCtlPeripheralEnable(ulTemp);
        ulRegVal = xHWREG(SYSCTL_RCGC1);
				if(ulTemp & 0x00100000)
				{
						ulTemp = ulTemp << 16;
				}
				else
				{
						ulTemp = ulTemp & 0x0FFFFFFF;
				}
        TestAssert((ulTemp == (ulRegVal & ulTemp)), "xsysctl API error!");  
    }
		
		for(i = 15; i < 17; i++)
		{
				ulTemp = ulSYSCTL_PERIPH[i];
				SysCtlPeripheralEnable(ulSYSCTL_PERIPH[i]);
        ulRegVal = xHWREG(SYSCTL_RCGC2);
				if(ulTemp & 0x00100000)
				{
						ulTemp = ulTemp << 16;
				}
				else
				{
						ulTemp = ulTemp & 0x0FFFFFFF;
				}
        TestAssert((ulTemp == (ulRegVal & ulTemp)), "xsysctl API error!"); 
		}
}


//*****************************************************************************
//
//! \brief xsysctl 002 test execute main body.
//!
//! \return None.
//
//*****************************************************************************
static void xSysctl003Execute(void)
{
    xsysctl_SysCtlPeripheralEnable_test();
    xsysctl_SysCtlPeripheralDisable_test();

    xsysctl_SysCtlPeripheralReset_test();
}

//
// xsysctl register test case struct.
//
const tTestCase sTestXSysctl003Register = {
		xSysctl003GetTest,
		xSysctl003Setup,
		xSysctl003TearDown,
		xSysctl003Execute
};

//
// Xsysctl test suits.
//
const tTestCase * const psPatternXsysctl02[] =
{
    &sTestXSysctl003Register,
    0
};
