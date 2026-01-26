#pragma once
#include <stdint.h>
uint8_t firmware[] = {
    2, 0, 228, //JMP 00E4
    //Strings
    79, 108, 121, 109, 112, 117, 115, 32, 49, 48, 48, //"Olympus 100" starting at 0003
    69, 114, 114, 111, 114, 33, 32,                 //"Error!
    65, 32, 114, 101, 97, 100, 45,                  // A read-
    111, 110, 108, 121, 32, 100, 105, 115, 107, 32, // only disk
    105, 115, 32, 105, 110, 32, 68, 65, 84, 65, 33, // is in DATA!" starting at 000E 
    87, 65, 82, 78, 73, 78, 71, 33, 32,                      //"WARNING!
    68, 97, 116, 97, 32, 100, 105, 115, 107, 32,             // Data disk
    105, 110, 32, 80, 82, 71, 77, 33, 32,                    // in PRGM!
    84, 121, 112, 101, 32, 34, 67, 79, 80, 89, 34, 32,       // Type \"COPY\"
    116, 111, 32, 69, 82, 65, 83, 69, 32, 68, 65, 84, 65, 32,// to ERASE DATA     
    97, 110, 100, 32, 114, 101, 112, 108, 97, 99, 101, 32,   // and replace
    119, 105, 116, 104, 32, 80, 82, 71, 77, 46,              // with PRGM." starting at 0031
    67, 111, 112, 121, 105, 110, 103, 46, 46, 46, //"Copying..." starting at 007D
    68, 111, 110, 101, 33, //"Done!" starting at 0087
    //Functions
    //008C
    6, 35, //SETX 23
    110, 0, 14, //NLXS 000F
    1, 1, //QITE 01
    //0093
    6, 0, //SETX 00
    14, 0, //SETY 00
    22, 0, //SETA 00
    2, 128, 0, //JMP 8000
    //009C
    9, 0, 0, //WRTX 0000
    5, //RET
    //00A0
    10, 0, 0, //REDX 0000
    5, //RET
    //00A4
    17, 0, 157, //WRTY 009D
    25, 0, 158, //WRTA 009E
    25, 0, 162, //WRTA 00A2
    15, 64, //ADDY 40
    17, 0, 161, //WRTY 00A1
    16, 64, //SUBY 40 
    3, 0, 160, //JSR 00A0
    3, 0, 156, //JSR 009C
    255, //NOP
    5, //RET
    //00BC
    22, 0, //SETA 00
    3, 0, 164, //JSR 00A4
    27, 0, 186, //CHAE 00BA
    5, 255, 255, //RET NOP NOP
    86, //ICRA
    123, 10,  //JMPB 0A 
    255, //NOP
    //00CB
    14, 64, //SETY 40
    3, 0, 188, //JSR 00BC
    19, 0, 224, //CHYE 00E0
    5, 255, 255, //RET NOP NOP
    82, //ICRY
    123, 10, //JMPB 0A
    255, //NOP
    //00DA
    114, 0, //SDL1 00
    5, //RET
    //00DD
    119, 0, //SDSB 00
    5, //RET
    //Heap
    127, //7F at 00E0
    8, //08 at 00E1
    0, //00 at 00E2
    14, //0F at 00E3
    //Main at 00E4
    6, 11, //SETX 0B
    14, 2, //SETY 02
    110, 0, 3, //NLXS 00 03
    62, 0, //DBL1 00
    19, 64, 0, //CHYE 4000
    2, 0, 140, //JMP 008C
    58, 0, //DAL1 00
    19, 128, 0, //CHYE 8000
    2, 0, 147, //JMP 0093
    6, 76, //SETX 004C
    110, 0, 49, //NLXS 0031
    106, 4, //IPCX 04
    50, 63, 252, //RDLX 3FFC
    14, 67, //SETY 43
    10, 63, 252, //REDX 3FFC
    33, //XEQY
    122, 5, //JMPF 05
    2, 0, 145, //JMP 0091   
    14, 79, //SETY 44
    10, 63, 253, //REDX 3FFD
    33, //XEQY
    122, 5, //JMPF 05
    2, 0, 145, //JMP 0091
    14, 80, //SETY 45
    10, 63, 254, //REDX 3FFE
    33, //XEQY
    122, 5, //JMPF 05
    2, 0, 145, //JMP 0091
    14, 89, //SETY 59
    10, 63, 255, //REDX 3FFF
    33, //XEQY
    122, 5, //JMPF 05
    2, 0, 145, //JMP 0091
    6, 10, //SETX 0A
    110, 0, 125, //NLXS 007D
    6, 0, //SETX 00
    9, 0, 219, //WRTX 00DB  I'm not proud of this, these 7 lines of
    9, 0, 222, //WRTX 00DE  code are redundant. We do not need them
    3, 0, 218, //JSR 00DA   except for the fact that removing them causes
    3, 0, 221, //JSR 00DD   writes to disk b to be offset by 8192 bytes
    9, 0, 226, //WRTX 00E2  times the number of times we increment X 
    3, 0, 203, //JSR 00CB   before jumping. What a horrible world to
    10, 0, 226, //REDX 00E2 have to do this in.
    9, 0, 219, //WRTX 00DB
    9, 0, 222, //WRTX 00DE
    3, 0, 218, //JSR 00DA
    3, 0, 221, //JSR 00DD
    9, 0, 226, //WRTX 00E2
    3, 0, 203, //JSR 00CB
    10, 0, 226, //REDX 00E2
    11, 0, 227, //CHXE 00E3
    0, 255, 255, //QITZ NOP NOP
    78, //ICRX
    78, //ICRX
    123, 29 //JMPB 1D
};
/*
 A couple of things to learn from this:
 1. I'm not done writing opcodes (currently at $79)
 2. place heap (I'm calling it that. Got a problem?)
    before everything else.
 3. Jump to main, assets and functions, main, is a
    perfect order for how to do this.

 */
//UPDATE 1/26/2026: I have added opcodes $7A and $7B. No, I'm not writing an opcode to copy sectors of RAM.