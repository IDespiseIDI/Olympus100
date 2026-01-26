/*okay, here we go, this is supposed to be a BASIC (not the programming language)
virtual computer emulator, no graphics API, nothing fancy, just a test based interface
I chose firmware (/fw) for the place to put the main.cpp file because that is supposed
to be the first thing that powers on. What is supposed to happen is "./firmware.fw" (or somewhere
 else) is fed into the cpu. */
#include "globalcpu.h"
#include "globaldisk.h"
#include "globalram.h"
#include "main.h"
#include <iostream>
#include <cstddef>
#include <algorithm>
std::string diskapath;
std::string diskbpath;
bool quit = false;

//std::string fwpath = "./firmware.fw"; //firmware path, if not specified, defaults to ./firmware.fw
//bool stayinbios = false;
int main(int argc, char *argv[]) { //choose firmware file, whether to stay at boot screen, etc.
if (argc < 3) {
    std::cerr << "Usage: " << argv[0] << " <diskA path> <diskB path>" << std::endl;
    return -1;
}
diskapath = argv[1];
diskbpath = argv[2];
//    } //done checking cmdline args
    /*get system information. Oh, I'll need to work on that now I guess.
    std::cout << "Olympus 100" << std::endl;
    Oh, wait. Why am I doing that? shouldn't this code from here on out ONLY be calls to the CPU?
    Unless one isn't found of course.*/
    //literally 2 days later looking at what I said. WHAT? WHY WOULD A CPU NOT BE FOUND?
    diska.open(diskapath, std::ios::in | std::ios::out | std::ios::binary);
    diskb.open(diskbpath, std::ios::in | std::ios::out | std::ios::binary);
    if (!diska || !diskb) { //Oh, still need to check for disks
        std::cout << "A disk is missing, please try again" << std::endl;
        return (-1);
    }
    for (size_t i = 0; i < 365; ++i) {
        memory[i] = firmware[i];
    }
    pcounter = 0;
    while(!quit) {
        opcode(memory[pcounter], memory[pcounter + 1], memory[pcounter + 2]);
    }
    diska.close();
    diskb.close();
    return 0;
    
}