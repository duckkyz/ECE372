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
<<<<<<< HEAD
//#define SWITCH PORTDbits.RD6
=======
>>>>>>> Lab0/master
/* Please note that the configuration file has changed from lab 0.
 * the oscillator is now of a different frequency.
 */

typedef enum stateTypeEnum{
    run, stop, debouncePush, debounceRelease, wait
} stateType;

<<<<<<< HEAD
volatile stateType state = run;
volatile stateType lastState = run;
volatile int buttonState;
=======
volatile int dummyVariable = 0;
volatile stateType state = run;
volatile stateType lastState = run;
volatile stateType nextState = stop ;
>>>>>>> Lab0/master

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
<<<<<<< HEAD
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
=======
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
>>>>>>> Lab0/master
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
<<<<<<< HEAD
    if(SWITCH == PUSHED){
        //buttonState = PUSHED;
        state = debouncePush;
    }
    else{
        //buttonState = RELEASED;
=======
    dummyVariable = PORTGbits.RG13 = 1;
    IFS1bits.CNGIF = 0;
    if(SWITCH == PUSHED) {
        if(lastState == run) nextState = stop;
        else if(lastState == stop) nextState = run;
        state = debouncePush;
    }
        
    else if(SWITCH == RELEASED){ 
        //nextState = lastState;
>>>>>>> Lab0/master
        state = debounceRelease;
        
    }
<<<<<<< HEAD
    IFS1bits.CNGIF = 0;
=======
>>>>>>> Lab0/master
}