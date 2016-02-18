// ******************************************************************************************* //
//
// File:         lab1p1.c
// Date:         2/5/2016
// Authors:      Ben Johnson
//
// Description: Part 1 for lab 1
// ******************************************************************************************* //

#include <xc.h>
#include <sys/attribs.h>
#include "config.h"
#include "leds.h"
#include "interrupt.h"
#include "switch.h"
#include "timer.h"


#define OUTPUT 0
#define INPUT 1

#define PART1 0
#define PART2 1

#define RUNLED 1
#define STOPLED 2

#define FORWARD 0
#define BACKWARD 1

#define RELEASED 1
#define PUSHED 0

#define SWITCH PORTGbits.RG13
/* Please note that the configuration file has changed from lab 0.
 * the oscillator is now of a different frequency.
 */

typedef enum stateTypeEnum{
    run, stop, debouncePush, debounceRelease, wait
} stateType;

volatile stateType state = run;
volatile stateType lastState;

int main(void)
{
    SYSTEMConfigPerformance(10000000);
    enableInterrupts();
    
    initLEDs();
    initTimer2();
    initSW2();
    
    while(1){
        switch(state){
            case(run):
                turnOnLED(RUNLED);
                lastState = run;
                state = wait;
                break;
            case(stop):
                turnOnLED(STOPLED);
                lastState = stop;
                state = wait;
                break;
            case(debouncePush):
                CNENGbits.CNIEG13 = 0;      //CN for the pin
                delayMs(5);
                if(lastState == run) state = stop;
                else if(lastState == stop) state = run;
                CNENGbits.CNIEG13 = 1;      //CN for the pin
                break;
            case(debounceRelease):
                CNENGbits.CNIEG13 = 0;      //CN for the pin
                delayMs(5);
                state = lastState;
                CNENGbits.CNIEG13 = 1;      //CN for the pin
                break;
            case(wait):
                break;
        }
    }
    
    return 0;
}

void __ISR(_CHANGE_NOTICE_VECTOR, IPL7SRS) _CNInterrupt(void){
    IFS1bits.CNGIF = 0;
    if(SWITCH == RELEASED) state = debounceRelease;
    else if(SWITCH == PUSHED) state = debouncePush;
}