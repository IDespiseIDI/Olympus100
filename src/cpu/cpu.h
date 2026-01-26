#pragma once
#include <stdint.h>
#include "globalcpu.h"
/* void NOP();
void QITZ();
void QITE(int8_t error);
void JMP(int8_t hb, int8_t lb);
void JSR(int8_t hb, int8_t lb);
void ABA(int8_t hb, int8_t lb);
void RET();
void SETX(int8_t val);
void ADDX(int8_t addend); //had to look the name of that up. shame on me.
void SUBX(int8_t subend); //(winging it here) I have a college level education in math (not a degree... YET) and I had to look that up!
void WRTX(int8_t hb, int8_t lb);
void REDX(int8_t hb, int8_t lb);
void CHXE(int8_t hb, int8_t lb);
void CHXI(int8_t hb, int8_t lb); //I'm still thinking about that
// void NOPX(); //finished X primary register operations. lets actually not include specific NOP codes
void SETY(int8_t val); //should just be able to copy-paste for the Y-register primary commands
void ADDY(int8_t addend); 
void SUBY(int8_t subend); 
void WRTY(int8_t hb, int8_t lb);
void REDY(int8_t hb, int8_t lb);
void CHYE(int8_t hb, int8_t lb);
void CHYI(int8_t hb, int8_t lb);
// void NOPY(); //all good.
void SETA(int8_t val); //A register commands
void SUBA(int8_t subend); 
void WRTA(int8_t hb, int8_t lb);
void REDA(int8_t hb, int8_t lb);
void CHAE(int8_t hb, int8_t lb);
void CHAI(int8_t hb, int8_t lb);
// void NOPA(); //all register primary commands done.
void XTOY();
void XTOA();
void YTOA();
void XEQY();
void XIQY(); //X IneQual Y
void XEQA();
void XIQA();
void YEQA();
void YIQA();
void XSWY();
void XSWA();
void YSWA();
void YIQX();
void AIQX();
void AIQY();
// void NOPI();
void WAIT();
void UTLX(); //User Text Length X
void UTLY();
void UTLA();
void RDLX(int8_t hb, int8_t lb); //ReaD Length X
void RDLY(int8_t hb, int8_t lb);
void RDLA(int8_t hb, int8_t lb);
// void NOPU();
void PRTX(int8_t hb, int8_t lb); //PRinT length X
void PRTY(int8_t hb, int8_t lb);
void PRTA(int8_t hb, int8_t lb);
void PRTB();
void DAL1(int8_t hb); //Disk A Load 1
void DAL2(int8_t hb);
void DAL3(int8_t hb);
void DAL4(int8_t hb);
void DBL1(int8_t hb);
void DBL2(int8_t hb);
void DBS1(int8_t hb);
void DBS2(int8_t hb);
void DMPM(int8_t hb, int8_t lb);
void DMPI();
void DMPS();
void DMPV();
void ADDS(int8_t hb, int8_t lb);
void SETS(int8_t hb);
void SXIN(int8_t hb, int8_t lb);
void SYIN(int8_t hb, int8_t lb);
void SAIN(int8_t hb, int8_t lb);
void STKX();
void STKY();
void STKA();
void ICRX();
void DCRX();
void INCX(int8_t hb, int8_t lb);
void DECX(int8_t hb, int8_t lb);
void ICRY();
void DCRY();
void INCY(int8_t hb, int8_t lb);
void DECY(int8_t hb, int8_t lb);
void ICRA();
void DCRA();
void INCA(int8_t hb, int8_t lb);
void DECA(int8_t hb, int8_t lb);
void XADY();
void XADA();
void YADX();
void YADA();
void AADX();
void AADY();
void XSBY();
void XSBA();
void YSBX();
void YSBA();
void ASBX();
void ASBY();
void ALLX();
void ALLY();
void ALLA();
void IPCX(int8_t hb);
void IPCY(int8_t hb);
void IPCA(int8_t hb);
void NLXS(int8_t hb, int8_t lb);
void NLYS(int8_t hb, int8_t lb);
void NLAS(int8_t hb, int8_t lb);
void SDL1(int8_t hb);
void SDL2(int8_t hb);
void SDL3(int8_t hb);
void SDLB(int8_t hb);
void SDSB(int8_t hb);
void DMPA();
void DMPB(); */
//This didn't work. I will instead put the opcodes themselves before opcode() in opcode.cpp
