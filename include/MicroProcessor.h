#ifndef MICROPROCESSOR_H_
#define MICROPROCESSOR_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

//start of the code
int start_of_code;

void ThrowError(char*,int);
int my_itoa(int val, char* buf);

int flag;
int A,B,C,D,E,H,L,M,SP,PC,PSW,IR;

typedef struct{
    int addr;
    int value;
}Memory;


int getzero();
int getcarry();
int getsign();
int getparity();
int getAF();

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
