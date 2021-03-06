#ifndef _LED_H_
#define _LED_H_

#include "config.h"

/*******************************************************************************
 * Declare function prototypes
 ******************************************************************************/
void LED_init(void);
void invert_leds(uint8_t);
void set_leds(uint8_t);
void reset_leds(uint8_t);
//------------------------------------------------------------------------------
#define LED_BLUE 0x2
#define PIN_LED_BLUE GPIO_Pin_13

#endif /* _LED_H_ */
