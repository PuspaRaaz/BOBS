#ifndef MICROPROCESSOR_H_
#define MICROPROCESSOR_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "Stack.h"
#include "ppi.h"



#define MAX_OP_LEN 0x1000
//start of the code
#define start_of_code 0x8000

void ThrowError(char*,int);     //Throw error

//For both RunOpcode and SingleStep to work one must call the main function of Microprocessor.c
// i.e both opcode must be generated and Opcode_init should be called
void RunOpcode();               //Run all opcodes
void SingleStep();              //Run single step


int hasHalted;


int flag;

PPI pPort; ///ppi ports, pPort.pa.val
PPI mPort; ///microprocessor ports mPort.pa.val

int A,B,C,D,E,H,L,M,PC,PSW,IR;

typedef struct{
    int addr;
    int value;
}Memory;

Memory Op[MAX_OP_LEN];

int getzero();
int getcarry();
int getsign();
int getparity();
int getAF();
int Parity(int n);

void setzero();
void resetzero();
void setcarry();
void resetcarry();
void setsign();
void resetsign();
void setparity();
void resetparity();
void setAF();
void resetAF();
void complement_carry();



#endif
