/*
 * File:   timer.c
 * Authors:
 *
 * Created on December 30, 2014, 8:07 PM
 */

#include <xc.h>
#include "timer.h"

//PR = [(delay*Freq)/prescaler] - 1
//
//
/*
void initTimer1(){
    TMR1 = 0;               // Keeps track of the count
    T1CONbits.TCKPS = 0;    // Initialize pre-scalar
    T1CONbits.TCS = 0;      // Setting the oscillator
    IEC0bits.T1IE = 1;      // Enable the interrupt
    IFS0bits.T1IF = 0;      // Put the flag down
    IPC1bits.T1IP = 3;      // Configure the Interrupt Priority
}
*/

void initTimer2(){
    TMR2 = 0;              //Clears TMR2
    T2CONbits.TCKPS = 0;    //Sets the pre-scalar
    T2CONbits.TCS = 0;      //Sets up the oscillator
    //IEC0bits.T2IE = 1;      // Enable the interrupt
    IFS0bits.T2IF = 0;      // Put the flag down
    IPC2bits.T2IP = 2;      // Configure the Interrupt Priority
    
}

void delayMs(int delay){
    //TODO: Using timer 2, create a delay
    // that is delay amount of ms.
    
    TMR2 = 0;                   //Clears TMR2
    PR2 = delay*625;            //Sets the delay as a multiple of ms
    IFS0bits.T2IF = 0;          //Puts down flag
    T2CONbits.ON = 1;  
    //IEC1bits.CNGIE = 0;         //Turn timer on
    while(IFS0bits.T2IF == 0); //While the timer isn't done
    IFS0bits.T2IF = 0;
    //IEC1bits.CNGIE = 1;
    T2CONbits.ON = 0;           //Turn timer off
}
/*
void delayUs(unsigned int delay){
    TMR2 = 0;                   //Clears TMR2
    IFS0bits.T2IF = 0;      // Put the flag down
    PR2 = delay*39;            //Sets the delay as a multiple of Us
    T2CONbits.ON = 1;           //Turn timer on
    while(IFS0bits.T2IF == 0); //While the timer isn't done
    IFS0bits.T2IF = 0;
    T2CONbits.ON = 0;           //Turn timer off
}
*/