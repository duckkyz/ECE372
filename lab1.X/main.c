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
    run, stop, debounce
} stateType;

volatile stateType state = run;
volatile stateType lastState;
volatile int buttonState;

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
                delayMs(10);
                break;
            case(stop):
                turnOnLED(STOPLED);
                lastState = stop;
                delayMs(10);
                break;
            case(debounce):
                //CNENDbits.CNIED6 = 0;      //CN for the pin
                delayMs(5);
                if (buttonState == PUSHED){
                    if(lastState == run) state = stop;
                    else if(lastState == stop) state = run;
                    buttonState = 2;
                }
                else if(buttonState == RELEASED){
                    delayMs(5);
                    state = lastState;
                    buttonState = 3;
                }
                //CNENDbits.CNIED6 = 1;      //CN for the pin
                break;
        }
    }
    
    return 0;
}

void __ISR(_CHANGE_NOTICE_VECTOR, IPL7SRS) _CNInterrupt(void){
    if(SWITCH == PUSHED) buttonState = PUSHED;
    else if(SWITCH == RELEASED) buttonState = RELEASED;
    state = debounce;
    IFS1bits.CNGIF = 0;
}