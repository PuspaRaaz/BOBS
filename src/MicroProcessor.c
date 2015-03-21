#include "MicroProcessor.h"

int main(){
    start_of_code = 0x8000;
    const size_t total_size = 300;
    const size_t line_size = 30;

    char* tline = malloc(total_size);
    char* cline = malloc(line_size);

    strcpy(tline, " ");

    FILE* ifile = fopen("Instruction.txt","r");
    FILE* ofile = fopen("Opcode.txt","w");

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
   printf("found %s at pos %d\n",message,pos);
   //displayErrorMessage(message, start_of_code+pos);
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
    SP = 0;
    PSW = 0;
    IR = 0;

//Initialize the flags


    flag = 0;

}


/*
int my_itoa(int val, char* buf)
{
    const unsigned int radix = 10;
    char* p;
    unsigned int a;        //every digit
    int len;
    char* b;            //start of the digit char
    char temp;
    unsigned int u;

    p = buf;
    if (val < 0){
        *p++ = '-';
        val = 0 - val;
    }
    u = (unsigned int)val;

    b = p;
    do{
        a = u % radix;
        u /= radix;

        *p++ = a + '0';

    } while (u > 0);

    len = (int)(p - buf);
    *p-- = 0;
    //swap
    do{
        temp = *p;
        *p = *b;
        *b = temp;
        --p;
        ++b;

    } while (b < p);

    return len;
}

*/

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



