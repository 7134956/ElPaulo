/*
Частота процессора и шин пускай 8MHz
CELL 24
Number of ATA6870N 4
SCK Frequency (kHz) 250
CLK Frequency(kHz) 500
Балансировочное сопротивление 33 Ом
Ток до 110ма
*/


#ifndef CONFIG_H
#define CONFIG_H

#include "stdint.h"

#define CLK_PORT 
#define CLK_PIN 
#define CHIP_CLK 500000
#define CHIPS 4

#define DELAY_TIM_FREQUENCY 1000 /* = 1KHZ -> timer runs in milliseconds */

//!< Cells IC 1 Bits 0-5 -> Cells 1-6
#define CELLSIC1 0x3F
//!< Cells IC 2	Bits 0-5 -> Cells 1-6
#define CELLSIC2 0x3F
//!< Cells IC 3 Bits 0-5 -> Cells 1-6
#define CELLSIC3 0x3F
//!< Cells IC 4	Bits 0-5 -> Cells 1-6
#define CELLSIC4 0x3F

//!< Temperature reference resistance in Ohm
#define RES_REF1                (3300)
//!< Temperature reference resistance in Ohm
#define RES_REF2                (3300)
//!< Temperature reference resistance in Ohm
#define RES_REF3                (3300)
//!< Temperature reference resistance in Ohm
#define RES_REF4                (3300)

//!< Temperature Lookup Start
#define T_TLS                   (-20)
//!< Temperature Lookup End
#define T_TLE                   (80)
//!< Temperature Lookup Stepsize
#define T_TLSZ                  (1)

//!< Temperature Lower Threshold
#define T_LOWERTRESHOLD         (-20)
//!< Temperature Upper Threshold
#define T_UPPERTHRESHOLD        (+60)

//!< Shunt resistance in mOhm
#define SHUNT_RESISTANCE        (10)
//!< RCC Conversion Period 0x00 - 256ms, 0x01 - 512ms, 0x02 - 1s, 0x03 - 2s
#define RCC_CONVERSIONPERIOD    (0x00)
//!< RCC Divide Stepsize
#define RCC_DIVIDEDSZ           (0)
//!< RCC Charge Threshold in mA
#define RCC_CHARGETHRESHOLD     (50)
//!< RCC Discharge Threshold in mA
#define RDC_DISCHARGETHRESHOLD  (50)

//!< CC-ADC Regular Current Condition voltage step size in V
#define RCC_STEP_SIZE_uV        (26.855)
//!< RCC steps size in mA (with a given \ref SHUNT_RESISTANCE)
#define RCC_STEP_SIZE_mA        (RCC_STEP_SIZE_uV/SHUNT_RESISTANCE)
//!< RCC CADRCC Value
#define RCC_CADRCC (~((int)((float)RCC_CHARGETHRESHOLD/RCC_STEP_SIZE_mA)))+1
//!< RDC CADRDC Value
#define RDC_CADRDC (~((int)((float)RDC_DISCHARGETHRESHOLD/RCC_STEP_SIZE_mA)))+1


//!< F_CPU Value in Hz
#define F_CPU 8000000UL //Should not be changed!(See Applicationnote for further info)

#endif
