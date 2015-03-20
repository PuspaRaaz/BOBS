#ifndef OPCODE_H_
#define OPCODE_H_

#include "MicroProcessor.h"

//Global variables used
int pos;
Memory* opcode;

//Function used
void Opcode_main(Memory* Op, int Op_count);
void Eval_Opcode(int value);

//Opcode lists
#endif
