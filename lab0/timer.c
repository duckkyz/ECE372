/* 
 * File:   timer.c
 * Author: Sean Kenney
 *
 * Created on August 27, 2015, 3:26 PM
 */

#include <xc.h>

void initTimer1(){
    TMR1 = 0;// Keeps track of the count
    PR1 = 1221*2;// Thing to compare against
    T1CONbits.TCKPS = 3; // Initialize pre-scalar
    T1CONbits.TCS = 0; // Setting the oscillator
    IEC0bits.T1IE = 1;// Enable the interrupt
    IFS0bits.T1IF = 0;// Put the flag down
    IPC1bits.T1IP = 3;// Configure the Interrupt Priority
    //T1CONbits.TON = 1;// Turn the timer on
}

initTimer2(){
    TMR2 = 0 ;// clear TMR1
    T2CONbits.TCKPS = 0;//pre-scalar
    T2CONbits.TCS = 0;//osc config
    IFS0bits.T2IF = 0;//flag
    
}

delayMs(int delay){
    TMR2 = 0;
    PR2 = delay*624;
    IFS0bits.T2IF = 0;//flag
    T2CONbits.ON = 1;
    while(IFS0bits.T2IF == 0){}
    T2CONbits.ON = 0;
    IFS0bits.T2IF = 0;
    
}