#include "Opcode.h"

void Opcode_main(Memory* Op, int pCounter){
    PC = pCounter - start_of_code;  //this will be the current pos of our opcode
    opcode = Op;
    hasHalted = 0;
    Evaluate(PC);
    printflags();
}

void printflags(){
    printf("A: %X\n B: %X\n C: %X\n D: %X\n E: %X\n H: %X\n L: %X\n M: %X\n ",A,B,C,D,E,H,L,M);
    printf("S %d, CY %d, Z %d, AC %d, P %d ", getsign(),getcarry(),getzero(),getAF(),getparity());
}
void Evaluate(int pCounter){
    while(1){
        Eval_Opcode(opcode[PC].value);
        if (hasHalted)
                return;
        PC ++;
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

    else if (value == 0x0A){
        ///LDAX B
        int lo = C;
        int up = B;

        res = (up << 8) + lo - start_of_code;
        A = opcode[res].value;
    }

    else if (value == 0x1A){
        ///LDAX D
        int lo = E;
        int up = D;

        res = (up << 8) + lo - start_of_code;
        A = opcode[res].value;
    }

    else if (value == 0x2A){
        ///LHLD Address
        int lo = opcode[PC+1].value;
        int up = opcode[PC+2].value;

        res = (up << 8) + lo - start_of_code;
        L = opcode[res].value;
        H = opcode[res+1].value;
    }

    else if (value == 0x01){
        ///LXI B
        int lo = opcode[PC+1].value;
        int up = opcode[PC+2].value;

        B = up;
        C = lo;
    }

    else if (value == 0x11){
        ///LXI D
        int lo = opcode[PC+1].value;
        int up = opcode[PC+2].value;

        D = up;
        E = lo;
    }

    else if (value == 0x21){
        ///LXI H
        int lo = opcode[PC+1].value;
        int up = opcode[PC+2].value;

        H = up;
        L = lo;
    }

    else if (value == 0x31){
        ///LXI SP
        int lo = opcode[PC+1].value;
        int up = opcode[PC+2].value;
        res = (up << 8) + lo;
        SP = res - start_of_code;
    }


    else if (value == 0x7F){
        ///MOV A,A
    } else if (value == 0x78){
        ///MOV A,B
        A = B;
    } else if (value == 0x79){
        ///MOV A,C
        A = C;
    } else if (value == 0x7A){
        ///MOV A,D
        A = D;
    } else if (value == 0x7B){
        ///MOV A,E
        A = E;
    } else if (value == 0x7C){
        ///MOV A,H
        A = H;
    } else if (value == 0x7D){
        ///MOV A,L
        A = L;
    } else if (value == 0x7E){
        ///MOV A,M
        A = M;
    }


    else if (value == 0x47){
        ///MOV B,A
        B = A;
    } else if (value == 0x40){
        ///MOV B,B
    } else if (value == 0x41){
        ///MOV B,C
        B = C;
    } else if (value == 0x42){
        ///MOV A,D
        B = D;
    } else if (value == 0x43){
        ///MOV A,E
        B = E;
    } else if (value == 0x44){
        ///MOV A,H
        B = H;
    } else if (value == 0x45){
        ///MOV A,L
        B = L;
    } else if (value == 0x46){
        ///MOV A,M
        B = M;
    }

    else if (value == 0x4F){
        ///MOV C,A
        C = A;
    } else if (value == 0x48){
        ///MOV C,B
        C = B;
    } else if (value == 0x49){
        ///MOV C,C
    } else if (value == 0x4A){
        ///MOV C,D
        C = D;
    } else if (value == 0x4B){
        ///MOV C,E
        C = E;
    } else if (value == 0x4C){
        ///MOV C,H
        C = H;
    } else if (value == 0x4D){
        ///MOV C,L
        C = L;
    } else if (value == 0x4E){
        ///MOV C,M
        C = M;
    }

    else if (value == 0x57){
        ///MOV D,A
        D = A;
    } else if (value == 0x50){
        ///MOV D,B
        D = B;
    } else if (value == 0x51){
        ///MOV D,C
        D = C;
    } else if (value == 0x52){
        ///MOV D,D
    } else if (value == 0x53){
        ///MOV D,E
        D = E;
    } else if (value == 0x54){
        ///MOV D,H
        D = H;
    } else if (value == 0x55){
        ///MOV D,L
        D = L;
    } else if (value == 0x56){
        ///MOV D,M
        D = M;
    }

    else if (value == 0x5F){
        ///MOV E,A
        E = A;
    } else if (value == 0x58){
        ///MOV E,B
        E = B;
    } else if (value == 0x59){
        ///MOV E,C
        E = C;
    } else if (value == 0x5A){
        ///MOV E,D
        E = D;
    } else if (value == 0x5B){
        ///MOV E,E
    } else if (value == 0x5C){
        ///MOV E,H
        E = H;
    } else if (value == 0x5D){
        ///MOV E,L
        E = L;
    } else if (value == 0x5E){
        ///MOV E,M
        E = M;
    }

    else if (value == 0x67){
        ///MOV H,A
        H = A;
    } else if (value == 0x60){
        ///MOV H,B
        H = B;
    } else if (value == 0x61){
        ///MOV H,C
        H = C;
    } else if (value == 0x62){
        ///MOV H,D
        H = D;
    } else if (value == 0x63){
        ///MOV H,E
        H = E;
    } else if (value == 0x64){
        ///MOV H,H
    } else if (value == 0x65){
        ///MOV H,L
        H = L;
    } else if (value == 0x66){
        ///MOV H,M
        H = M;
    }

    else if (value == 0x6F){
        ///MOV L,A
        L = A;
    } else if (value == 0x68){
        ///MOV L,B
        L = B;
    } else if (value == 0x69){
        ///MOV L,C
        L = C;
    } else if (value == 0x6A){
        ///MOV L,D
        L = D;
    } else if (value == 0x6B){
        ///MOV L,E
        L = E;
    } else if (value == 0x6C){
        ///MOV L,H
        L = H;
    } else if (value == 0x6D){
        ///MOV L,L
    } else if (value == 0x6E){
        ///MOV L,M
        L = M;
    }


    else if (value == 0x77){
        ///MOV M,A
        M = A;
    } else if (value == 0x70){
        ///MOV M,B
        M = B;
    } else if (value == 0x71){
        ///MOV M,C
        M = C;
    } else if (value == 0x72){
        ///MOV M,D
        M = D;
    } else if (value == 0x73){
        ///MOV M,E
        M = E;
    } else if (value == 0x74){
        ///MOV M,H
        M = H;
    } else if (value == 0x75){
        ///MOV M,L
        M = L;
    }

    else if (value == 0x3E){
        ///MVI A, DATA
        A = opcode[++PC].value;
    }
    else if (value == 0x06){
        ///MVI B, DATA
        B = opcode[++PC].value;
    }
    else if (value == 0x0E){
        ///MVI C, DATA
        C = opcode[++PC].value;
    }
    else if (value == 0x16){
        ///MVI D, DATA
        D = opcode[++PC].value;
    }
    else if (value == 0x1E){
        ///MVI E, DATA
        E = opcode[++PC].value;
    }
    else if (value == 0x26){
        ///MVI H, DATA
        H = opcode[++PC].value;
    }
    else if (value == 0x2E){
        ///MVI L, DATA
        L = opcode[++PC].value;
    }
    else if (value == 0x36){
        ///MVI M, DATA
        M = opcode[++PC].value;
    }

    else if(value == 0x00){
        ///NOP
    }

    else if (value == 0xB7){
        ///ORA A
        A = A | A;
        updateFlags(A,0,0);
        resetAF();
        resetcarry();
    }

    else if (value == 0xB0){
        ///ORA B
        A = A | B;
        updateFlags(A,0,0);
        resetAF();
        resetcarry();
    }

    else if (value == 0xB1){
        ///ORA C
        A = A | C;
        updateFlags(A,0,0);
        resetAF();
        resetcarry();
    }

    else if (value == 0xB2){
        ///ORA D
        A = A | D;
        updateFlags(A,0,0);
        resetAF();
        resetcarry();
    }

    else if (value == 0xB3){
        ///ORA E
        A = A | E;
        updateFlags(A,0,0);
        resetAF();
        resetcarry();
    }

    else if (value == 0xB4){
        ///ORA H
        A = A | H;
        updateFlags(A,0,0);
        resetAF();
        resetcarry();
    }

    else if (value == 0xB5){
        ///ORA L
        A = A | L;
        updateFlags(A,0,0);
        resetAF();
        resetcarry();
    }

    else if (value == 0xB6){
        ///ORA M
        A = A | M;
        updateFlags(A,0,0);
        resetAF();
        resetcarry();
    }

    else if (value == 0xF6){
        ///ORI DATA
        A = A | opcode[++PC].value;
        updateFlags(A,0,0);
        resetAF();
        resetcarry();
    }

    else if (value == 0xD3){
        ///OUT port-address
        op1 = opcode[++PC].value - baseADD;
        Port[op1] = A;
    }

    else if (value == 0xE9){
        ///PCHL
        PC = (H << 8) + L;
    }

    else if (value == 0xD1){
        ///POP B
        C = pop();
        B = pop();
    }

    else if (value == 0xE1){
        ///POP D
        E = pop();
        D = pop();
    }

    else if (value == 0xF1){
        ///POP PSW
        flag = pop();
        A = pop();
    }

    else if (value == 0xC5){
        ///PUSH B
        push(B);
        push(C);
    }

    else if (value == 0xD5){
        ///PUSH D
        push(D);
        push(E);
    }

    else if (value == 0xE5){
        ///PUSH PSW
        push(A);
        push(flag);
    }

    else if (value == 0x17){
        ///RAL
        op1 = getcarry();
        if (A & 0x80) setcarry();
        else resetcarry();

        A = A << 1;
        A = A & 0xff;
        A |= op1;
    }

    else if (value == 0x1F){
        ///RAR
        op1 = A & 1;
        op2 = getcarry();
        A = A >> 1;
        A |= (op2 << 7);

        if (op1) setcarry();
        else resetcarry();
    }

    else if (value == 0x07){
        ///RLC
        op1 = (A & 0x80) >> 7; //msb
        A = A << 1;
        A = A & 0xff;
        A |= op1;
        if (op1) setcarry();
        else resetcarry();
    }

    else if(value == 0x0F){
        ///RRC
        op1 = A & 1;
        A = A >> 1;
        A |= op1 << 7 ;
        if (op1) setcarry();
        else resetcarry();
    }

    else if (value == 0xD8){
        ///RC
        if (getcarry() == 0) return;
        PC = pop();
        Evaluate(PC);
    }

    else if (value == 0xC9){
        ///RET
        PC = pop();
        Evaluate(PC);
    }

    else if (value == 0xF8){
        ///RM
        if (getsign() == 0) return;
        PC = pop();
        Evaluate(PC);
    }

    else if (value == 0xD0){
        ///RNC
        if (getcarry() == 1) return;
        PC = pop();
        Evaluate(PC);
    }

    else if (value == 0xC0){
        ///RNZ
        if (getzero() == 1) return;
        PC = pop();
        Evaluate(PC);
    }

     else if (value == 0xC8){
        ///RZ
        if (getzero() == 0) return;
        PC = pop();
        Evaluate(PC);
    }

    else if (value == 0xF0){
        ///RP
        if (getsign() == 1) return;
        PC = pop();
        Evaluate(PC);
    }

    else if (value == 0xE8){
        ///RPE
        if (getparity() == 0) return;
        PC = pop();
        Evaluate(PC);
    }

    else if (value == 0xE0){
        ///RP0
        if (getparity() == 1) return;
        PC = pop();
        Evaluate(PC);
    }

    else if (value == 0x76){
        ///HLT
        hasHalted = 1;
    }

    else if (value == 0xEF){
        ///RST 5
        hasHalted = 0;
    }

    else if (value == 0x9F){
        ///SBB A
        op1 = A;
        op2 = ~A & 0xff;
        res = op1 + op2;
        updateFlags(res,op1,op2);
        A = res & 0xff;
    }




}
