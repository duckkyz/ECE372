/*
 * File:   switch.c
 * Authors: Ben Johnson
 *
 * Created on Feb 5, 2016
 */

#include <xc.h>
#include "switch.h"

#define INPUT 1
#define OUTPUT 0


void initSW2(){
<<<<<<< HEAD
    TRISGbits.TRISG13 = INPUT;  
    CNCONGbits.ON = 1;          //G Change Notification on
    CNENGbits.CNIEG13 = 1;      //CN for the pin
    IEC1bits.CNGIE = 1;
    CNPUGbits.CNPUG13 = 1;
    
    /*
    TRISDbits.TRISD6 = INPUT;   //SW1 = input
    CNCONDbits.ON = 1;    //CN on
    CNENDbits.CNIED6 = 1; // Enable CN interrupt for pin
    IEC1bits.CNDIE = 1;   // Enable overall CN Interrupt
    IFS1bits.CNDIF = 0;      // Put Interrupt flag down
    CNPUDbits.CNPUD6 = 1; //Enable PUR
    */
    IPC8bits.CNIP = 7;
    IPC8bits.CNIS = 2;
    IFS1bits.CNGIF = 0;
=======
    
    TRISGbits.TRISG13 = INPUT;  
    CNCONGbits.ON = 1;          //G Change Notification on
    CNENGbits.CNIEG13 = 1;      //CN for the pin
    IEC1bits.CNGIE = 1;         //Enables the interrupt
    IFS1bits.CNGIF = 0;         //Lowers the flag
    CNPUGbits.CNPUG13 = 1;      //Puts the pull up resistor on
    IPC8bits.CNIP = 7;          //Sets the priority
    IPC8bits.CNIS = 2;          //Sets the secondary Priority
>>>>>>> Lab0/master
    
}
