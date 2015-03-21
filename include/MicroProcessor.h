#ifndef MICROPROCESSOR_H_
#define MICROPROCESSOR_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "Stack.h"

//start of the code
#define start_of_code 0x8000

void ThrowError(char*,int);
int my_itoa(int val, char* buf);

int flag;
int Port[4];
int baseADD;
int A,B,C,D,E,H,L,M,PC,PSW,IR;

typedef struct{
    int addr;
    int value;
}Memory;


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
