// ******************************************************************************************* //
//
// File:         lab1p1.c
// Date:         
// Authors:      
//
// Description: Part 1 for lab 1
// ******************************************************************************************* //

#include <xc.h>
#include <sys/attribs.h>
#include "interrupt.h"
#include "timer.h"
#include "config.h"
#include "lcd.h"
#include "keypad.h"



#define press 0
#define release 1
#define running1 1
#define running2 2

#define COL1 PORTEbits.RE5
#define COL2 PORTEbits.RE7
#define COL3 PORTEbits.RE6



typedef enum stateTypeEnum {
    Wait, Scan, Print, MoveCursor, debounce1, debounce2
} stateType;

volatile stateType state;
volatile long int time = 0;
volatile const char*print;
/* Please note that the configuration file has changed from lab 0.
 * the oscillator is now of a different frequency.
 */
volatile int key = -1;
volatile int count = 0;

int main(void)
{
    SYSTEMConfigPerformance(10000000); //10MHZ
   initTimer2();
   initLCD();
   initKeypad();

  printStringLCD("Part1");
   enableInterrupts();
    enableKeyboardInterrupt();
   
   
   moveCursorLCD(0,0);
    state = Wait;

     while (1) 
     {
       // testLCD();
         
     switch (state) {
            case Wait:
                break;

            case Scan:
                key = scanKeypad();
                state = MoveCursor;
                break;
                
            case MoveCursor:
                if(count == 0) moveCursorLCD(0,0);
                else if (count == 16) moveCursorLCD(1,0);
                state = Print;
                break;
                
            case debounce1:
                delayUs(1000);
                state = Scan;
                break;
                
            case debounce2:
                delayUs(1000);
                state = MoveCursor;
                break;

            case Print:
                delayUs(1000);
                if(key == 0) {printCharLCD('0'); count++;}
                else if(key == 1) {printCharLCD('1'); count++;}
                else if(key == 2) {printCharLCD('2'); count++;}
                else if(key == 3) {printCharLCD('3');count++;}
                else if(key == 4) {printCharLCD('4');count++;}
                else if(key == 5) {printCharLCD('5');count++;}
                else if(key == 6) {printCharLCD('6');count++;}
                else if(key == 7) {printCharLCD('7');count++;}
                else if(key == 8) {printCharLCD('8');count++;}
                else if(key == 9) {printCharLCD('9');count++;}
                else if(key == 10) {printCharLCD('*');count++;}
                else if(key == 12) {printCharLCD('#');count++;}
               // else if(key == -1) printCharLCD(219);
                state = Wait;
                break;

        }
    }
    
    return 0;
}



void __ISR(_CHANGE_NOTICE_VECTOR, IPL7SRS) _CNInterrupt(void) {
    int dummy1;
    int dummy2;
    int dummy3;
    
    IFS1bits.CNEIF = 0;

    dummy1 = COL1;
    dummy2 = COL2;
    dummy3 = COL3;

    

    
    if(state == Wait && (COL1==press||COL2==press||COL3==press)){
        //count ++;
        if(count ==32) count = 0;
        
    }
    
    if (state == Wait) state = debounce1;
    else if (state == Scan) state = debounce2;
}