/* 
 * File:   main.c
 * Author: Ben Johnson
 * Description: lab 0.
 * Created on August 27, 2015, 10:14 AM
 */

#include <xc.h>
#include <sys/attribs.h>
#include "switch.h"
#include "timer.h"
#include "led.h"
#include "interrupt.h"
#include "config.h"

#define OUTPUT 0
#define INPUT 1

#define PART1 0
#define PART2 1

#define LED_1 1
#define LED_2 2
#define LED_3 3

#define FORWARD 0
#define BACKWARD 1

#define RELEASED 1
#define PUSHED 0

#define SWITCH1 PORTDbits.RD6

//TODO: Define states of the state machine
typedef enum stateTypeEnum{
    led1, led2, led3, wait, wait2, wait3, debounceRelease, buttonPressLt1, buttonPress1, buttonReleased
} stateType;

//TODO: Use volatile variables that change within interrupts
volatile int part = PART2;               //Sets the lab part
volatile int direction = FORWARD;
volatile stateType state = led1;
volatile stateType lastLED;
volatile stateType nextLED;

int main() {    
    //This function is necessary to use interrupts. 
    enableInterrupts();
 
    //TODO: Write each initialization function
    initSwitch1();
    initLEDs();
    initTimer2();
    initTimer1();
    
    while(1){
        //TODO: Implement a state machine to create the desired functionality
        switch(part){
            case(PART1):            //Part 1 of lab
                switch(state){
                    case(led1):
                        turnOnLED(LED_1);
                        lastLED = state;
                        state = wait;
                        break;
                    case(led2):
                        turnOnLED(LED_2);
                        lastLED = state;
                        state = wait;
                        break;
                    case(led3):
                        turnOnLED(LED_3);
                        lastLED = state;
                        state = wait;
                        break;
                    case(wait):
                        T1CONbits.ON = 1;       //Turn timer on
                        break;


                }

            case(PART2):
                switch(state){
                    case(led1):
                        turnOnLED(LED_1);
                        lastLED = state;
                        state = wait;
                        break;
                    case(led2):
                        turnOnLED(LED_2);
                        lastLED = state;
                        state = wait;
                        break;
                    case(led3):
                        turnOnLED(LED_3);
                        lastLED = state;
                        state = wait;
                        break;
                    case(buttonPressLt1):
                        direction = FORWARD;
                        T1CONbits.ON = 1;           //Turn TMR1 on
                        if(SWITCH1 == RELEASED){
                            state = buttonReleased;
                            T1CONbits.ON = 0;
                            TMR1 = 0;
                        }
                        break;
                    case(buttonPress1):
                        direction = BACKWARD;
                        if(SWITCH1 == RELEASED) state = buttonReleased;

                        break;
                    case(buttonReleased):
                        delayMs(5);
                        state = wait3;
                        break;
                    case(wait):
                        if(SWITCH1 == PUSHED){
                            delayMs(5);
                            if(SWITCH1 == PUSHED) state = buttonPressLt1;
                        }
                        break;
                    case(wait2):
                        break;
                    case(wait3):
                        if(lastLED == led1){
                            if(direction == FORWARD) state = led2;
                            else if(direction == BACKWARD) state = led3;
                        }
                        else if(lastLED == led2){
                            if(direction == FORWARD) state = led3;
                            else if(direction == BACKWARD) state = led1;
                        }
                        else if(lastLED == led3){
                            if(direction == FORWARD) state = led1;
                            else if(direction == BACKWARD) state = led2;
                        }
                        break; 
                    case(debounceRelease):
                        //stuff
                        break; 
                }
            break;
        }
    }
    return 0;
}


void __ISR(_TIMER_1_VECTOR, IPL3SRS) _T1Interrupt(){
    if(IFS0bits.T1IF == 1){
        if(part == PART1){
            if(lastLED == led1) state = led2;
            else if(lastLED == led2) state = led3;
            else if(lastLED == led3) state = led1;
        }
        else if(part == PART2){
            if(state == buttonPressLt1) state = buttonPress1;
            
        }
        T1CONbits.ON = 0;                                       //Turn off timer
        IFS0bits.T1IF = 0;                                      //Puts flag down
    }
/*    else if(IFS0bits.T2IF == 1){
        if(part == PART1){}
        else if(part == PART2){
            if(state == buttonReleased){
                if(lastLED == led1){
                    if(direction == FORWARD) state = led2;
                    else if(direction == BACKWARD) state = led3;
                }
                else if(lastLED == led2){
                    if(direction == FORWARD) state = led3;
                    else if(direction == BACKWARD) state = led1;
                }
                else if(lastLED == led3){
                    if(direction == FORWARD) state = led1;
                    else if(direction == BACKWARD) state = led2;
                }
            }
        }
        T2CONbits.ON = 0;                                       //Turns off timer
        IFS0bits.T2IF = 0;                                      //Puts flag down
    }
    /*else if(IFS1bits.CNDIF == 1){
        if(part == PART1){}
        else if(part == PART2){
            if(state == (led1 | led2 | led3)){
                state = wait;

            }
            else if(state == (buttonPressLt1 | buttonPress1)){
                state = buttonReleased;
            }
        }
        IFS1bits.CNDIF = 0;
    }*/
}

