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

#define RUNLED_TRIS TRISGbits.TRISG12
#define STOPLED_TRIS TRISGbits.TRISG14

#define RUNLED LATGbits.LATG12
#define STOPLED LATGbits.LATG14

void initLEDs(){
    RUNLED_TRIS = OUTPUT;
    STOPLED_TRIS = OUTPUT; 
    ODC_RUN = ON;
    ODC_STOP = ON;
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