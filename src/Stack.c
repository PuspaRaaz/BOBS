#include "Stack.h"

void init_stack(){
    SP = -1;
}

void push(int v){
    SP ++;
    value[SP] = v;
}

int pop(){
    return value[SP--];
}
