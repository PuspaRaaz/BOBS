#ifndef OPCODE_H_
#define OPCODE_H_

#include "MicroProcessor.h"

//Global variables used
Memory* opcode;
int hasHalted;
//Function used
void Opcode_main(Memory* Op,int pCounter);
void Eval_Opcode(int value);
void updateFlags(int regA, int op1, int op2,int mode); //mode = 0 for addition, 1 for subtraction
void Evaluate(int pCounter);
void printflags();
//Opcode lists
#endif
