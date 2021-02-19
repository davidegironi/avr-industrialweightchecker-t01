/*
avr industrial weight checker t01 - v1.0

copyright (c) Davide Gironi, 2021

Released under GPLv3.
Please refer to LICENSE file for licensing information.
*/

#ifndef MAIN_H
#define MAIN_H

#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <avr/wdt.h>
#include <avr/eeprom.h>
#include <avr/pgmspace.h>

//include key lib
#include "key/key.h"

//include lcd lib
#include "lcd/lcd.h"

//include hx711 lib
#include "hx711/hx711.h"

//define buttons
#define BUTTON_UP KEY_BUTTON1
#define BUTTON_DOWN KEY_BUTTON2
#define BUTTON_SELECT KEY_BUTTON3

//programming status
#define PROGSTATUS_GETWEIGHTINTERVAL 0
#define PROGSTATUS_GETWEIGHTTHRESHOLDERR 1
#define PROGSTATUS_GETWEIGHTTHRESHOLDDIFF 2
#define PROGSTATUS_TARE 3
#define PROGSTATUS_ALERTENABLED 4
#define PROGSTATUS_SKIPINTERVAL 5
#define PROGSTATUS_SKIPTIME 6
#define PROGSTATUSTOT 7

//calibration status
#define CALSTATUS_GAIN 0
#define CALSTATUS_OFFSET 1
#define CALSTATUS_WEIGHT 2
#define CALSTATUS_SCALE 3
#define CALSTATUSTOT 4

//alarm relay
#define RELALERT_DDR DDRB
#define RELALERT_PORT PORTB
#define RELALERT_PINNUM PB2
#define RELALERT_OFF RELALERT_PORT |= (1<<RELALERT_PINNUM)
#define RELALERT_ON RELALERT_PORT &= ~(1<<RELALERT_PINNUM)

//skip relay
#define RELSKIP_DDR DDRD
#define RELSKIP_PORT PORTD
#define RELSKIP_PINNUM PD3
#define RELSKIP_OFF RELSKIP_PORT |= (1<<RELSKIP_PINNUM)
#define RELSKIP_ON RELSKIP_PORT &= ~(1<<RELSKIP_PINNUM)

//max and min weight interval
#define GETWEIGHT_INTERVAL_MIN 1
#define GETWEIGHT_INTERVAL_MAX 60

//max and min weight threshold errors
#define GETWEIGHT_THRESHOLDERR_MIN 1
#define GETWEIGHT_THRESHOLDERR_MAX 50

//max and min weight threshold diff error
#define GETWEIGHT_THRESHOLDDIFF_MIN -5000
#define GETWEIGHT_THRESHOLDDIFF_MAX +5000

//max and min calibration weight
#define WEIGHTCAL_WEIGHT_MIN 1
#define WEIGHTCAL_WEIGHT_MAX 100

//max and min skip interval
#define SKIP_INTERVAL_MIN 0
#define SKIP_INTERVAL_MAX 1440

//max and min skip time
#define SKIP_TIME_MIN 1
#define SKIP_TIME_MAX 60

//enabled alert
#define ALERT_ENABLED_DEFAULT 0

//default weight interval in sec
#define GETWEIGHT_INTERVAL_DEFAULT 1

//default weight threshold for errors in sec
#define GETWEIGHT_THRESHOLDERR_DEFAULT 5

//default weight threshold for diff weight
#define GETWEIGHT_THRESHOLDDIFF_DEFAULT 500

//default weight for calibration
#define WEIGHTCAL_WEIGHT_DEFAULT 10

//default calibration offset
#define WEIGHTCAL_OFFSET_DEFAULT 8000000

//default calibration scale
#define WEIGHTCAL_SCALE_DEFAULT 1000

//defaul skip interval
#define SKIP_INTERVAL_DEFAULT 0

//default skip time
#define SKIP_TIME_DEFAULT 2

//default calibration gain
#define WEIGHTCAL_GAIN_DEFAULT HX711_GAINDEFAULT


//main timer setting
//freq = FCPU / (prescale * (256 - preload))
//preload = 256 - FCPU/(prescaler * freqdesired)
//freq = FCPU / (prescale * 256)
//  es. 488.28 = 8000000 / ( 64 * 256)
#define MAINTIMER_PRESCALER (1<<CS01) | (1<<CS00)
//step to count 10 ms
#define MAINTIMER_10MSSTEP 5
//step to count 1000 ms
#define MAINTIMER_1000MSSTEP 488
//timer interrupt
#define MAINTIMER_INTERRUPT ISR(TIMER0_OVF_vect) 
//timer init
#define MAINTIMER_INIT \
    TCCR0 |= MAINTIMER_PRESCALER; \
	TIMSK |= 1<<TOIE0;

#endif
