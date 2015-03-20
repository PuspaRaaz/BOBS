#include "Opcode.h"

void Opcode_main(Memory* Op, int Op_count){
    pos = 0;  //this will be the current pos of our opcode
    opcode = Op;
    //now untill our opcodes finish
    for(pos;pos<Op_count;pos++){
        Eval_Opcode(Op[pos].value);

    }
}


void Eval_Opcode(int value){
    int temp;
    //add accumulator with carry (aci)
    if (value == 0x3c ){
        temp = opcode[++pos].value + Flag.C ;
        if (temp > 0xFF){
            Flag.C = 1;
            temp -= 0xFF;
        }
        else
            Flag.C = 0;

        Reg.A += temp;
    }
//
//    //ADC A
//    else if (value == 0x8f){
//        temp = opcode[++pos].value + Flag.C;
//        Reg
//    }

}
