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

#define SWITCH1 PORTDbits.RD6

//TODO: Define states of the state machine
typedef enum stateTypeEnum{
    led1, led2, led3, wait, wait2, debouncePress, debounceRelease, buttonPressLt1, buttonPress1, buttonReleased
} stateType;

//TODO: Use volatile variables that change within interrupts
volatile int part = PART1;               //Sets the lab part
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
                            TMR1 = 0;
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
                            T1CONbits.ON = 1;           //Turn TMR2 on
                            //if clock goes passed
                            /*Will wait until button is released:
                                if released before 1s, will set direction to FORWARD
                                and then move to buttonReleased
                                else will set direction to BACKWARD and move to 
                                buttonPress1
                            */
                            break;
                        case(buttonPress1):
                            direction = BACKWARD;
                            /*Will just hang out and wait for the button to be released
                                then will move to buttonReleased state
                            */
                            break;
                        case(buttonReleased):
                            delayMS(5);
                            /*Will wait until the counter has stabilized and then will move
                                to the next LED in the sqeuence based on lastLED and direction 
                            */
                            break;
                        case(wait):
                            delayMS(1);
                            state = buttonPressLt1;
                            break;
                        case(wait2):
                            //stuff
                            break;
                        case(debouncePress):
                            //Will wait un
                            break; 
                        case(debounceRelease):
                            //stuff
                            break; 
                        case(debounceRelease2):
                            //stuff
                            break; 
                    }
                break;
                
        }
        
    }
    
    return 0;
}


void __ISR(_TIMER_1_VECTOR, IPL3SRS) _T1Interrupt()
{
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
    else if(IFS0bits.T2IF == 1){
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
    else if(IFS1bits.CNDIF == 1){
        if(state == (led1 or led2 or led3)){
            state = wait;
            
        }
        else if(state == (buttonPressLt1 or buttonPress1)){
            state = buttonReleased;
        }
        
        
    }
}

