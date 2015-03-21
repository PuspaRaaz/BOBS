#include "Opcode.h"

void Opcode_main(Memory* Op, int pCounter){
    PC = pCounter - start_of_code;  //this will be the current pos of our opcode
    opcode = Op;
    hasHalted = 0;
    Evaluate(PC);
    printflags();
}

printflags(){
    printf("A: %X\n B: %X\n C: %X\n D: %X\n E: %X\n H: %X\n L: %X\n M ",A,B,C,D,E,H,L,M);
    printf("S %d, CY %d, Z %d, AC %d, P %d ", getsign(),getcarry(),getzero(),getAF(),getparity());
}
void Evaluate(int pCounter){
    while(1){
        Eval_Opcode(opcode[PC].value);
        if (hasHalted)
                break;
    }
}
void updateFlags(int regA, int op1, int op2){
    if (regA > 0xFF) setcarry();
    else resetcarry();

    if (regA == 0x00) setzero();
    else resetzero();

    /*add a parity check here
    ..............
    ............
    ............
    ..............
    */

    int nib = (op1 & 0xF) + (op2 & 0xF);
    if (nib > 0xF) setAF();
    else resetAF();

    if ((regA >> 7) & 1) setsign();
    else resetsign();
}

void Eval_Opcode(int value){
    int op1,op2,res;
    if (value == 0xCE){
        /// ACI DATA
        int prevCarry = getcarry();
        op1 = A;
        op2 = opcode[++PC].value;
        res = op1 + op2 + prevCarry;
        updateFlags(res,op1,op2);
        A = res & 0xFF;
    }

    else if (value == 0x8f){
        ///ADC A
         int prevCarry = getcarry();
        op1 = A;
        op2 = A;
        res = op1 + op2 + prevCarry;
        updateFlags(res,op1,op2);
        A = res & 0xFF;
    }

    else if (value == 0x88){
        ///ADC B
         int prevCarry = getcarry();
        op1 = A;
        op2 = B;
        res = op1 + op2 + prevCarry;
        updateFlags(res,op1,op2);
        A = res & 0xFF;
    }

    else if (value == 0x89){
        ///ADC C
         int prevCarry = getcarry();
        op1 = A;
        op2 = C;
        res = op1 + op2 + prevCarry;
        updateFlags(res,op1,op2);
        A = res & 0xFF;
    }

    else if (value == 0x8A){
        ///ADC D
         int prevCarry = getcarry();
        op1 = A;
        op2 = D;
        res = op1 + op2 + prevCarry;
        updateFlags(res,op1,op2);
        A = res & 0xFF;
    }

    else if (value == 0x8B){
        ///ADC E
         int prevCarry = getcarry();
        op1 = A;
        op2 = E;
        res = op1 + op2 + prevCarry;
        updateFlags(res,op1,op2);
        A = res & 0xFF;
    }

    else if (value == 0x8C){
        ///ADC H
         int prevCarry = getcarry();
        op1 = A;
        op2 = H;
        res = op1 + op2 + prevCarry;
        updateFlags(res,op1,op2);
        A = res & 0xFF;
    }

    else if (value == 0x8D){
        ///ADC L
         int prevCarry = getcarry();
        op1 = A;
        op2 = L;
        res = op1 + op2 + prevCarry;
        updateFlags(res,op1,op2);
        A = res & 0xFF;
    }

    else if (value == 0x8E){
        ///ADC M
         int prevCarry = getcarry();
        op1 = A;
        op2 = M;
        res = op1 + op2 + prevCarry;
        updateFlags(res,op1,op2);
        A = res & 0xFF;
    }

    else if (value == 0x87){
        ///ADD A
        op1 = A;
        op2 = A;
        res = op1 + op2;
        updateFlags(res,op1,op2);
        A = res & 0xFF;
    }

    else if (value == 0x80){
        ///ADD B
        op1 = A;
        op2 = B;
        res = op1 + op2;
        updateFlags(res,op1,op2);
        A = res & 0xFF;
    }

    else if (value == 0x81){
        ///ADD C
        op1 = A;
        op2 = C;
        res = op1 + op2;
        updateFlags(res,op1,op2);
        A = res & 0xFF;
    }

    else if (value == 0x82){
        ///ADD D
        op1 = A;
        op2 = D;
        res = op1 + op2;
        updateFlags(res,op1,op2);
        A = res & 0xFF;
    }

    else if (value == 0x83){
        ///ADD E
        op1 = A;
        op2 = E;
        res = op1 + op2;
        updateFlags(res,op1,op2);
        A = res & 0xFF;
    }

    else if (value == 0x84){
        ///ADD H
        op1 = A;
        op2 = H;
        res = op1 + op2;
        updateFlags(res,op1,op2);
        A = res & 0xFF;
    }

    else if (value == 0x85){
        ///ADD L
        op1 = A;
        op2 = L;
        res = op1 + op2;
        updateFlags(res,op1,op2);
        A = res & 0xFF;
    }

    else if (value == 0x86){
        ///ADD M
        op1 = A;
        op2 = M;
        res = op1 + op2;
        updateFlags(res,op1,op2);
        A = res & 0xFF;
    }

    else if (value == 0xC6){
        ///ADI DATA
        op1 = A;
        op2 = opcode[++PC].value;
        res = op1 + op2;
        updateFlags(res,op1,op2);
        A = res & 0xFF;
    }

    else if (value == 0xA7){
        ///ANA A
        op1 = A;
        op2 = A;
        res = op1 & op2;
        updateFlags(res,op1,op2);
        resetcarry();
        setAF();
        A = res & 0xFF;
    }

    else if (value == 0xA0){
        ///ANA B
        op1 = A;
        op2 = B;
        res = op1 & op2;
        updateFlags(res,op1,op2);
        resetcarry();
        setAF();
        A = res & 0xFF;
    }

    else if (value == 0xA1){
        ///ANA C
        op1 = A;
        op2 = C;
        res = op1 & op2;
        updateFlags(res,op1,op2);
        resetcarry();
        setAF();
        A = res & 0xFF;
    }

    else if (value == 0xA2){
        ///ANA D
        op1 = A;
        op2 = D;
        res = op1 & op2;
        updateFlags(res,op1,op2);
        resetcarry();
        setAF();
        A = res & 0xFF;
    }

    else if (value == 0xA3){
        ///ANA E
        op1 = A;
        op2 = E;
        res = op1 & op2;
        updateFlags(res,op1,op2);
        resetcarry();
        setAF();
        A = res & 0xFF;
    }
    else if (value == 0xA4){
        ///ANA H
        op1 = A;
        op2 = H;
        res = op1 & op2;
        updateFlags(res,op1,op2);
        resetcarry();
        setAF();
        A = res & 0xFF;
    }

    else if (value == 0xA5){
        ///ANA L
        op1 = A;
        op2 = L;
        res = op1 & op2;
        updateFlags(res,op1,op2);
        resetcarry();
        setAF();
        A = res & 0xFF;
    }

    else if (value == 0xA6){
        ///ANA M
        op1 = A;
        op2 = M;
        res = op1 & op2;
        updateFlags(res,op1,op2);
        resetcarry();
        setAF();
        A = res & 0xFF;
    }

    else if (value == 0xE6){
        ///ANI DATA
        op1 = A;
        op2 = opcode[++PC].value;
        res = op1 & op2;
        updateFlags(res,op1,op2);
        resetcarry();
        setAF();
        A = res & 0xFF;
    }

    else if (value == 0xCD){
        ///CALL LABEL
        int tempPC = PC + 3;
        push(tempPC);

        int lo = opcode[PC+1].value;
        int up = opcode[PC+2].value;

        PC = (up << 8) + lo - start_of_code;
        Evaluate(PC);
    }

    else if (value == 0xC9){
        ///RET
        PC = pop();
        Evaluate(PC);
    }

    else if (value == 0x76){
        ///HLT
        hasHalted = 1;
    }

    PC ++;
}
