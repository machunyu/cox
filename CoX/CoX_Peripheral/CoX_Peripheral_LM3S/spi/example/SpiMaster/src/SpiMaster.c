//*****************************************************************************
//
//! \file SPI_loop.c
//! \brief Test SPI.
//! \version 1.0
//! \date 8/2/2011
//! \author CooCox
//! \copy
//!
//! Copyright (c) 2009-2011 CooCox.  All rights reserved.
//
//*****************************************************************************
#include "xhw_types.h"
#include "xhw_memmap.h"
#include "xspi.h"
#include "xhw_spi.h"
#include "xsysctl.h"
#include "xgpio.h"
#include "xcore.h"

unsigned long ulSourceData[] = {0x01, 0x12, 0x23, 0x34,
                                0x45, 0x56, 0x67, 0x78};
unsigned long ulDestData[8];


//*****************************************************************************
//
//! Ininite the SPI case which is needed
//!
//! \param None
//!
//! This function ininite the SPI including clock source and enable spi 
//!
//! \return none
//
//*****************************************************************************
void SpiReceiveTransferInit(void)
{
		unsigned long ulTemp;
	
    //
    // Set SysClk 50MHz using Extern 16M oscillator
    //
    xSysCtlClockSet(50000000, xSYSCTL_OSC_MAIN | xSYSCTL_XTAL_16MHZ | SYSCTL_INT_OSC_DIS);
	
    //
    // Enable Peripheral SPI0
    //
    xSysCtlPeripheralReset(xSYSCTL_PERIPH_SPI0);
    xSysCtlPeripheralEnable(xSYSCTL_PERIPH_SPI0);
    xSysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

		ulTemp = (xSPI_MOTO_FORMAT_MODE_0 | xSPI_MODE_MASTER | xSPI_DATA_WIDTH8);
		xSPIConfigSet(xSPI0_BASE, 2000000, ulTemp);
	
    //
    // Configure Some GPIO pins as SPI Mode
    //
    xSPinTypeSPI(SPI0CLK, PA2);
		xSPinTypeSPI(SPI0CS, PA3);
		xSPinTypeSPI(SPI0RX, PA4);
		xSPinTypeSPI(SPI0TX, PA5);	
		
		//
		// make ssi run as loopback test mode
		//
		xHWREG(xSPI0_BASE + SSI_CR1) |= SSI_CR1_LBM;
		
		SSIEnable(xSPI0_BASE);
}
//*****************************************************************************
//
//! Spi Master Slave Mode Configure
//!
//! \param None
//!
//! This function configure the SPI as master and slave mode at the same time
//! transfer and receive data
//!
//! \return None
//
//*****************************************************************************
void SpiSlaveModeConfig(void)
{   
		unsigned long i;
	
    for(i = 0; i < 8; i++)
    {
        ulDestData[i] = xSPISingleDataReadWrite(xSPI0_BASE, ulSourceData[i]);
    }    
}
