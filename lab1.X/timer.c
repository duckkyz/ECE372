/*
 * File:   timer.c
 * Authors:
 *
 * Created on December 30, 2014, 8:07 PM
 */

#include <xc.h>
#include "timer.h"
void initTimer2(){
    TMR2 = 0;              //Clears TMR2
    T2CONbits.TCKPS = 0;    //Sets the pre-scalar
    T2CONbits.TCS = 0;      //Sets up the oscillator
    IFS0bits.T2IF = 0;      // Put the flag down
    IPC2bits.T2IP = 2;      // Configure the Interrupt Priority
    
}

void delayMs(unsigned int delay){
    TMR2 = 0;                   //Clears TMR2
    IFS0bits.T2IF = 0;      // Put the flag down
    PR2 = delay*624;            //Sets the delay as a multiple of Us
    T2CONbits.ON = 1;           //Turn timer on
    while(IFS0bits.T2IF == 0); //While the timer isn't done
    IFS0bits.T2IF = 0;
    T2CONbits.ON = 0;           //Turn timer off
}