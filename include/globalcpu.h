#pragma once
#include <string>
#include <stdint.h>
#include <fstream>
/*this is for declaring cpu functions used across the entire program*/
extern uint8_t xreg; //X register
extern uint8_t yreg; //Y register
extern uint8_t areg; //A register
extern uint16_t stack[256]; //stack
extern uint16_t pcounter; //program counter
extern uint8_t stackpointer; //stack pointer doesn't need to be anything greater than 256, it's just function calls, right? ...right?
void opcode(uint8_t code, uint8_t arg1, uint8_t arg2);
extern bool quit;