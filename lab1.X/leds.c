/*
* File:   leds.c
* Author: 
*
* Created on December 27, 2014, 1:31 PM
*/

#include <xc.h>
#include "leds.h"

#define OUTPUT 0
#define INPUT 1

#define OFF 0
#define ON 1

#define RUNLED LATGbits.LATG12
#define STOPLED LATGbits.LATG14
//#define RUNLED LATDbits.LATD0
//#define STOPLED LATDbits.LATD1

void initLEDs(){
    TRISGbits.TRISG12 = OUTPUT;
    TRISGbits.TRISG14 = OUTPUT; 
    ODCGbits.ODCG12 = 1;
    ODCGbits.ODCG14 = 1;
    //TRISDbits.TRISD0 = OUTPUT;
    //TRISDbits.TRISD1 = OUTPUT; 
}

void turnOnLED(int led){
    if(led == 1){
        RUNLED = ON;
        STOPLED = OFF;
    }
    else if (led == 2){
        RUNLED = OFF;
        STOPLED = ON;
    }
}