#pragma once
#include <stdint.h>
#include "globalcpu.h"
#include "string.h"
#define m2op int hb, int lb
#define m1op int hb
#define mcs stack[stackpointer]
#define m16 (hb * 256) + lb
uint8_t xreg = 0; //X register
uint8_t yreg = 0; //Y register
uint8_t areg = 0; //A register
uint8_t *lreg; //Loaded register
uint16_t stack[256]; //stack
uint16_t pcounter = 0; //program counter
uint8_t stackpointer = 0; 
uint8_t das[4]; //disk a sectors loaded
uint8_t dbs[2]; //disk b sectors loaded
uint16_t dp = 0; //data pointer