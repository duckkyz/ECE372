#include <xc.h>
#include <sys/attribs.h>
#include "switch.h"
#include "timer.h"
#include "led.h"
#include "interrupt.h"
#include "config.h"

#define OUTPUT 0
#define INPUT 1

#define PRESS 0
#define RELEASE 1

#define SW1 PORTDbits.RD6
//TODO: Define states of the state machine
typedef enum stateTypeEnum{
    led1, led2, led3, wait, wait2, debouncePress, debounceRelease, debounceRelease2
} stateType;

volatile stateType state;
volatile stateType lastLED;
volatile int direction;


int main() {
    
    //This function is necessary to use interrupts. 
    enableInterrupts();
    
    //TODO: Write each initialization function
    initSwitch1();
    initLEDs();
    initTimer2();
    initTimer1();
    state = led1;
    
    while(1)
    {
        switch(state)
        {
            case led1:
                turnOnLED(1);
                lastLED = led1;
                state = wait;
                break;
            case led2:
                turnOnLED(2);  
                lastLED = led2;
                state = wait;
                break;
            case led3:
                turnOnLED(3);   
                lastLED = led3;
                state = wait;
                break;
            case wait:
                if(SW1 == PRESS)
                    state = debouncePress;
                TMR1 = 0;
                T1CONbits.ON = 0;              //turn on timer                
                break;
            case wait2:
                if(SW1 == RELEASE)           //wait for flag raise
                    state = debounceRelease;
                            T1CONbits.TON = 1;
                break;
            case debouncePress:
                delayMs(5);
                state = wait2;
                break;
            case debounceRelease:
                delayMs(5);
                state = debounceRelease2;
                break;           
            case debounceRelease2:
                if(direction==0)
                {
                    if(lastLED==led1)
                        state = led2;
                    else if(lastLED==led2)
                        state = led3;
                    else if(lastLED==led3)
                        state = led1;
                }
                else if(direction==1)
                {
                    if(lastLED==led1)
                        state = led3;
                    else if(lastLED==led2)
                        state = led1;
                    else if(lastLED==led3)
                        state = led2;
                }
                direction = 0;
                break; 
        }
        
    }
    
    return 0;
}



void __ISR(_TIMER_1_VECTOR, IPL3SRS) _T1Interrupt()
{
    IFS0bits.T1IF = 0;//flag down
    IFS0bits.T2IF = 0;//flag down
    T1CONbits.TON = 0;     
    direction = 1;
    state = wait2;
}