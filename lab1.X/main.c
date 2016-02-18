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

volatile int dummyVariable = 0;
volatile stateType state = run;
volatile stateType lastState = run;
volatile stateType nextState = stop ;

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
                break;
            case(stop):
                turnOnLED(STOPLED);
                lastState = stop;
                break;
            case(debouncePush):
                //CNENGbits.CNIEG13 = 0;      //CN for the pin
                //delayMs(5);
                state = wait;
                ///if(lastState == run) state = stop;
                //else if(lastState == stop) state = run;
                //CNENGbits.CNIEG13 = 1;      //CN for the pin
                break;
            case(debounceRelease):
                //CNENGbits.CNIEG13 = 0;      //CN for the pin
                //delayMs(5);
                state = nextState;
                //state = lastState;
                //CNENGbits.CNIEG13 = 1;      //CN for the pin
                break;
            case(wait):
                //if(SWITCH == PUSHED) state = debouncePush;
                //else if(SWITCH == RELEASED) state = debounceRelease;
                break;
        }
    }
    
    return 0;
}

void __ISR(_CHANGE_NOTICE_VECTOR, IPL7SRS) _CNInterrupt(void){
    dummyVariable = PORTGbits.RG13 = 1;
    IFS1bits.CNGIF = 0;
    if(SWITCH == PUSHED) {
        if(lastState == run) nextState = stop;
        else if(lastState == stop) nextState = run;
        state = debouncePush;
    }
        
    else if(SWITCH == RELEASED){ 
        //nextState = lastState;
        state = debounceRelease;
        
    }
}