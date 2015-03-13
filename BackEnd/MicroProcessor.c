#include "MicroProcessor.h"

int main()
{
    start_of_code = 0x8000;
    micro_main("Start1: Mov A,B \n Hello: ACI 24 \n MOV A,B\n HLT \n CALL Hello \n Hello2: MVI A,3");
    return 0;
}

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


char* ThrowError(char* message, int pos){
   return "hello";
}
