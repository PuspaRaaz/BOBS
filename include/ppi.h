#ifndef PPI_H_INCLUDED
#define PPI_H_INCLUDED
#include <math.h>

typedef struct
{
    int mode, io;
    int val;
}Port;

typedef struct
{
    int baseaddr;
    int strA, strB;
    int ppiMode;
    int cw;
    Port pa, pb, pc;
}PPI;

void ControlWord(int cword, int addr, PPI *mppi);
void PPIinit(PPI *mppi, int addr);
void ModeSelection(PPI *mppi);
void Write(int addr, int val, PPI *mppi);
int Read(int addr, PPI *mppi);
void PPIportShow(PPI *mppi);



#endif // PPI_H_INCLUDED
