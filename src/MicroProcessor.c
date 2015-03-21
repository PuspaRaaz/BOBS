#include "MicroProcessor.h"

int microMain(){
    initialize();
    const size_t total_size = 300;
    const size_t line_size = 30;

    char* tline = malloc(total_size);
    char* cline = malloc(line_size);

    strcpy(tline, " ");

    FILE* ifile = fopen("bin/Instruction.txt","r");
    FILE* ofile = fopen("bin/Opcode.txt","w");

    if (!(ifile)){
        printf("File could not be located");
        return -1;
    }

    while (fgets(cline, line_size, ifile) != NULL){
        strcat(tline,cline);
        strcat(tline," ");
    }
    micro_main(tline,ofile);
    free(tline);
    free(cline);

    fclose(ifile);
    fclose(ofile);
    return 0;
}

//Throw error
void ThrowError(char* message, int pos){
   printf("%s at pos %d\n",message,pos);
   displayErrorMessage(message, start_of_code+pos);
}

void initialize(){

//Initialize the registers
    A = 0;
    B = 0;
    C = 0;
    D = 0;
    E = 0;
    H = 0;
    L = 0;
    M = 0;
    PC = 0;
    PSW = 0;
    IR = 0;

//Initialize the flags
    flag = 0;

//initialize stack
    init_stack();

//Base address
    baseADD = 0x40;
    Port[0] = 100;
    Port[1] = 0;
    Port[2] = 0;
    Port[3] = 0;

}

int getzero(){
    return (flag >> 6) & 1;
}

int getcarry(){
    return (flag >> 0) & 1;
}
int getsign(){
    return (flag >> 7) & 1;
}
int getparity(){
    return (flag >> 2) & 1;
}
int getAF(){
    return (flag >> 4) & 1;
}

int Parity(int x){
    int p = 1;
    while (x){
        p ^= x&1;
        x >>= 1; // at each iteration, we shift the input one bit to the right
    }
    return p;
}

void setzero(){
    flag |= (1 << 6);
}
void resetzero() {
    flag &= ~(1 << 6);
}
void setcarry() {
    flag |= (1 << 0);
}
void resetcarry() {
    flag &= ~(1 << 0);
}
void setsign() {
    flag |= (1 << 7);
}
void resetsign() {
    flag &= ~(1 << 7);
}
void setparity() {
    flag |= (1 << 2);
}
void resetparity() {
    flag &= ~(1 << 2);
}
void setAF() {
    flag |= (1 << 4);
}
void resetAF() {
    flag &= ~(1 << 4);
}

void complement_carry() {
    flag ^= 1 << 0;
}




