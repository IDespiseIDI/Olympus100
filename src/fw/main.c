#include "globalcpu.h"
#include "globaldisk.h"
#include "globalram.h"
#include "main.h"
#include <string.h>
#include <stdlib.h>
FILE *diska;
FILE *diskb;
#ifdef _DEBUG
FILE *logfile;
int debugstart;
int debuglength;
int debugdepth;
#endif
int quit = 0;


int main(int argc, char *argv[]) {
    if (argc < 3) {
        perror("Missing disk");
        return -1;
    }
    if (argv[1] == argv[2]) {
        perror("You have inserted the same disk twice.\n");
        return (-1);
    }
    memory = calloc(65536, sizeof(uint8_t));
    if (memory == NULL) {
        perror("Failed to allocate memory.\n");
        return (-1);
    }
    diska = fopen(argv[1], "rb+");
    diskb = fopen(argv[2], "rb+");
#ifdef _DEBUG
    logfile = fopen("log.txt", "w");
    debugstart = atoi(argv[3]);
    debuglength = atoi(argv[4]);
    debugdepth = 255;
    if (argc > 4) {
        debugdepth = atoi(argv[5]);
    }
#endif
    if (!diska || !diskb) {
        perror("Disk error, please try again.");
        return (-1);
    }
    for (int i = 0; i < sizeof(firmware) / sizeof(uint8_t); i++) {
        memory[i] = firmware[i];
    }
    pcounter = 0;
    while(quit == 0) {
#ifdef _DEBUG
        if (stackpointer < debugdepth) {
            if(argc > 2) {
                for(int i=0; i < debuglength; i++) {
                    fprintf(logfile, "%hhu ", memory[debugstart + i]);
                }
                fprintf(logfile, "\n");
            }
            fprintf(logfile, "%hhu %hhu %hhu \n", memory[pcounter], memory[pcounter + 1], memory[pcounter + 2]);
            if (argc > 2) {
                fprintf(logfile, "\n");
            }
            fflush(logfile);
        }
#endif
        opcode(memory[pcounter], memory[pcounter + 1], memory[pcounter + 2]);
    }
    fclose(diska);
    fclose(diskb);
#ifdef _DEBUG
    fclose(logfile);
#endif
    return 0;
}