#pragma once
#include <stdint.h>
#include <stdio.h>
/*this is for declaring cpu functions used across the entire program*/
extern uint8_t xreg; //X register
extern uint8_t yreg; //Y register
extern uint8_t areg; //A register
extern uint16_t *stack; //stack
extern uint8_t* pcounter; //program counter
extern uint16_t* stackpointer; //stack pointer doesn't need to be anything greater than 256, it's just function calls, right? ...right?
extern uint8_t* dp; //data pointer
extern uint8_t *lreg; //loaded register
extern uint16_t* memaddr; //pointer to streamline getting a memory address instead of casting and addition
void opcode();
extern int quit;