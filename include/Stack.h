#pragma once

#include "MicroProcessor.h"
int value[0x200];
int SP;

void init_stack();
void push(int v);
int pop();



