
#include "ppi.h"

void PPIinit(PPI *mppi, int addr)
{
    mppi->baseaddr = addr;
    mppi->pa.io = mppi->pb.io = mppi->pc.io = 1;
    mppi->pa.mode = mppi->pb.mode = mppi->pc.mode = 0;
    mppi->pa.val = mppi->pb.val = mppi->pc.val = 0x00;
    mppi->strA = mppi->strB = 0x00;
}
void ModeSelection(PPI *mppi)
{
    if(mppi->cw & 0x80)
        mppi->ppiMode = 1;
    else
        mppi->ppiMode = 0;
    if(mppi->ppiMode) // I/O Mode
    {

        if(mppi->cw & 0x60)
            mppi->pa.mode = 2;
        else
        {
            if (mppi->cw & 0x20) mppi->pa.mode = 1;
            else mppi->pa.mode = 0;
        }


        mppi->pa.io = ((mppi->cw & 0x10)?1:0);
        int cu= ((mppi->cw & 0x08)?1:0);
        mppi->pb.mode = ((mppi->cw & 0x04)?1:0);
        mppi->pb.io = ((mppi->cw & 0x02)?1:0);
        int cl = ((mppi->cw & 0x01)?1:0);
        mppi->pc.io = cu + cl;
    }
    else  //BSR Mode
    {
        int temp = mppi->cw & 0x0e;
        temp >>= 1;

        if(mppi->cw & 0x01)
            mppi->pc.val |= 1 << temp;
        else
            mppi->pc.val &= ~(1<<temp);
    }
}
void Write(int addr, int val, PPI *mppi)
{
    int cur_addr = addr - mppi->baseaddr;
    switch(cur_addr)
    {
    case 0:
        {
            if(mppi->pa.io)
                return;
            mppi->pa.val = val;
            break;
        }
    case 1:
        {
            if(mppi->pb.io)
                return;
            mppi->pb.val = val;
            break;
        }
    case 2:
        {
            if(mppi->pc.io == 1) //pc upper is in output mode
            {
                mppi->pc.val = val & 0xf0;
                mppi->pc.val >>= 4;
                break;

            }
            else if(mppi->pc.io == 2) //pc lower is in output mode
            {
                mppi->pc.val = val & 0x0f;
                printf("%d", mppi->pc.val);
                break;
            }
            else if(mppi->pc.io == 0) //both in output mode
            {
                mppi->pc.val = val;
                break;
            }
            else
                return;
        }
    case 3:
        {
            mppi->cw = val;
            ModeSelection(mppi);
            break;
        }
    }
}
int Read(int addr, PPI *mppi)
{
    int temp = 0;
    int cur_addr = addr - mppi->baseaddr;
    if(cur_addr >=0 && cur_addr <= 3)

        switch(cur_addr)
    {
    case 0:
        printf("%d", mppi->pa.io);
        if(mppi->pa.io)
        {
            temp = mppi->pa.val;
            break;
        }

    case 1:
        if(mppi->pb.io)
        {
            temp = mppi->pa.val;
            break;

        }
        case 2:
        {
            if(mppi->pc.io == 1){
                temp = mppi->pc.val & 0x0f;
                break;
            }
            if(mppi->pc.io == 2){
                temp = mppi->pc.val & 0xf0;
                break;
            }
        }

    }
    return temp;
}
void PPIportShow(PPI *mppi)
{
    printf("Port A: %d\n", mppi->pa.val);
    printf("Port B: %d\n", mppi->pb.val);
    printf("Port C: %d\n", mppi->pc.val);
}
