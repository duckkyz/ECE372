/*
 * File:   leds.c
 * Authors: Ben Johnson
 *
 * Created on Feb 5, 2016
 */

#include <xc.h>
#include "leds.h"

#define OUTPUT 0
#define INPUT 1

#define ODC_RUN ODCGbits.ODCG12
#define ODC_STOP ODCGbits.ODCG14

#define OFF 0
#define ON 1

<<<<<<< HEAD
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
=======
#define RUNLED_TRIS TRISGbits.TRISG12
#define STOPLED_TRIS TRISGbits.TRISG14

#define RUNLED LATGbits.LATG12
#define STOPLED LATGbits.LATG14

void initLEDs(){
    RUNLED_TRIS = OUTPUT;
    STOPLED_TRIS = OUTPUT; 
    ODC_RUN = ON;
    ODC_STOP = ON;
>>>>>>> Lab0/master
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