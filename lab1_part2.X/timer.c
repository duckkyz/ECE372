/*
 * File:   timer.c
 * Authors:
 *
 * Created on December 30, 2014, 8:07 PM
 */

#include <xc.h>
#include "timer.h"

void initTMR2(){
    TMR2 = 0;
    T2CONbits.TCKPS = 3;        //Sets pre-scalar to 8
    T2CONbits.TCS = 0;          //Use internal clock

}
void delayUs(unsigned int delay){
    TMR2 = 0;
    PR2 = delay*10-1;
    IFS0bits.T2IF = 0;          //Lowers flag
    T2CONbits.ON = 1;           //Turns on timer
    while(IFS0bits.T2IF == 0);  //Waits for timer to finish 
    T2CONbits.ON = 0;           //Turns off timer
    IFS0bits.T2IF = 0;          //Lowers flag
    
}