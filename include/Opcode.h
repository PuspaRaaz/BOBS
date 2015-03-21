#ifndef OPCODE_H_
#define OPCODE_H_

#include "MicroProcessor.h"

//Global variables used
Memory* opcode;
int hasHalted;
//Function used
void Opcode_main(Memory* Op,int pCounter);
void Eval_Opcode(int value);
void updateFlags(int regA, int op1, int op2);
void Evaluate(int pCounter);
void printflags();
//Opcode lists
#endif
