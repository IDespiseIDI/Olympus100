#include "cpu.h"
#include "globalram.h"
#include "globalui.h"
#include "globaldisk.h"
#include <stdio.h>
#include <string.h>

uint8_t das[4]; //disk a sectors loaded
uint8_t dbs[2]; //disk b sectors loaded


void QITZ() {
    quit = 1;
    return;
}
void QITE() {
    printf("\nAn unhandled exception has occured. \n Error: %i \n", *(pcounter+1));
    quit = 1;
    return;
}
void JMP() {
    pcounter = *memaddr + memory;
    return;
}
void JSR() {
    *stackpointer = (pcounter-memory) + 3;
    stackpointer++;
    pcounter = *memaddr + memory;
    return;
}
void ABA() {
    stackpointer--;
    *stackpointer = 0;
    pcounter = *memaddr + memory;
    return;
}
void RET() {
    stackpointer--;
    pcounter = *stackpointer + memory;
    *stackpointer = 0;
    return;
}
void SETX() {
    xreg = *(pcounter+1);
    return;
}
void ADDX() {
    xreg += *(pcounter+1);
    return;
}
void SUBX() {
    xreg -= *(pcounter+1);
    return;
}
void WRTX() {
    memory[*memaddr] = xreg;
}
void REDX() {
    xreg = memory[*memaddr];
    return;
}
void CHXE() {
    if(xreg != memory[*memaddr]) {
        pcounter += 3;
    }
    return;
}
void CHXI() {
    if(xreg < memory[*memaddr]) {
        pcounter += 3;
    }
    return;
}
void LODX() {
    lreg = &xreg;
    return;
}
void SETY() {
    yreg = *(pcounter+1);
    return;
}
void ADDY() {
    yreg += *(pcounter+1);
    return;
}
void SUBY() {
    yreg -= *(pcounter+1);
    return;
}
void WRTY() {
    memory[*memaddr] = yreg;
    return;
}
void REDY() {
    yreg = memory[*memaddr];
    return;
}
void CHYE() {
    if(yreg != memory[*memaddr]) {
        pcounter += 3;
    }
    return;
}
void CHYI() {
    if(yreg < memory[*memaddr]) {
        pcounter += 3;
    }
    return;
}
void LODY() {
    lreg = &yreg;
    return;
}
void SETA() {
    areg = *(pcounter+1);
    return;
}
void ADDA() {
    areg += *(pcounter+1);
    return;
}
void SUBA() {
    areg -= *(pcounter+1);
    return;
}
void WRTA() {
    memory[*memaddr] = areg;
    return;
}
void REDA() {
    areg = memory[*memaddr];
    return;
}
void CHAE() {
    if(areg != memory[*memaddr]) {
        pcounter += 3;
    }
    return;
}
void CHAI() {
    if(areg < memory[*memaddr]) {
        pcounter += 3;
    }
    return;
}
void LODA() {
    lreg = &areg;
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
    *stackpointer = xreg;
    xreg = yreg;
    yreg = *stackpointer;
    *stackpointer = 0;
    return; //Use the stack to swap register values! Is that clever or what? The current stack position should be 0 between opcodes anyway.
}
void XSWA() {
    *stackpointer = xreg;
    xreg = areg;
    areg = *stackpointer;
    *stackpointer = 0;
    return;
}
void YSWA() {
    *stackpointer = yreg;
    yreg = areg;
    areg = *stackpointer;
    *stackpointer = 0;
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
    memset(strin, 0, 1);
    fgets(strin, 255, stdin);
    return;
}
void UTLX() {
    for (xreg = 0; strin[xreg] != NULL; xreg++) { //this is okay, right?

    }
    return;
}
void UTLY() {
    for (yreg = 0; strin[xreg] != NULL; xreg++) {

    }
    return;
}
void UTLA() {
    for (areg = 0; strin[xreg] != NULL; xreg++) {

    }
    return;
}
void RDLX() {
    for(uint8_t i=0; i < xreg; i++) {
        memory[*memaddr + i] = (uint8_t)strin[i];
    }
    return;
}
void RDLY() {
    for(uint8_t i=0; i < yreg; i++) {
        memory[*memaddr + i] = (uint8_t)strin[i];
    }
    return;
}
void RDLA() {
    for(uint8_t i=0; i < areg; i++) {
        memory[*memaddr + i] = (uint8_t)strin[i];
    }
    return;
}
void PRTX() {
    for(uint8_t i=0; i < xreg; i++) {
        printf("%c", memory[*memaddr + i]);
    }
    return;
}
void PRTY() {
    for(uint8_t i=0; i < yreg; i++) {
        printf("%c", memory[*memaddr + i]);
    }
    return;
}
void PRTA() {
    for(uint8_t i=0; i < areg; i++) {
        printf("%c", memory[*memaddr + i]);
    }
    return;
}
void PRTB() {
    printf("\n");
    return;
}
void DAL1() {
    fseek(diska, (int)*(pcounter+1) * 8192, SEEK_SET);
    fread(&memory[32768], sizeof(uint8_t), 8192 * sizeof(uint8_t), diska);
    das[0] = *(pcounter+1);
    return;
}
void DAL2() {
    fseek(diska, (int)*(pcounter+1) * 8192, SEEK_SET);
    fread(&memory[40960], sizeof(uint8_t), 8192 * sizeof(uint8_t), diska);
    das[1] = *(pcounter+1);
    return;
}
void DAL3() {
    fseek(diska, (int)*(pcounter+1) * 8192, SEEK_SET);
    fread(&memory[49152], sizeof(uint8_t), 8192 * sizeof(uint8_t), diska);
    das[2] = *(pcounter+1);
    return;
}
void DAL4() {
    fseek(diska, (int)*(pcounter+1) * 8192, SEEK_SET);
    fread(&memory[57344], sizeof(uint8_t), 8192 * sizeof(uint8_t), diska);
    das[3] = *(pcounter+1);
    return;
}
void DBL1() {
    fseek(diskb, (int)*(pcounter+1) * 8192, SEEK_SET);
    fread(&memory[16384], sizeof(uint8_t), 8192 * sizeof(uint8_t), diskb);
    dbs[0] = *(pcounter+1);
    return;
}
void DBL2() {
    fseek(diskb, (int)*(pcounter+1) * 8192, SEEK_SET);
    fread(&memory[24576], sizeof(uint8_t), 8192 * sizeof(uint8_t), diskb);
    dbs[1] = *(pcounter+1);
    return;
}
void DBS1() {
    if (*(pcounter+1) > 15) return;
    fseek(diskb, (int)*(pcounter+1) * 8192, SEEK_SET);
    fwrite(memory + 16384, 1, 8192, diskb);
    fflush(diskb);
    return;
}
void DBS2() {
    if (*(pcounter+1) > 15) return;
    fseek(diskb, (int)*(pcounter+1) * 8192, SEEK_SET);
    fwrite(memory + 24576, 1, 8192, diskb);
    fflush(diskb);
    return;
}
void DMPM() {
    for (int i = 0; i < 256; i++) {
        printf("%i", memory[*memaddr + i]);
    }
    printf("\n");
    return;
}
void DMPI() {
    for (int i = 0; i < 256; i++) {
        printf("%i", *(pcounter - 256 + i));
    }
    printf("\n");
    return;
}
void DMPS() {
    for (int i = 0; i < 256; i++) {
        printf("%i", stack[i]);
    }
    printf("\n");
    return;
}
void DMPV() {
    printf("%i %i %i %i %i %i", xreg, yreg, areg, *lreg, *stackpointer, *pcounter);
    printf("\n");
    return;
}
void ADDS() {
    *stackpointer = *memaddr;
    stackpointer++;
    return;
}
void SETS() {
    stackpointer = *(pcounter+1);
    return;
}
void SXIN() {
    stack[xreg] = *memaddr;
    return;
}
void SYIN() {
    stack[yreg] = *memaddr;
    return;
}
void SAIN() {
    stack[areg] = *memaddr;
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
void INCX() {
    xreg += memory[*memaddr];
    return;
}
void DECX() {
    xreg -= memory[*memaddr];
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
void INCY() {
    yreg += memory[*memaddr];
    return;
}
void DECY() {
    yreg -= memory[*memaddr];
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
void INCA() {
    areg += memory[*memaddr];
    return;
}
void DECA() {
    areg -= memory[*memaddr];
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
void IPCX() {
    fgets(strin, 255, stdin);
    for (xreg = 0; strin[xreg] != NULL; xreg++) {

    }
    if (xreg > *(pcounter+1)) {
        xreg = *(pcounter+1);
    }
    return;
}
void IPCY() {
    fgets(strin, 255, stdin);
    for (yreg = 0; strin[xreg] != NULL; xreg++) {

    }
    if (yreg > *(pcounter+1)) {
        yreg = *(pcounter+1);
    }
    return;
}
void IPCA() {
    fgets(strin, 255, stdin);
    for (areg = 0; strin[xreg] != NULL; xreg++) {

    }
    if (areg > *(pcounter+1)) {
        areg = *(pcounter+1);
    }
    return;
}
void NLXS() {
    printf("\n");
    for(uint8_t i=0; i < xreg; i++) {
        printf("%c", memory[*memaddr + i]);
    }
    return;
}
void NLYS() {
    printf("\n");
    for(uint8_t i=0; i < yreg; i++) {
        printf("%c", memory[*memaddr + i]);
    }
    return;
}
void NLAS() {
    printf("\n");
    for(uint8_t i=0; i < areg; i++) {
        printf("%c", memory[*memaddr + i]);
    }
    return;
}
void SDL1() {
    fseek(diska, (int)*(pcounter+1) * 8192, SEEK_SET);
    fread(&memory[32768], sizeof(uint8_t), 16384 * sizeof(uint8_t), diska);
    return;
}
void SDL2() {
    fseek(diska, (int)*(pcounter+1) * 8192, SEEK_SET);
    fread(&memory[40960], sizeof(uint8_t), 16384 * sizeof(uint8_t), diska);
    return;
}
void SDL3() {
    fseek(diska, (int)*(pcounter+1) * 8192, SEEK_SET);
    fread(&memory[49152], sizeof(uint8_t), 16384 * sizeof(uint8_t), diska);
    return;
}
void SDLB() {
    fseek(diskb, (int)*(pcounter+1) * 8192, SEEK_SET);
    fread(&memory[16384], sizeof(uint8_t), 16384 * sizeof(uint8_t), diskb);
    return;
}
void SDSB() {
    if (*(pcounter+1) > 14) {
         return;
    }
    fseek(diskb, (int)*(pcounter+1) * 8192, SEEK_SET);
    fwrite(memory + 16384, 1, 16384, diskb);
    fflush(diskb);
    return;
}
void DMPA() {
    for(int i = 0; i < 4; i++) {
        printf("%i ", das[i]);
    }
    printf("\n");
    return;
}
void DMPB() {
    printf("%i %i\n", dbs[0], dbs[1]);
    return;
}
void JMPF() {
    pcounter += *(pcounter+1);
    return;
}
void JMPB() {
    pcounter -= *(pcounter+1);
    return;
}
void CXEN() {
    if (xreg != *(pcounter+1)) {
        pcounter += 3;
    }
    return;
}
void CXIN() {
    if (xreg < *(pcounter+1)) {
        pcounter += 3;
    }
    return;
}
void CYEN() {
    if (yreg != *(pcounter+1)) {
        pcounter += 3;
    }
    return;
}
void CYIN() {
    if (yreg < *(pcounter+1)) {
        pcounter += 3;
    }
    return;
}
void CAEN() {
    if (areg != *(pcounter+1)) {
        pcounter += 3;
    }
    return;
}
void CAIN() {
    if (areg < *(pcounter+1)) {
        pcounter += 3;
    }
    return;
}
void PRTN() {
    printf("%i", *(pcounter+1));
    return;
}
void ICRD() {
    dp++;
    return;
}
void DCRD() {
    dp--;
    return;
}
void INCD() {
    dp += *(pcounter+1);
    return;
}
void DECD() {
    dp -= *(pcounter+1);
    return;
}
void SETD() {
    dp = memory + *memaddr;
    return;
}
void ZERD() {
    dp = 0;
    return;
}
void ICDX() {
    dp += xreg;
    return;
}
void DCDX() {
    dp -= xreg;
    return;
}
void ICDY() {
    dp += yreg;
    return;
}
void DCDY() {
    dp -= yreg;
    return;
}
void ICDA() {
    dp += areg;
    return;
}
void DCDA() {
    dp -= areg;
    return;
}
void ICDL() {
    dp += *lreg;
}
void DCDL() {
    dp += *lreg;
}
void DSXX() {
    dp = 256 * (uint16_t)xreg + (uint16_t)xreg + memory;
    return;
}
void DSXY() {
    dp = 256 * (uint16_t)xreg + (uint16_t)yreg + memory;
    return;
}
void DSXA() {
    dp = 256 * (uint16_t)xreg + (uint16_t)areg + memory;
    return;
}
void DSXL() {
    dp = 256 * (uint16_t)xreg + (uint16_t)*lreg + memory;
    return;
}
void DSYX() {
    dp = 256 * (uint16_t)yreg + (uint16_t)xreg + memory;
    return;
}
void DSYY() {
    dp = 256 * (uint16_t)yreg + (uint16_t)yreg + memory;
    return;
}
void DSYA() {
    dp = 256 * (uint16_t)yreg + (uint16_t)areg + memory;
    return;
}
void DSYL() {
    dp = 256 * (uint16_t)yreg + (uint16_t)*lreg + memory;
    return;
}
void DSAX() {
    dp = 256 * (uint16_t)areg + (uint16_t)xreg + memory;
    return;
}
void DSAY() {
    dp = 256 * (uint16_t)areg + (uint16_t)yreg + memory;
    return;
}
void DSAA() {
    dp = 256 * (uint16_t)areg + (uint16_t)areg + memory;
    return;
}
void DSAL() {
    dp = 256 * (uint16_t)areg + (uint16_t)*lreg + memory;
    return;
}
void DSLX() {
    dp = 256 * (uint16_t)*lreg + (uint16_t)xreg + memory;
    return;
}
void DSLY() {
    dp = 256 * (uint16_t)*lreg + (uint16_t)yreg + memory;
    return;
}
void DSLA() {
    dp = 256 * (uint16_t)*lreg + (uint16_t)areg + memory;
    return;
}
void DSLL() {
    dp = 256 * (uint16_t)*lreg + (uint16_t)*lreg + memory;
    return;
}
void DTOX() {
    *dp = xreg;
    return;
}
void XTOD() {
    xreg = *dp;
    return;
}
void DTOY() {
    *dp = yreg;
    return;
}
void YTOD() {
    yreg = *dp;
    return;
}
void DTOA() {
    *dp = areg;
    return;
}
void ATOD() {
    areg = *dp;
    return;
}
void DTOL() {
    *dp = *lreg;
    return;
}
void LTOD() {
    *lreg = *dp;
    return;
}
void DTSV() {
    *dp = *(pcounter+1);
    return;
}
void DTSZ() {
    *dp = 0;
    return;
}
void SETL() {
    *lreg = *(pcounter+1);
    return;
}
void ADDL() {
    *lreg += *(pcounter+1);
    return;
}
void SUBL() {
    *lreg -= *(pcounter+1);
    return;
}
void WRTL() {
    memory[*memaddr] = *lreg;
}
void REDL() {
    *lreg = memory[*memaddr];
    return;
}
void CHLE() {
    if(*lreg != memory[*memaddr]) {
        pcounter += 3;
    }
    return;
}
void CHLI() {
    if(*lreg < memory[*memaddr]) {
        pcounter += 3;
    }
    return;
}
void NOP() {
    return;
}
void opcode() { 
    memaddr = pcounter + 1;
    switch (*pcounter) {
        case 0:
            QITZ();
            break;
        case 1:
            QITE();
            break;
        case 2:
            JMP();
// jump instructions do not update the program counter. that's just bad practice
            break;
        case 3:
            JSR();
            break;
        case 4:
            ABA();
            break;
        case 5:
            RET();
            break;
        case 6:
            SETX();
            pcounter += 2;
            break;
        case 7:
            ADDX();
            pcounter += 2;
            break;
        case 8:
            SUBX();
            pcounter += 2;
            break;
        case 9:
            WRTX();
            pcounter += 3;
            break;
        case 10:
            REDX();
            pcounter += 3;
            break;
        case 11:
            CHXE();
            pcounter += 3;
            break;
        case 12:
            CHXI();
            pcounter += 3;
            break;
        case 13:
            LODX();
            pcounter++;
            break;
        case 14:
            SETY();
            pcounter += 2;
            break;
        case 15:
            ADDY();
            pcounter += 2;
            break;
        case 16:
            SUBY();
            pcounter += 2;
            break;
        case 17:
            WRTY();
            pcounter += 3;
            break;
        case 18:
            REDY();
            pcounter += 3;
            break;
        case 19:
            CHYE();
            pcounter += 3;
            break;
        case 20:
            CHYI();
            pcounter += 3;
            break;
        case 21:
            LODY();
            pcounter++;
            break;
        case 22:
            SETA();
            pcounter += 2;
            break;
        case 23:
            ADDA();
            pcounter += 2;
            break;
        case 24:
            SUBA();
            pcounter += 2;
            break;
        case 25:
            WRTA();
            pcounter += 3;
            break;
        case 26:
            REDA();
            pcounter += 3;
            break;
        case 27:
            CHAE();
            pcounter += 3;
            break;
        case 28:
            CHAI();
            pcounter += 3;
            break;
        case 29:
            LODA();
            pcounter++;
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
            RDLX();
            pcounter += 3;
            break;
        case 51:
            RDLY();
            pcounter += 3;
            break;
        case 52:
            RDLA();
            pcounter += 3;
            break;
        case 54:
            PRTX();
            pcounter += 3;
            break;
        case 55:
            PRTY();
            pcounter += 3;
            break;
        case 56:
            PRTA();
            pcounter += 3;
            break;
        case 57:
            PRTB();
            pcounter++;
            break;
        case 58:
            DAL1();
            pcounter += 2;
            break;
        case 59:
            DAL2();
            pcounter += 2;
            break;
        case 60:
            DAL3();
            pcounter += 2;
            break;
        case 61:
            DAL4();
            pcounter += 2;
            break;
        case 62:
            DBL1();
            pcounter += 2;
            break;
        case 63:
            DBL2();
            pcounter += 2;
            break;
        case 64:
            DBS1();
            pcounter += 2;
            break;
        case 65:
            DBS2();
            pcounter += 2;
            break;
        case 66:
            DMPM();
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
            ADDS();
            pcounter += 3;
            break;
        case 71:
            SETS();
            pcounter += 2;
            break;
        case 72:
            SXIN();
            pcounter += 3;
            break;
        case 73:
            SYIN();
            pcounter += 3;
            break;  
        case 74:
            SAIN();
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
            INCX();
            pcounter += 3;
            break;
        case 81:
            DECX();
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
            INCY();
            pcounter += 3;
            break;
        case 85:
            DECY();
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
            INCA();
            pcounter += 3;
            break;
        case 89:
            DECA();
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
            IPCX();
            pcounter += 2;
            break;
        case 107:
            IPCY();
            pcounter += 2;
            break;
        case 108:
            IPCA();
            pcounter += 2;
            break;
        case 110:
            NLXS();
            pcounter += 3;
            break;
        case 111:
            NLYS();
            pcounter += 3;
            break;
        case 112:
            NLAS();
            pcounter += 3;
            break;
        case 114:
            SDL1();
            pcounter += 2;
            break;
        case 115:
            SDL2();
            pcounter += 2;
            break;       
        case 116:
            SDL3();
            pcounter += 2;
            break;
        case 118:
            SDLB();
            pcounter += 2;
            break;
        case 119:
            SDSB();
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
            JMPF();
            break;
        case 123:
            JMPB();
            break;
        case 124:
            CXEN();
            pcounter +=2;
            break;
        case 125:
            CXIN();
            pcounter +=2;
            break;
        case 126:
            CYEN();
            pcounter +=2;
            break;
        case 127:
            CYIN();
            pcounter +=2;
            break;
        case 128:
            CAEN();
            pcounter +=2;
            break;
        case 129:
            CAIN();
            pcounter +=2;
            break;
        case 130:
            PRTN();
            pcounter += 2;
            break;
        case 132:
            ICRD();
            pcounter++;
            break;
        case 133:
            DCRD();
            pcounter++;
            break;
        case 134:
            INCD();
            pcounter += 2;
            break;
        case 135:
            DECD();
            pcounter += 2;
            break;
        case 136:
            SETD();
            pcounter += 3;
            break;
        case 137:
            ZERD();
            pcounter++;
            break;
        case 138:
            ICDX();
            pcounter++;
            break;
        case 139:
            DCDX();
            pcounter++;
            break;
        case 140:
            ICDY();
            pcounter++;
            break;
        case 141:
            DCDY();
            pcounter++;
            break;
        case 142:
            ICDA();
            pcounter++;
            break;
        case 143:
            DCDA();
            pcounter++;
            break;
        case 144:
            ICDL();
            pcounter++;
            break;
        case 145:
            DCDL();
            pcounter++;
            break;
        case 146:
            DSXX();
            pcounter++;
            break;
        case 147:
            DSXY();
            pcounter++;
            break;
        case 148:
            DSXA();
            pcounter++;
            break;
        case 149:
            DSXL();
            pcounter++;
            break;
        case 150:
            DSYX();
            pcounter++;
            break;
        case 151:
            DSYY();
            pcounter++;
            break;
        case 152:
            DSYA();
            pcounter++;
            break;
        case 153:
            DSYL();
            pcounter++;
            break;
        case 154:
            DSAX();
            pcounter++;
            break;
        case 155:
            DSAY();
            pcounter++;
            break;
        case 156:
            DSAA();
            pcounter++;
            break;
        case 157:
            DSAL();
            pcounter++;
            break;
        case 158:
            DSLX();
            pcounter++;
            break;
        case 159:
            DSLY();
            pcounter++;
            break;
        case 160:
            DSLA();
            pcounter++;
            break;
        case 161:
            DSLL();
            pcounter++;
            break;
        case 162:
            DTOX();
            pcounter++;
            break;
        case 163:
            XTOD();
            pcounter++;
            break;
        case 164:
            DTOY();
            pcounter++;
            break;
        case 165:
            YTOD();
            pcounter++;
            break;
        case 166:
            DTOA();
            pcounter++;
            break;
        case 167:
            ATOD();
            pcounter++;
            break;
        case 168:
            DTOL();
            pcounter++;
            break;
        case 169:
            LTOD();
            pcounter++;
            break;
        case 170:
            DTSV();
            pcounter += 2;
            break;
        case 171:
            DTSZ();
            pcounter++;
            break;
        case 172:
            SETL();
            pcounter += 2;
            break;
        case 173:
            ADDL();
            pcounter += 2;
            break;
        case 174:
            SUBL();
            pcounter += 2;
            break;
        case 175:
            WRTL();
            pcounter += 3;
            break;
        case 176:
            REDL();
            pcounter += 3;
            break;
        case 177:
            CHLE();
            pcounter += 3;
            break;
        case 178:
            CHLI();
            pcounter += 3;
            break;
        default:
            NOP();
            pcounter++;
            break;
    } 
}
