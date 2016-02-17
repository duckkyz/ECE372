// ******************************************************************************************* //
//
// File:         lab1p1.c
// Date:         
// Authors:      
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
//#define SWITCH PORTDbits.RD6
/* Please note that the configuration file has changed from lab 0.
 * the oscillator is now of a different frequency.
 */

typedef enum stateTypeEnum{
    run, stop, debouncePush, debounceRelease, wait
} stateType;

volatile stateType state = run;
volatile stateType lastState = run;
volatile int buttonState;

int main(void)
{
    SYSTEMConfigPerformance(40000000);
    enableInterrupts();
    
    initLEDs();
    //initTimer2();
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
                CNCONGbits.ON = 0;          //G Change Notification off
                delayMs(5);
                if(lastState == run) state = stop;
                else if(lastState == stop) state = run;
                //buttonState = 2;
                CNCONGbits.ON = 1;          //G Change Notification on
                break;
            case(debounceRelease):
                CNCONGbits.ON = 0;          //G Change Notification off
                delayMs(5);
                state = lastState;
                CNCONGbits.ON = 1;          //G Change Notification on
                //buttonState = 3;
                break;
            case(wait):
                //if(SWITCH == PUSHED) state = debouncePush;
                //else if(SWITCH == RELEASED) state = debounceRelease;
                break;
        }
    }
    
    return 0;
}

void __ISR(_CHANGE_NOTICE_VECTOR, IPL4SRS) _CNInterrupt(void){
    if(SWITCH == PUSHED){
        //buttonState = PUSHED;
        state = debouncePush;
    }
    else{
        //buttonState = RELEASED;
        state = debounceRelease;
    }
    IFS1bits.CNGIF = 0;
}