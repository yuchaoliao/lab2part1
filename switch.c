/*
 * File:   switch.c
 * Author: Garrett
 *
 * Created on September 19, 2015, 10:46 AM
 */
#include <xc.h>

void initSW2(){
    //TODO: Initialize the appropriate pins to work with the external switch using a
    //change notification interrupt.
    TRISGbits.TRISG12 = 1;// Enable input for switch
    CNCONGbits.ON = 1;      // Turn on CN device
    CNENGbits.CNIEG13 = 1;
    IEC1bits.CNGIE = 1;
    IFS1bits.CNGIF = 0;  //flag down
   
    CNPUGbits.CNPUG13 = 1; // enable pull up resistor
    
}


void initSW1(){
    TRISDbits.TRISD6 = 1;// Enable input for switch
    CNCONDbits.ON = 1;       // Turn on CN device
    IPC8bits.CNIP = 7;
    CNENDbits.CNIED6 = 1;       // Enable CN interrupt for pin
    IEC1bits.CNDIE = 1;         // Enable overall CN Interrupt
    IFS1bits.CNDIF = 0;         // Put Interrupt flag down
    
    CNPUDbits.CNPUD6 = 1;// Enable Internal Pull-up resistor
    
}
