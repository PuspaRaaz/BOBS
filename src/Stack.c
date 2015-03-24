#include "Stack.h"

void init_stack(){
    SP = start_of_code + 0x200;
}

void push(int v){
    SP--;
    value[SP-start_of_code] = v;
}

int pop(){
	int val = value[SP - start_of_code];
    SP++;
    return val;
}
