/*
 * File:   timer.c
 * Authors: Ben Johnson
 *
 * Created on Feb 5, 2016
 */

#include <xc.h>
#include "timer.h"

void initTimer2(){
    TMR2 = 0;              //Clears TMR2
    T2CONbits.TCKPS = 0;    //Sets the pre-scalar
    T2CONbits.TCS = 0;      //Sets up the oscillator
    IEC0bits.T2IE = 1;      // Enable the interrupt
    IFS0bits.T2IF = 0;      // Put the flag down
    IPC2bits.T2IP = 2;      // Configure the Interrupt Priority
    
}

<<<<<<< HEAD
void delayMs(unsigned int delay){
    TMR2 = 0;                   //Clears TMR2
    IFS0bits.T2IF = 0;      // Put the flag down
    PR2 = delay*624;            //Sets the delay as a multiple of Us
    T2CONbits.ON = 1;           //Turn timer on
    while(IFS0bits.T2IF == 0); //While the timer isn't done
    IFS0bits.T2IF = 0;
=======
void delayMs(int delay){
    //TODO: Using timer 2, create a delay
    // that is delay amount of ms.
    // osc = 625000 Hz
    // PR = ((10^(-3))*625000)/1 - 1 
    // PR = 624
    
    TMR2 = 0;                   //Clears TMR2
    PR2 = delay*624;            //Sets the delay as a multiple of ms
    IFS0bits.T2IF = 0;          //Puts down flag
    T2CONbits.ON = 1;  
    while(IFS0bits.T2IF == 0);  //While the timer isn't done
    IFS0bits.T2IF = 0;          //Lower flag
>>>>>>> Lab0/master
    T2CONbits.ON = 0;           //Turn timer off
}