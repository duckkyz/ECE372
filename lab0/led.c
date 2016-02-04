<<<<<<< HEAD
/* 
 * File:   led.c
 * Author: Ben Johnson
 *
 * Created on February 1, 2016, 5:17 PM
 */

#include <xc.h>
#include "led.h"

#define OUTPUT 0
#define INPUT 1

#define OFF 0
#define ON 1

void initLEDs(){
    TRISDbits.TRISD0 = OUTPUT;
    TRISDbits.TRISD1 = OUTPUT;
    TRISDbits.TRISD2 = OUTPUT;
}

void turnOnLED(int led){
    if(led == 1){
        LATDbits.LATD0 = ON;
        LATDbits.LATD1 = OFF;
        LATDbits.LATD2 = OFF;
    }
    else if (led == 2){
        LATDbits.LATD0 = OFF;
        LATDbits.LATD1 = ON;
        LATDbits.LATD2 = OFF;
    }
    else if (led == 3){
        LATDbits.LATD0 = OFF;
        LATDbits.LATD1 = OFF;
        LATDbits.LATD2 = ON;
    }
    
=======
/* 
 * File:   led.c
 * Author: Ben Johnson
 *
 * Created on February 1, 2016, 5:17 PM
 */

#include <xc.h>
#include "led.h"

#define OUTPUT 0
#define INPUT 1

#define OFF 0
#define ON 1

void initLEDs(){
    TRISDbits.TRISD0 = OUTPUT;
    TRISDbits.TRISD1 = OUTPUT;
    TRISDbits.TRISD2 = OUTPUT;
}

void turnOnLED(int led){
    if(led == 1){
        LATDbits.LATD0 = ON;
        LATDbits.LATD1 = OFF;
        LATDbits.LATD2 = OFF;
    }
    else if (led == 2){
        LATDbits.LATD0 = OFF;
        LATDbits.LATD1 = ON;
        LATDbits.LATD2 = OFF;
    }
    else if (led == 3){
        LATDbits.LATD0 = OFF;
        LATDbits.LATD1 = OFF;
        LATDbits.LATD2 = ON;
    }
    
>>>>>>> 9f1d9e5ff0557f20fe22e0bd26c382024f0ef8fc
}