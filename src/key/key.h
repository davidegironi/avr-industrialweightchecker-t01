/*
key lib 0x03 exttimer

copyright (c) Davide Gironi, 2012

References:
  * Debouncing 8 Keys Sampling 4 Times With Repeat Function
    by Peter Dannegger (danni@specs.de)
    http://www.mikrocontroller.net/attachment/46796/tasten.c

Notes:
  use pullup resistors

Released under GPLv3.
Please refer to LICENSE file for licensing information.
*/

/*
Notes:
  * use pullup resistors
*/

#ifndef KEY_H_
#define KEY_H_

//setup button port
#define KEY_DDR DDRC
#define KEY_PIN PINC
#define KEY_BUTTON1 PC0
#define KEY_BUTTON2 PC1
#define KEY_BUTTON3 PC2

//setup repeat keymask for longpress buttons
#define KEY_REPEATMASK (1<<KEY_BUTTON1 ^ 1<<KEY_BUTTON2 ^ 1<<KEY_BUTTON3)

//setup repeat time
#define KEY_REPEATSTART 200 // after 2000ms
#define KEY_REPEATNEXT 10 // every 100ms

extern void key_init();
extern void key_timerinterrupt();
extern uint8_t key_getpress(uint8_t key_mask);
extern uint8_t key_getrpt(uint8_t key_mask);
extern uint8_t key_getshort(uint8_t key_mask);
extern uint8_t key_getlong(uint8_t key_mask);

#endif
