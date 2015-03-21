#include "Opcode.h"

void Opcode_main(Memory* Op, int pCounter){
    PC = pCounter - start_of_code;  //this will be the current pos of our opcode
    opcode = Op;
    hasHalted = 0;
    Evaluate(PC);
    printflags();
}

printflags(){
    printf("A: %X\n B: %X\n C: %X\n D: %X\n E: %X\n H: %X\n L: %X\n M: %X\n ",A,B,C,D,E,H,L,M);
    printf("S %d, CY %d, Z %d, AC %d, P %d ", getsign(),getcarry(),getzero(),getAF(),getparity());
}
void Evaluate(int pCounter){
    while(1){
        Eval_Opcode(opcode[PC].value);
        if (hasHalted)
                return;
    }
}
void updateFlags(int regA, int op1, int op2){
    if (regA == 0x00) setzero();
    else resetzero();

    if (Parity(regA)) setparity();
    else resetparity();

    if ((regA >> 7) & 1) setsign();
    else resetsign();

    if(op1 == 0 && op2 ==0)
        return;

    if (regA > 0xFF) setcarry();
    else resetcarry();

    int nib = (op1 & 0xF) + (op2 & 0xF);
    if (nib > 0xF) setAF();
    else resetAF();


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

    else if (value == 0xDC){
        ///CC LABEL
        //if carry flag is 0
        if (getcarry() == 0)
            return;

        int tempPC = PC + 3;
        push(tempPC);

        int lo = opcode[PC+1].value;
        int up = opcode[PC+2].value;

        PC = (up << 8) + lo - start_of_code;
        Evaluate(PC);
    }

    else if (value == 0xFC){
        ///CM LABEL
        //if not a minus sign
        if (getsign() == 0)
            return;

        int tempPC = PC + 3;
        push(tempPC);

        int lo = opcode[PC+1].value;
        int up = opcode[PC+2].value;

        PC = (up << 8) + lo - start_of_code;
        Evaluate(PC);
    }

    else if (value == 0xD4){
        ///CNC LABEL
        //if carry return
        if (getcarry() == 1)
            return;

        int tempPC = PC + 3;
        push(tempPC);

        int lo = opcode[PC+1].value;
        int up = opcode[PC+2].value;

        PC = (up << 8) + lo - start_of_code;
        Evaluate(PC);
    }

    else if (value == 0xC4){
        ///CNZ LABEL
        //if zero return
        if (getzero() == 1)
            return;

        int tempPC = PC + 3;
        push(tempPC);

        int lo = opcode[PC+1].value;
        int up = opcode[PC+2].value;

        PC = (up << 8) + lo - start_of_code;
        Evaluate(PC);
    }

    else if (value == 0xFC){
        ///CP LABEL
        //if not positive return
        if (getsign() == 1)
            return;

        int tempPC = PC + 3;
        push(tempPC);

        int lo = opcode[PC+1].value;
        int up = opcode[PC+2].value;

        PC = (up << 8) + lo - start_of_code;
        Evaluate(PC);
    }

    else if (value == 0xEC){
        ///CPE LABEL
        //if not parity return
        if (getparity() == 0)
            return;

        int tempPC = PC + 3;
        push(tempPC);

        int lo = opcode[PC+1].value;
        int up = opcode[PC+2].value;

        PC = (up << 8) + lo - start_of_code;
        Evaluate(PC);
    }

    else if (value == 0xE4){
        ///CPO LABEL
        //if parity return
        if (getparity() == 1)
            return;

        int tempPC = PC + 3;
        push(tempPC);

        int lo = opcode[PC+1].value;
        int up = opcode[PC+2].value;

        PC = (up << 8) + lo - start_of_code;
        Evaluate(PC);
    }

    else if (value == 0xCC){
        ///CZ LABEL
        //if not zero return
        if (getzero() == 0)
            return;

        int tempPC = PC + 3;
        push(tempPC);

        int lo = opcode[PC+1].value;
        int up = opcode[PC+2].value;

        PC = (up << 8) + lo - start_of_code;
        Evaluate(PC);
    }




    else if (value == 0x2F){
        ///CMA
        A = ~A & 0xFF;
    }

    else if (value == 0x3F){
        ///CMC
        complement_carry();
    }

    else if (value == 0xBF){
        ///CMP A
        op1 = A;
        op2 = A;
        if (op1 > op2) setcarry();
        else if (op1 == op2) setzero();
        else{resetcarry(); resetzero();}
    }

    else if (value == 0xB8){
        ///CMP B
        op1 = A;
        op2 = B;
        if (op1 > op2) setcarry();
        else if (op1 == op2) setzero();
        else{resetcarry(); resetzero();}
    }

    else if (value == 0xB9){
        ///CMP C
        op1 = A;
        op2 = C;
        if (op1 > op2) setcarry();
        else if (op1 == op2) setzero();
        else{resetcarry(); resetzero();}
    }

    else if (value == 0xBA){
        ///CMP D
        op1 = A;
        op2 = D;
        if (op1 > op2) setcarry();
        else if (op1 == op2) setzero();
        else{resetcarry(); resetzero();}
    }

    else if (value == 0xBB){
        ///CMP E
        op1 = A;
        op2 = E;
        if (op1 > op2) setcarry();
        else if (op1 == op2) setzero();
        else{resetcarry(); resetzero();}
    }

    else if (value == 0xBC){
        ///CMP H
        op1 = A;
        op2 = H;
        if (op1 > op2) setcarry();
        else if (op1 == op2) setzero();
        else{resetcarry(); resetzero();}
    }

    else if (value == 0xBD){
        ///CMP L
        op1 = A;
        op2 = L;
        if (op1 > op2) setcarry();
        else if (op1 == op2) setzero();
        else{resetcarry(); resetzero();}
    }

    else if (value == 0xBE){
        ///CMP M
        op1 = A;
        op2 = M;
        if (op1 > op2) setcarry();
        else if (op1 == op2) setzero();
        else{resetcarry(); resetzero();}
    }

    else if (value == 0xFE){
        ///CPI DATA
        op1 = A;
        op2 = opcode[++PC].value;
        if (op1 > op2) setcarry();
        else if (op1 == op2) setzero();
        else{resetcarry(); resetzero();}
    }

    else if (value == 0x27){
        ///DAA
        op1 = A & 0xf; //lower nibble
        op2 = ((A >> 4) & 0xf);  //higher nibble

        if (op1 > 9)
            op1 = 0x06;
        else
            op1 = 0;

        if (op2 > 9)
            op2 = 0x6;
        else
            op2 = 0;
        op1 = (op2 << 4) + op1;
        op2 = A;

        res = op1 + op2;
        updateFlags(res,op1,op2);

        A = res & 0xff;
    }

    else if (value == 0x09){
        ///DAD B
        op1 = (H << 8) + L;
        op2 = (B << 8) + C;
        res = op1 + op2;
        if (res > 0xffff) setcarry();
        H = (res >> 8) & 0xff;
        L = res & 0xff;
    }

    else if (value == 0x19){
        ///DAD D
        op1 = (H << 8) + L;
        op2 = (D << 8) + E;
        res = op1 + op2;
        if (res > 0xffff) setcarry();
        H = (res >> 8) & 0xff;
        L = res & 0xff;
    }

    else if (value == 0x29){
        ///DAD H
        op1 = (H << 8) + L;
        op2 = (H << 8) + L;
        res = op1 + op2;
        if (res > 0xffff) setcarry();
        H = (res >> 8) & 0xff;
        L = res & 0xff;
    }

    else if (value == 0x39){
        ///DAD SP
        op1 = (H << 8) + L;
        op2 = SP;
        res = op1 + op2;
        if (res > 0xffff) setcarry();
        H = (res >> 8) & 0xff;
        L = res & 0xff;
    }

    else if (value == 0x3D){
        ///DCR A
        A -= 1;
    }

    else if (value == 0x05){
        ///DCR B
        B -= 1;
    }

    else if (value == 0x0D){
        ///DCR C
        C -= 1;
    }

    else if (value == 0x15){
        ///DCR D
        D -= 1;
    }

    else if (value == 0x1D){
        ///DCR E
        E -= 1;
    }

    else if (value == 0x25){
        ///DCR H
        H -= 1;
    }

    else if (value == 0x2D){
        ///DCR L
        L -= 1;
    }

    else if (value == 0x35){
        ///DCR M
        M -= 1;
    }

    else if (value == 0x0B){
        ///DCX B
        res = (B << 8) + C;
        res -= 1;
        B = (res >> 8) & 0xff;
        C = res & 0xff;
    }

    else if (value == 0x1B){
        ///DCX D
        res = (D << 8) + E;
        res -= 1;
        D = (res >> 8) & 0xFF;
        E = res & 0xFF;
    }

    else if (value == 0x2B){
        ///DCX H
        res = (H << 8) + L;
        res -= 1;
        H = (res >> 8) & 0xFF;
        L = res & 0xFF;
    }

    else if (value == 0x3B){
        ///DCX SP
        SP -= 1;
    }

    else if (value == 0xDB){
        ///IN port-address
        op1 = opcode[++PC].value - baseADD;
        A = Port[op1];
    }

    else if (value == 0x3C){
        ///INR A
        A += 1;
    }

    else if (value == 0x04){
        ///INR B
        B += 1;
    }

    else if (value == 0x0C){
        ///INR C
        C += 1;
    }

    else if (value == 0x14){
        ///INR D
        D += 1;
    }

    else if (value == 0x1C){
        ///INR E
        E += 1;
    }

    else if (value == 0x24){
        ///INR H
        H += 1;
    }

    else if (value == 0x2C){
        ///INR L
        L += 1;
    }

    else if (value == 0x34){
        ///INR M
        M += 1;
    }

    else if (value == 0x03){
        ///INX B
        res = (B << 8) + C;
        res += 1;
        B = (res >> 8) & 0xFF;
        C = res & 0xFF;
    }

    else if (value == 0x13){
        ///INX D
        res = (D << 8) + E;
        res += 1;
        D = (res >> 8) & 0xFF;
        E = res & 0xFF;
    }

    else if (value == 0x23){
        ///INX H
        res = (H << 8) + L;
        res += 1;
        H = (res >> 8) & 0xFF;
        L = res & 0xFF;
    }

    else if (value == 0x33){
        ///INX SP
        SP += 1;
    }

    else if (value == 0xDA){
        ///JC Label
        if (getcarry() == 0)
            return;

        int lo = opcode[PC+1].value;
        int up = opcode[PC+2].value;

        PC = (up << 8) + lo - start_of_code;
        Evaluate(PC);
    }

    else if (value == 0xDA){
        ///JM Label
        if (getsign() == 0)
            return;

        int lo = opcode[PC+1].value;
        int up = opcode[PC+2].value;

        PC = (up << 8) + lo - start_of_code;
        Evaluate(PC);
    }

    else if (value == 0xC3){
        ///JMP Label
        int lo = opcode[PC+1].value;
        int up = opcode[PC+2].value;

        PC = (up << 8) + lo - start_of_code;
        Evaluate(PC);
    }

    else if (value == 0xD2){
        ///JNC Label
        if (getcarry() == 1)
            return;

        int lo = opcode[PC+1].value;
        int up = opcode[PC+2].value;

        PC = (up << 8) + lo - start_of_code;
        Evaluate(PC);
    }

    else if (value == 0xC2){
        ///JNZ Label
        if (getzero() == 1)
            return;

        int lo = opcode[PC+1].value;
        int up = opcode[PC+2].value;

        PC = (up << 8) + lo - start_of_code;
        Evaluate(PC);
    }

    else if (value == 0xf2){
        ///JP Label
        if (getsign() == 1)
            return;

        int lo = opcode[PC+1].value;
        int up = opcode[PC+2].value;

        PC = (up << 8) + lo - start_of_code;
        Evaluate(PC);
    }

    else if (value == 0xEA){
        ///JPE Label
        if (getparity() == 0)
            return;

        int lo = opcode[PC+1].value;
        int up = opcode[PC+2].value;

        PC = (up << 8) + lo - start_of_code;
        Evaluate(PC);
    }

    else if (value == 0xE2){
        ///JPO Label
        if (getparity() == 1)
            return;

        int lo = opcode[PC+1].value;
        int up = opcode[PC+2].value;

        PC = (up << 8) + lo - start_of_code;
        Evaluate(PC);
    }

    else if (value == 0xCA){
        ///JZ Label
        if (getzero() == 0)
            return;

        int lo = opcode[PC+1].value;
        int up = opcode[PC+2].value;

        PC = (up << 8) + lo - start_of_code;
        Evaluate(PC);
    }

    else if (value == 0x3A){
        ///LDA Address
        int lo = opcode[PC+1].value;
        int up = opcode[PC+2].value;

        res = (up << 8) + lo - start_of_code;
        A = opcode[res].value;

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
