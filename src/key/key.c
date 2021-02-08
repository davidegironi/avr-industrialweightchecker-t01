/*
key lib 0x03 exttimer

copyright (c) Davide Gironi, 2012

References:
  * Debouncing 8 Keys Sampling 4 Times With Repeat Function
    by Peter Dannegger (danni@specs.de)
    http://www.mikrocontroller.net/attachment/46796/tasten.c

Released under GPLv3.
Please refer to LICENSE file for licensing information.
*/

#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#include "key.h"

volatile uint8_t key_state; // debounced and inverted key state: bit = 1: key pressed
volatile uint8_t key_press; // key press detect
volatile uint8_t key_rpt; // key long press and repeat

/*
 * timer0 interrupt
 * check the key pressed every 10ms
 */
void key_timerinterrupt() {
	static uint8_t ct0, ct1;
	static uint16_t rpt;
	uint8_t i;

	i = key_state ^ ~KEY_PIN; // key changed ?
	ct0 = ~(ct0 & i); // reset or count ct0
	ct1 = ct0 ^ (ct1 & i); // reset or count ct1
	i &= ct0 & ct1; // count until roll over ?
	key_state ^= i; // then toggle debounced state
	key_press |= key_state & i; // 0->1: key press detect

	if( (key_state & KEY_REPEATMASK) == 0 ) // check repeat function
		rpt = KEY_REPEATSTART; // start delay
	if( --rpt == 0 ) {
		rpt = KEY_REPEATNEXT; // repeat delay
		key_rpt |= key_state & KEY_REPEATMASK;
	}
}

/*
 * check if a key is pressed
 */
uint8_t key_getpress(uint8_t key_mask) {
	cli();
	key_mask &= key_press; // read key(s)
	key_press ^= key_mask; // clear key(s)
	sei();
	return key_mask;
}

/*
 * check if a key is pressed with repetition
 */
uint8_t key_getrpt(uint8_t key_mask) {
	cli();
	key_mask &= key_rpt; // read key(s)
	key_rpt ^= key_mask; // clear key(s)
	sei();
	return key_mask;
}

/*
 * check if a key is pressed one time
 */
uint8_t key_getshort(uint8_t key_mask) {
	cli();// read key state and key press atomic !
	return key_getpress( ~key_state & key_mask );
}

/*
 * check if a key is pressed for long time
 */
uint8_t key_getlong(uint8_t key_mask) {
	return key_getpress( key_getrpt( key_mask ) );
}

/*
 * init the key functions
 */
void key_init() {
	//input
	KEY_DDR &= ~(1 << KEY_BUTTON1);
	KEY_DDR &= ~(1 << KEY_BUTTON2);
	KEY_DDR &= ~(1 << KEY_BUTTON3);
}
