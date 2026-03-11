#pragma once
#include <stdint.h>
#include "globalcpu.h"
uint8_t xreg = 0; //X register
uint8_t yreg = 0; //Y register
uint8_t areg = 0; //A register
uint8_t* lreg = 0; //Loaded register
uint16_t* stack; //stack, separate from main RAM
uint8_t* pcounter; //program counter
uint16_t* stackpointer; 
uint8_t* dp; //data pointer
uint16_t* memaddr;