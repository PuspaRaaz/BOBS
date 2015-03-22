#ifndef OPCODE_H_
#define OPCODE_H_

#include "MicroProcessor.h"

//Global variables used
Memory* opcode;


//Function used
void Opcode_init(int pCounter);
void Eval_Stepwise();
void updateFlags(int regA, int op1, int op2,int mode); //mode = 0 for addition, 1 for subtraction
void printflags();
void Interrupt(int jmpvalue);
//Opcode lists
#endif
