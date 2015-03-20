#include "MicroProcessor.h"

int microMain(){
    start_of_code = 0x8000;
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
    displayErrorMessage(message, pos);
}

void initialize(){

//Initialize the registers
    Reg.A = 0;
    Reg.B = 0;
    Reg.C = 0;
    Reg.D = 0;
    Reg.E = 0;
    Reg.H = 0;
    Reg.L = 0;
    Reg.M = 0;

//Initialize the flags


    Flag.AC = 0;
    Flag.C = 0;
    Flag.P = 0;
    Flag.S = 0;
    Flag.Z = 0;


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

