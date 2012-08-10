//*****************************************************************************
//
//! @page xsysctl_testcase xcore register test
//!
//! File: @ref xsysctltest.c
//!
//! <h2>Description</h2>
//! This module implements the test sequence for the xsysctl sub component.<br><br>
//! - \p Board: M051 <br><br>
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

unsigned long ulLdoVoltage[] = {SYSCTL_LDO_2_25V, SYSCTL_LDO_2_30V, SYSCTL_LDO_2_35V,
                                SYSCTL_LDO_2_40V, SYSCTL_LDO_2_45V, SYSCTL_LDO_2_50V,
                                SYSCTL_LDO_2_55V, SYSCTL_LDO_2_60V, SYSCTL_LDO_2_65V,
                                SYSCTL_LDO_2_70V, SYSCTL_LDO_2_75V};

//*****************************************************************************
//
//! \brief Get the Test description of xsysctl004 register test.
//!
//! \return the desccription of the xcore004 test.
//
//*****************************************************************************
static char* xSysctl005GetTest(void)
{
    return "xsysctl, 005, xsysctl api test:Power and BOD.";
}

//*****************************************************************************
//
//! \brief something should do before the test execute of xsysctl002 test.
//!
//! \return None.
//
//*****************************************************************************
static void xSysctl005Setup(void)
{

}

//*****************************************************************************
//
//! \brief something should do after the test execute of xsysctl001 test.
//!
//! \return None.
//
//*****************************************************************************
static void xSysctl005TearDown(void)
{   

}

//*****************************************************************************
//
//! \brief xsysctl 005 test of Brown-Out Detector Control Register test .
//!
//! \return None.
//
//*****************************************************************************
static void xsysctl_Ldo_test(void)
{    
    unsigned long ulTemp,i; 
    
    //
    // Set Threshold Voltage as 2.2V test
    //
    for(i = 0; i < 11; i++)
    {
        SysCtlLDOSet(ulLdoVoltage[i]);
        ulTemp = SysCtlLDOGet();
        TestAssert(ulLdoVoltage[i] == (ulTemp & ulLdoVoltage[i]),
                                                        "xsysctl API error!");
    }
}

//*****************************************************************************
//
//! \brief xsysctl 005 test execute main body.
//!
//! \return None.
//
//*****************************************************************************
static void xSysctl005Execute(void)
{
    xsysctl_Ldo_test();
}

//
// xsysctl register test case struct.
//
const tTestCase sTestXSysctl005Register = {
    xSysctl005GetTest,
    xSysctl005Setup,
    xSysctl005TearDown,
    xSysctl005Execute
};

//
// Xsysctl test suits.
//
const tTestCase * const psPatternXsysctl04[] =
{
    &sTestXSysctl005Register,
    0
};
