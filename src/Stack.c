#include "Stack.h"

void init_stack(){
    top = -1;
}

void push(int v){
    top ++;
    value[top] = v;
}

int pop(){
    return value[top--];
}
