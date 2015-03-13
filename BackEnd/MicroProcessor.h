#ifndef MICROPROCESSOR_H_
#define MICROPROCESSOR_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

//start of the code
int start_of_code;

char* ThrowError(char*,int);
int my_itoa(int val, char* buf);

//flags
typedef struct {
    char S,Z,AC,P,C;
}flags;
flags Flag;

//registers
typedef struct {
    char A,B,C,E,H,L,SP;
}registers;
registers Reg;

typedef struct{
    int addr;
    int value;
}Memory;


#endif
