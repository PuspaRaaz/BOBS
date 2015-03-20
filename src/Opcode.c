#include "Opcode.h"

void Opcode_main(Memory* Op, int Op_count){
    pos = 0;  //this will be the current pos of our opcode
    opcode = Op;
    //now untill our opcodes finish
    while(pos<Op_count){
        Eval_Opcode(Op[pos].value);
        pos++;
    }
}


void Eval_Opcode(int value){

}
