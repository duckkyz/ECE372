/* 
 * File:   switch.c
 * Author: gvanhoy
 *
 * Created on August 27, 2015, 3:12 PM
 */

#include <xc.h>

#define INPUT 1
#define OUTPUT 0

#define ENABLED 1
#define DISABLED 0

#define DOWN 0

void initSwitch1(){
    //TODO: Initialize switch 1
    TRISDbits.TRISD6 = INPUT;   //SW1 = input
    CNCONDbits.ON = ENABLED;    //CN on
    CNENDbits.CNIED6 = ENABLED; // Enable CN interrupt for pin
    IEC1bits.CNDIE = ENABLED;   // Enable overall CN Interrupt
    IFS1bits.CNDIF = DOWN;      // Put Interrupt flag down
    CNPUDbits.CNPUD6 = ENABLED; //Enable PUR   
}