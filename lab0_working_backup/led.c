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
    TRISGbits.TRISG12 = OUTPUT;
    TRISGbits.TRISG14 = OUTPUT;
    //TRISGbits.TRISD2 = OUTPUT;
}

void turnOnLED(int led){
    if(led == 1){
        LATGbits.LATG12 = ON;
        LATGbits.LATG14 = OFF;
        //LATDbits.LATD2 = OFF;
    }
    else if (led == 2){
        LATGbits.LATG12 = OFF;
        LATGbits.LATG14 = ON;
        //LATDbits.LATD2 = OFF;
    }
    //else if (led == 3){
     //   LATDbits.LATD0 = OFF;
      //  LATDbits.LATD1 = OFF;
       // LATDbits.LATD2 = ON;
    //}
    
}