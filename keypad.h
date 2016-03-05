/* 
 * File:   keypad.h
 * Author: user
 *
 * Created on February 5, 2015, 11:42 AM
 */

#ifndef KEYPAD_H
#define	KEYPAD_H


void initKeypad(void);
int scanKeypad(void);
void enableKeyboardInterrupt(void);
void disableKeyboardInterrupt(void);

#endif	/* KEYPAD_H */

