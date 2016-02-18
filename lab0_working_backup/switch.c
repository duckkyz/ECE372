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
    TRISGbits.TRISG13 = INPUT;   //SW1 = input
    CNCONGbits.ON = ENABLED;    //CN on
    CNENGbits.CNIEG13 = ENABLED; // Enable CN interrupt for pin
    IEC1bits.CNGIE = ENABLED;   // Enable overall CN Interrupt
    IFS1bits.CNGIF = DOWN;      // Put Interrupt flag down
    CNPUGbits.CNPUG13 = ENABLED; //Enable PUR   
}