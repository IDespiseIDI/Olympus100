#pragma once
#include <stdint.h>
uint8_t firmware[] = {
    2, 0, 237, // JMP &mn
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
    //Functions starting at 008C
    //wp=*008C
    6, 35,  //SETX 23 
    110, 0, 14, //NLXS 000E
    1, 1, //QITE 01
    //rn=*0093
    6, 0, //SETX 00
    14, 0, //SETY 00
    22, 0, //SETA 00
    13, //LODX
    57, //PRTB
    2, 128, 0, //JMP 8000
    //cc=*009E
    163, //XTOD
    33, //XEQY
    5, //RET
    255, 255, //NOP NOP
    1, 2, //QITE 02
    //ca=*00A5
    152, //DSYA
    163, //XTOD
    16, 64, //SUBY 40
    152, //DSYA
    162, //DTOX
    15, 64, //ADDY 40
    128, 255, //CAEN FF
    5, //RET
    255, 255, //NOP NOP
    86, //ICRA
    2, 0, 165, //JMP &ca
    //cy=*00B6
    22, 0, //SETA 00
    3, 0, 165, //JSR &ca
    126, 191, //CYEN BF
    5, //RET
    255, 255, //NOP NOP
    82, //ICRY
    2, 0, 182, //JMP &cy
    //da=*00C4
    114, 0, //SDL1 sa=*00C5
    5, //RET
    //db=*00C7
    119, 0, //SDSB sb=*00C8
    5, //RET
    //dc=*00CA
    6, 5, //SETX 05
    110, 0, 135, //NLXS 0087
    0, //QITZ
    //cs=*00D0
    9, 0, 197, //WRTX &sa
    9, 0, 200, //WRTX &sb
    3, 0, 196, //JSR &da
    14, 128, //SETY 80
    3, 0, 182, //JSR &cy
    3, 0, 199, //JSR &db
    10, 0, 197, //REDX &sa
    124, 14, //CXEN 0E
    2, 0, 202, //JMP &dc
    7, 2, //ADDX 02
    2, 0, 208, //JMP &cs
    //mn=*00EB
    6, 11, //SETX 0A
    54, 0, 3, //PRTX 0003
    62, 0, //DBL1 00
    10, 64, 0, //REDX 4000
    124, 2, //CXEN 02
    2, 0, 140, //JMP &wp
    58, 0, //DAL1 00
    10, 128, 0, //REDX 8000
    124, 2, //CXEN 02
    2, 0, 147, //JMP &rn
    6, 76, //SETX 4C
    110, 0, 49, //NLXS 0031
    106, 4, //IPCX 04
    50, 63, 252, //RDLX 3FFC
    136, 63, 252, //SETD 3FFC
    14, 67, //SETY 43
    3, 0, 158, //JSR &cc
    132, //ICRD
    14, 79, //SETY 4F
    3, 0, 158, //JSR &cc
    132, //ICRD
    14, 80, //SETY 50
    3, 0, 158, //JSR &cc
    132, //ICRD
    14, 89, //SETY 59
    3, 0, 158, //JSR &cc
    6, 10, //SETX 0A
    110, 0, 125, //NLXS 007D
    6, 0, //SETX 00
    2, 0, 208, //JMP &cs
};