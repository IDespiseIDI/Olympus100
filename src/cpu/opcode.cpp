#include "cpu.h"
#include "globalcpu.h"
#include "globalram.h"
#include "globalui.h"
#include "globaldisk.h"
#include <iostream>
#include <fstream>
/*macros I thought of while programing the opcodes, 
but after implementing them in the switch statement*/
#define m2op int hb, int lb
#define m1op int hb
#define mcs stack[stackpointer]
#define m16 (hb * 256) + lb
uint8_t xreg; //X register
uint8_t yreg; //Y register
uint8_t areg; //A register
uint16_t stack[256]; //stack
uint16_t pcounter; //program counter
uint8_t stackpointer; 
uint8_t das[4];
uint8_t dbs[2];
// #define TRACE
void NOP() {
    return;
}
void QITZ() {
    quit = true;
    return;
}
void QITE(m1op) {
    std::cout << "An unhandled exception has occured." << std::endl << "Error: " << (int)hb << std::endl;
    quit = true;
    return;
}
void JMP(m2op) {
    pcounter = (hb * 256) + lb;
    return;
}
void JSR(m2op) {
    stack[stackpointer] = pcounter + 3;
    stackpointer++;
    pcounter = (hb * 256) + lb;
    return;
}
void ABA(m2op) {
    stackpointer--;
    stack[stackpointer] = 0;
    pcounter = (hb * 256) + lb;
    return;
}
void RET() {
    stackpointer--;
    pcounter = mcs;
    mcs = 0;
    return;
}
void SETX(m1op) {
    xreg = hb;
    return;
}
void ADDX(m1op) {
    xreg += hb;
    return;
}
void SUBX(m1op) {
    xreg -= hb;
    return;
}
void WRTX(m2op) {
    if (m16 < 32768) {
        memory[m16] = xreg;
    }
    return;
}
void REDX(m2op) {
    xreg = memory[m16];
    return;
}
void CHXE(m2op) {
    if(xreg != memory[m16]) {
        pcounter += 3;
    }
    return;
}
void CHXI(m2op) {
    if(xreg < memory[m16]) {
        pcounter += 3;
    }
    return;
}
void SETY(m1op) {
    yreg = hb;
    return;
}
void ADDY(m1op) {
    yreg += hb;
    return;
}
void SUBY(m1op) {
    yreg -= hb;
    return;
}
void WRTY(m2op) {
    if (m16 < 32768) {
        memory[m16] = yreg;
    }
    return;
}
void REDY(m2op) {
    yreg = memory[m16];
    return;
}
void CHYE(m2op) {
    if(yreg != memory[m16]) {
        pcounter += 3;
    }
    return;
}
void CHYI(m2op) {
    if(yreg < memory[m16]) {
        pcounter += 3;
    }
    return;
}
void SETA(m1op) {
    areg = hb;
    return;
}
void ADDA(m1op) {
    areg += hb;
    return;
}
void SUBA(m1op) {
    areg -= hb;
    return;
}
void WRTA(m2op) {
    if (m16 < 32768) {
        memory[m16] = areg;
    }
    return;
}
void REDA(m2op) {
    areg = memory[m16];
    return;
}
void CHAE(m2op) {
    if(areg != memory[m16]) {
        pcounter += 3;
    }
    return;
}
void CHAI(m2op) {
    if(areg < memory[m16]) {
        pcounter += 3;
    }
    return;
}
void XTOY() {
    xreg = yreg;
    return;
}
void XTOA() {
    xreg = areg;
    return;
}
void YTOA() {
    yreg = areg;
    return;
}
void XEQY() {
    if (xreg != yreg) {
        pcounter += 3;
    }
    return;
}
void XIQY() {
    if (xreg < yreg) {
        pcounter += 3;
    }
    return;
}
void XEQA() {
    if (xreg != areg) {
        pcounter += 3;
    }
    return;
}
void XIQA() {
    if (xreg < areg) {
        pcounter += 3;
    }
    return;
}
void YEQA() {
    if (yreg != areg) {
        pcounter += 3;
    }
    return;
}
void YIQA() {
    if (yreg < areg) {
        pcounter += 3;
    }
    return;
}
void XSWY() {
    mcs = xreg;
    xreg = yreg;
    yreg = mcs;
    mcs = 0;
    return; //Use the stack to swap register values! Is that clever or what? The current stack position should be 0 between opcodes anyway.
}
void XSWA() {
    mcs = xreg;
    xreg = areg;
    areg = mcs;
    mcs = 0;
    return;
}
void YSWA() {
    mcs = yreg;
    yreg = areg;
    areg = mcs;
    mcs = 0;
    return;
}
void YIQX() {
    if (yreg < xreg) {
        pcounter += 3;
    }
    return;
}
void AIQX() {
    if (areg < xreg) {
        pcounter += 3;
    }
    return;
}
void AIQY() {
    if (areg < yreg) {
        pcounter += 3;
    }
    return;
}
void WAIT() {
    std::cin >> strin;
    return;
}
void UTLX() {
    xreg = strin.length();
}
void UTLY() {
    yreg = strin.length();
}
void UTLA() {
    areg = strin.length();
}
void RDLX(m2op) {
    for(uint8_t i=0; i < xreg; i++) {
        memory[m16 + i] = (uint8_t)strin[i];
    }
    return;
}
void RDLY(m2op) {
    for(uint8_t i=0; i < yreg; i++) {
        memory[m16 + i] = (uint8_t)strin[i];
    }
    return;
}
void RDLA(m2op) {
    for(uint8_t i=0; i < areg; i++) {
        memory[m16 + i] = (uint8_t)strin[i];
    }
    return;
}
void PRTX(m2op) {
    for(uint8_t i=0; i < xreg; i++) {
        std::cout << (char)memory[m16 + i];
    }
    return;
}
void PRTY(m2op) {
    for(uint8_t i=0; i < yreg; i++) {
        std::cout << (char)memory[m16 + i];
    }
    return;
}
void PRTA(m2op) {
    for(uint8_t i=0; i < areg; i++) {
        std::cout << (char)memory[m16 + i];
    }
    return;
}
void PRTB() {
    std::cout << std::endl;
    return;
}
void DAL1(m1op) {
    diska.seekg((int)hb * 8192, std::ios::beg);
    diska.read(reinterpret_cast<char*>(&memory[32768]), 8192);
    das[0] = hb;
    return;
}
void DAL2(m1op) {
    diska.seekg((int)hb * 8192, std::ios::beg);
    diska.read(reinterpret_cast<char*>(&memory[40960]), 8192);
    das[1] = hb;
    return;
}
void DAL3(m1op) {
    diska.seekg((int)hb * 8192, std::ios::beg);
    diska.read(reinterpret_cast<char*>(&memory[49152]), 8192);
    das[2] = hb;
    return;
}
void DAL4(m1op) {
    diska.seekg((int)hb * 8192, std::ios::beg);
    diska.read(reinterpret_cast<char*>(&memory[57344]), 8192);
    das[3] = hb;
    return;
}
void DBL1(m1op) {
    diskb.seekg((int)hb * 8192, std::ios::beg);
    diskb.read(reinterpret_cast<char*>(&memory[16384]), 8192);
    dbs[0] = hb;
    return;
}
void DBL2(m1op) {
    diskb.seekg((int)hb * 8192, std::ios::beg);
    diskb.read(reinterpret_cast<char*>(&memory[24576]), 8192);
    dbs[1] = hb;
    return;
}
void DBS1(m1op) {
    if (hb > 15) return;
    diskb.seekp(hb * 8192, std::ios::beg);
    diskb.write(reinterpret_cast<const char*>(&memory[16384]), 8192);
    diskb.flush();
    return;
}
void DBS2(m1op) {
    if (hb > 15) return;
    diskb.seekp(hb * 8192, std::ios::beg);
    diskb.write(reinterpret_cast<const char*>(&memory[24576]), 8192);
    diskb.flush();
    return;
}
void DMPM(m2op) {
    for (int i = 0; i < 256; i++) {
        std::cout << memory[m16 + i];
    }
    std::cout << std::endl;
    return;
}
void DMPI() {
    for (int i = 0; i < 256; i++) {
        std::cout << (int)memory[pcounter - 256 + i] << " ";
    }
    std::cout << std::endl;
    return;
}
void DMPS() {
    for (int i = 0; i < 256; i++) {
        std::cout << stack[i];
    }
    std::cout << std::endl;
    return;
}
void DMPV() {
    std::cout << xreg << yreg << areg << stackpointer << pcounter << std::endl;
    return;
}
void ADDS(m2op) {
    mcs = m16;
    stackpointer++;
    return;
}
void SETS(m1op) {
    stackpointer = hb;
    return;
}
void SXIN(m2op) {
    stack[xreg] = m16;
    return;
}
void SYIN(m2op) {
    stack[yreg] = m16;
    return;
}
void SAIN(m2op) {
    stack[areg] = m16;
    return;
}
void STKX() {
    stackpointer = xreg;
    return;
}
void STKY() {
    stackpointer = yreg;
    return;
}
void STKA() {
    stackpointer = areg;
    return;
}
void ICRX() {
    xreg++;
    return;
}
void DCRX() {
    xreg--;
    return;
}
void INCX(m2op) {
    xreg += memory[m16];
    return;
}
void DECX(m2op) {
    xreg -= memory[m16];
    return;
}
void ICRY() {
    yreg++;
    return;
}
void DCRY() {
    yreg--;
    return;
}
void INCY(m2op) {
    yreg += memory[m16];
    return;
}
void DECY(m2op) {
    yreg -= memory[m16];
    return;
}
void ICRA() {
    areg++;
    return;
}
void DCRA() {
    areg--;
    return;
}
void INCA(m2op) {
    areg += memory[m16];
    return;
}
void DECA(m2op) {
    areg -= memory[m16];
    return;
}
void XADY() {
    xreg += yreg;
    return;
}
void XADA() {
    xreg += areg;
    return;
}
void YADX() {
    yreg += xreg;
    return;
}
void YADA() {
    yreg += areg;
    return;
}
void AADX() {
    areg += xreg;
    return;
}
void AADY() {
    areg = yreg;
    return;
}
void XSBY() {
    xreg -= yreg;
    return;
}
void XSBA() {
    xreg -= areg;
    return;
}
void YSBX() {
    yreg -= xreg;
    return;
}
void YSBA() {
    yreg -= areg;
    return;
}
void ASBX() {
    areg -= xreg;
    return;
}
void ASBY() {
    areg -= yreg;
    return;
}
void ALLX() {
    yreg = xreg;
    areg = xreg;
    return;
}
void ALLY() {
    xreg = yreg;
    areg = yreg;
    return;
}
void ALLA() {
    xreg = areg;
    yreg = areg;
    return;
}
void IPCX(m1op) {
    std::cin >> strin;
    xreg = strin.length();
    if (xreg > hb) {
        xreg = hb;
    }
    return;
}
void IPCY(m1op) {
    std::cin >> strin;
    yreg = strin.length();
    if (yreg > hb) {
        yreg = hb;
    }
    return;
}
void IPCA(m1op) {
    std::cin >> strin;
    areg = strin.length();
    if (areg > hb) {
        areg = hb;
    }
    return;
}
void NLXS(m2op) {
    std::cout << std::endl;
    for(uint8_t i=0; i < xreg; i++) {
        std::cout << (char)memory[m16 + i];
    }
    std::cout << std::endl;
    return;
}
void NLYS(m2op) {
    std::cout << std::endl;
    for(uint8_t i=0; i < yreg; i++) {
        std::cout << (char)memory[m16 + i];
    }
    std::cout << std::endl;
    return;
}
void NLAS(m2op) {
    std::cout << std::endl;
    for(uint8_t i=0; i < areg; i++) {
        std::cout << (char)memory[m16 + i];
    }
    std::cout << std::endl;
    return;
}
void SDL1(m1op) {
    diska.seekg(hb * 8192, std::ios::beg);
    diska.read(reinterpret_cast<char*>(&memory[32768]), 16384);
    return;
}
void SDL2(m1op) {
    diska.seekg(hb * 8192, std::ios::beg);
    diska.read(reinterpret_cast<char*>(&memory[40960]), 16384);
    return;
}
void SDL3(m1op) {
    diska.seekg(hb * 8192, std::ios::beg);
    diska.read(reinterpret_cast<char*>(&memory[49152]), 16384);
    return;
}
void SDLB(m1op) {
    diskb.seekg(hb * 8192, std::ios::beg);
    diskb.read(reinterpret_cast<char*>(&memory[16384]), 16384);
    return;
}
void SDSB(m1op) {
    if (hb > 14) return;
    diskb.seekp(hb * 8192, std::ios::beg);
    diskb.write(reinterpret_cast<const char*>(&memory[16384]), 16384);
    diskb.flush();
    return;
}
void DMPA() {
    for(int i = 0; i < 4; i++) {
        std::cout << das[i];
    }
    std::cout << std::endl;
    return;
}
void DMPB() {
    std::cout << dbs[0];
    std::cout << dbs[1];
    std::cout << std::endl;
    return;
}
void JMPF(m1op) {
    pcounter += hb;
    return;
}
void JMPB(m1op) {
    pcounter -= hb;
    return;
}
void opcode(uint8_t code, uint8_t arg1, uint8_t arg2) {
#ifdef TRACE  
    std::cout << "REGDEB: " << (int)xreg << " " << (int)yreg << " " << (int)areg << std::endl;
    std::cout << "DISKA: ";
    for (int i = 0; i < 8; i++) {
        std::cout << (int)memory[32768 + i] << " ";
    }
    std::cout << std::endl;
    std::cout << "DISKB: ";
    for (int i = 0; i < 8; i++) {
        std::cout << (int)memory[16384 + i] << " ";
    }
    std::cout << std::endl;
    std::cout << "DEBUG: " << static_cast<int>(code) << " " << static_cast<int>(arg1) << " " << static_cast<int>(arg2) << std::endl;
#endif

    switch (code) {
        case 0:
            QITZ();
            break;
        case 1:
            QITE(arg1);
            break;
        case 2:
            JMP(arg1, arg2);
// jump instructions do not update the program counter. that's just bad practice
            break;
        case 3:
            JSR(arg1, arg2);
            break;
        case 4:
            ABA(arg1, arg2);
            break;
        case 5:
            RET();
            break;
        case 6:
            SETX(arg1);
            pcounter += 2;
            break;
        case 7:
            ADDX(arg1);
            pcounter += 2;
            break;
        case 8:
            SUBX(arg1);
            pcounter += 2;
            break;
        case 9:
            WRTX(arg1, arg2);
            #ifdef TRACE
            std::cout << "DEBUG: X=" << (int)xreg << " written to address " << 256 * (int)arg1 + (int)arg2 << std::endl;
            #endif
            pcounter += 3;
            break;
        case 10:
            REDX(arg1, arg2);
            pcounter += 3;
            break;
        case 11:
            CHXE(arg1, arg2);
            pcounter += 3;
            break;
        case 12:
            CHXI(arg1, arg2);
            pcounter += 3;
            break;
        case 14:
            SETY(arg1);
            pcounter += 2;
            break;
        case 15:
            ADDY(arg1);
            pcounter += 2;
            break;
        case 16:
            SUBY(arg1);
            pcounter += 2;
            break;
        case 17:
            WRTY(arg1, arg2);
            pcounter += 3;
            break;
        case 18:
            REDY(arg1, arg2);
            pcounter += 3;
            break;
        case 19:
            CHYE(arg1, arg2);
            pcounter += 3;
            break;
        case 20:
            CHYI(arg1, arg2);
            pcounter += 3;
            break;
        case 22:
            SETA(arg1);
            pcounter += 2;
            break;
        case 23:
            ADDA(arg1);
            pcounter += 2;
            break;
        case 24:
            SUBA(arg1);
            pcounter += 2;
            break;
        case 25:
            WRTA(arg1, arg2);
            pcounter += 3;
            break;
        case 26:
            REDA(arg1, arg2);
            pcounter += 3;
            break;
        case 27:
            CHAE(arg1, arg2);
            pcounter += 3;
            break;
        case 28:
            CHAI(arg1, arg2);
            pcounter += 3;
            break;
        case 30:
            XTOY();
            pcounter++;
            break;
        case 31:
            XTOA();
            pcounter++;
            break;
        case 32:
            YTOA();
            pcounter++;
            break;
        case 33:
            XEQY();
            pcounter++;
            break;
        case 34:
            XIQY();
            pcounter++;
            break;
        case 35:
            XEQA();
            pcounter++;
            break;
        case 36:
            XIQA();
            pcounter++;
            break;
        case 37:
            YEQA();
            pcounter++;
            break;
        case 38:
            YIQA();
            pcounter++;
            break;
        case 39:
            XSWY();
            pcounter++;
            break;
        case 40:
            XSWA();
            pcounter++;
            break;
        case 41:
            YSWA();
            pcounter++;
            break;
        case 42:
            YIQX();
            pcounter++;
            break;
        case 43:
            AIQX();
            pcounter++;
            break;
        case 44:
            AIQY();
            pcounter++;
            break;
        case 46:
            WAIT();
            pcounter++;
            break;
        case 47:
            UTLX();
            pcounter++;
            break;
        case 48:
            UTLY();
            pcounter++;
            break;
        case 49:
            UTLA();
            pcounter++;
            break;
        case 50:
            RDLX(arg1, arg2);
            pcounter += 3;
            break;
        case 51:
            RDLY(arg1, arg2);
            pcounter += 3;
            break;
        case 52:
            RDLA(arg1, arg2);
            pcounter += 3;
            break;
        case 54:
            PRTX(arg1, arg2);
            pcounter += 3;
            break;
        case 55:
            PRTY(arg1, arg2);
            pcounter += 3;
            break;
        case 56:
            PRTA(arg1, arg2);
            pcounter += 3;
            break;
        case 57:
            PRTB();
            pcounter++;
            break;
        case 58:
            DAL1(arg1);
            pcounter += 2;
            break;
        case 59:
            DAL2(arg1);
            pcounter += 2;
            break;
        case 60:
            DAL3(arg1);
            pcounter += 2;
            break;
        case 61:
            DAL4(arg1);
            pcounter += 2;
            break;
        case 62:
            DBL1(arg1);
            pcounter += 2;
            break;
        case 63:
            DBL2(arg1);
            pcounter += 2;
            break;
        case 64:
            DBS1(arg1);
            pcounter += 2;
            break;
        case 65:
            DBS2(arg1);
            pcounter += 2;
            break;
        case 66:
            DMPM(arg1, arg2);
            pcounter += 3;
            break;
        case 67:
            DMPI();
            pcounter++;
            break;
        case 68:
            DMPS();
            pcounter++;
            break;
        case 69:
            DMPV();
            pcounter++;
            break;
        case 70:
            ADDS(arg1, arg2);
            pcounter += 3;
            break;
        case 71:
            SETS(arg1);
            pcounter += 2;
            break;
        case 72:
            SXIN(arg1, arg2);
            pcounter += 3;
            break;
        case 73:
            SYIN(arg1, arg2);
            pcounter += 3;
            break;  
        case 74:
            SAIN(arg1, arg2);
            pcounter += 3;
            break;
        case 75:
            STKX();
            pcounter++;
            break; 
        case 76:
            STKY();
            pcounter++;
            break; 
        case 77:
            STKA();
            pcounter++;
            break;
        case 78:
            ICRX();
            pcounter++;
            break;
        case 79:
            DCRX();
            pcounter++;
            break;
        case 80:
            INCX(arg1, arg2);
            pcounter += 3;
            break;
        case 81:
            DECX(arg1, arg2);
            pcounter += 3;
            break;
        case 82:
            ICRY();
            pcounter++;
            break;
        case 83:
            DCRY();
            pcounter++;
            break;
        case 84:
            INCY(arg1, arg2);
            pcounter += 3;
            break;
        case 85:
            DECY(arg1, arg2);
            pcounter += 3;
            break;
        case 86:
            ICRA();
            pcounter++;
            break;
        case 87:
            DCRA();
            pcounter++;
            break;
        case 88:
            INCA(arg1, arg2);
            pcounter += 3;
            break;
        case 89:
            DECA(arg1, arg2);
            pcounter += 3;
            break;
        case 90:
            XADY();
            pcounter++;
            break;
        case 91:
            XADA();
            pcounter++;
            break;
        case 92:
            YADX();
            pcounter++;
            break;
        case 93:
            YADA();
            pcounter++;
            break;
        case 94:
            AADX();
            pcounter++;
            break;
        case 95:
            AADY();
            pcounter++;
            break;
        case 96:
            XSBY();
            pcounter++;
            break;
        case 97:
            XSBA();
            pcounter++;
            break;
        case 98:
            YSBX();
            pcounter++;
            break;
        case 99:
            YSBA();
            pcounter++;
            break;
        case 100:
            ASBX();
            pcounter++;
            break;
        case 101:
            ASBY();
            pcounter++;
            break;
        case 102:
            ALLX();
            pcounter++;
            break;
        case 103:
            ALLY();
            pcounter++;
            break;
        case 104:
            ALLA();
            pcounter++;
            break;
        case 106:
            IPCX(arg1);
            pcounter += 2;
            break;
        case 107:
            IPCY(arg1);
            pcounter += 2;
            break;
        case 108:
            IPCA(arg1);
            pcounter += 2;
            break;
        case 110:
            NLXS(arg1, arg2);
            pcounter += 3;
            break;
        case 111:
            NLYS(arg1, arg2);
            pcounter += 3;
            break;
        case 112:
            NLAS(arg1, arg2);
            pcounter += 3;
            break;
        case 114:
            SDL1(arg1);
            pcounter += 2;
            break;
        case 115:
            SDL2(arg1);
            pcounter += 2;
            break;       
        case 116:
            SDL3(arg1);
            pcounter += 2;
            break;
        case 118:
            SDLB(arg1);
            pcounter += 2;
            break;
        case 119:
            SDSB(arg1);
            pcounter += 2;
            break;
        case 120:
            DMPA();
            pcounter++;
            break;
        case 121:
            DMPB();
            pcounter++;
            break;
        case 122:
            JMPF(arg1);
            break;
        case 123:
            JMPB(arg1);
            break;
        default:
            NOP();
            pcounter++;
            break;
    } 
}





