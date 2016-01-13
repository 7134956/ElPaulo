/******************************************************************************
 Includes
******************************************************************************/

#include "ATA6870_func.h"
#include "stm32f10x.h"
#include "can.h"
//#include <avr/io.h>
//#include <avr/pgmspace.h>
//#include <stdint.h>
//#include <util/delay.h>

/******************************************************************************
 Global variables.
******************************************************************************/

//!< Sets the connected Cells. Value defined in config.h
uint8_t ActiveCells[CHIPS];

uint32_t ActiveShunt;

//!< Cellvoltages*10000.[Chip][Cell]
uint32_t VBAT[CHIPS][6];
//!< ADC Voltage acquisition.[Chip][Cell]
uint16_t Acquisition[CHIPS][6];
//!< ADC Offset acquisition.[Chip][Cell]
uint16_t Offset[CHIPS][6];

//!< Sets the active Temperature Channel
uint8_t ActiveTemp;
//!< ADC Temperature acquisistions.[NTC Channel]
uint16_t Tacquisition[CHIPS*2];
//!< Temperature Reference resistors. Value defined in config.h
uint16_t RefRes[CHIPS*2];
//!< Temperature in °C
int8_t Temp[CHIPS*2];

const uint16_t ADC_Lookup[] = {
#include "LookupADC.txt"
};

/*
Current Operation	0x01 - Offsetacq, 
					0x03 - Voltageacq 
*/
uint8_t operation;

//!< Turns ATA6870 off or on
uint8_t ATA6870_state = 0x01;

/*! \brief Main loop 
 *
 *   The code provided in the main() function is intended as example of how to
 *   use the ATMega32HVB and ATA6870 together.\n
 *
 *   The example is not a complete application intended for use with smart
 *   batteries, and it would most likely be desirable to do use the devices
 *   somewhat different in a smart battery application. It is e.g. expected
 *   that interrupts between ATA6870 and ATMega32HVB would be used. 
 */

int main(void){
	
	//!< Temperature Reference resistors. Value defined in config.h
	RefRes[0]=RES_REF1;
	RefRes[1]=RES_REF2;
	RefRes[2]=RES_REF3;
	RefRes[3]=RES_REF4;

	//!< Sets the connected Cells. Value defined in config.h
	ActiveCells[0] = CELLSIC1;
	ActiveCells[1] = CELLSIC2;
	ActiveCells[2] = CELLSIC3;
	ActiveCells[3] = CELLSIC4;

	CCInit();				// Coulombcounter Init
	SPI_MasterInit();		// SPI Init
	TimerInit(DELAY_TIM_FREQUENCY);			// Timer prescaler Init
	CLK_init(CHIP_CLK); // Start Frequency output for ATA6870(kHz)
	CAN_init(); //Setup CAN bus
	
	while(OpenCellcheck()){ //Checks for open Clamps
		_delay_ms(50);
	}

//	sei();	// enable interrupt

	while(1){
		if(ATA6870_state){
			PD_N_ON();
		}
		else{
			PD_N_OFF();
		}


		//----------------------------- Vacq 1---------------------------------------//
		ATA6870_SPI_COM(0x01,0x0B,0x02);//wakeup irq surpressed
		_delay_ms(20);
		
		ActiveTemp=0x00;				//Set measured Temperature Channel
		ATA6870_SPI_COM(0x01,0x05,0x03);//Vacq Temp Channel 1
		_delay_ms(20);
		
		ATA6870_SPI_COM(0x01,0x0C,0x00);//Read Status Reg
		_delay_ms(20);
		
		operation=0x03;
		ATA6870_SPI_COM(0x01,0xFE,0x00);//Burstread

		_delay_ms(20);

		ReadNTC();
		//------------------------------ Offset acq 1---------------------------------//	
		
		
		ATA6870_SPI_COM(0x01,0x05,0x01);//Offset acq
		_delay_ms(20);
		
		ATA6870_SPI_COM(0x01,0x0C,0x00);//Read Status Reg
		_delay_ms(20);
		
		operation=0x01;
		ATA6870_SPI_COM(0x01,0xFE,0x00);//Burstread
		_delay_ms(20);
		
		//--------------------------------- Check 1------------------------------------//
	
		CalculateV(0x01);
		//----------------------------- NTC2 Chip1---------------------------------------//
		
		ActiveTemp=0x01;				//Set measured Temperature Channel
		ATA6870_SPI_COM(0x01,0x05,0x0B);//Vacq Temp Channel 2
		_delay_ms(20);
		
		ATA6870_SPI_COM(0x01,0x0C,0x00);//Read Status Reg
		_delay_ms(20);
		
		operation=0x03;
		ATA6870_SPI_COM(0x01,0xFE,0x00);//Burstread

		_delay_ms(20);

		ReadNTC();
		
		//--------------------------------- Vacq 2--------------------------------------//

		ATA6870_SPI_COM(0x02,0x0B,0x02);//wakeup irq surpressed
		_delay_ms(20);
		
		ATA6870_SPI_COM(0x02,0x05,0x03);//Vacq Temp Channel 1
		_delay_ms(20);
		
		ATA6870_SPI_COM(0x02,0x0C,0x00);//Read Status Reg
		_delay_ms(20);
		
		operation=0x03;
		ATA6870_SPI_COM(0x02,0xFE,0x00);//Burstread
		_delay_ms(20);
		
		//------------------------------ Offset acq 2----------------------------------//	
	
		
		ATA6870_SPI_COM(0x02,0x05,0x01);//Offset acq
		_delay_ms(20);
		
		ATA6870_SPI_COM(0x02,0x0C,0x00);//Read Status Reg
		_delay_ms(20);
		
		operation=0x01;
		ATA6870_SPI_COM(0x02,0xFE,0x00);//Burstread
		_delay_ms(20);
		
		//------------------------------------ Check 2----------------------------------//
		
		CalculateV(0x02);
		
		if(Undervoltage(25000,0x01)||Overvoltage(42000,0x01)||Undervoltage(25000,0x02)||Overvoltage(42000,0x02)||Temp[0]<=(T_LOWERTRESHOLD)||Temp[0]>=T_UPPERTHRESHOLD||Temp[1]<=(T_LOWERTRESHOLD)||Temp[1]>=T_UPPERTHRESHOLD){
			Configure_Fet(0x00);
		}
		else{
			Configure_Fet(0x03);
		}
		
	}
}


/*******************************************************************************
 *Delay by the provided number of micro seconds.
 *Limitation: "us" * System-Freq in MHz must now overflow in 16 bit.
 *Values between 0 and 1.000 (1 second) are ok.
 ******************************************************************************/
void _delay_ms(uint16_t ms) {
	TIM_SetCounter(TIM1, 0);
	/* use 16 bit count wrap around */
	while ((uint16_t) (TIM1->CNT) <= ms)
		;
}
