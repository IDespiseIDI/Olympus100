#pragma once
#ifndef GLOBALRAM
#define GLOBALRAM
#include <stdint.h>
extern uint8_t memory[65536]; //there's really not a better way to do this? Wow!
//why is this not working? how could memory possibly be declared twice? 
//Oh... I didn't put extern there at first
#endif