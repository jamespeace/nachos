#include "userkernel.h"
#include "synchconsole.h"

int SysPrint(int *input)
{
    int i, val;
    int memAddr = (int)input;
    i = 0;

    input++;
    kernel->machine->ReadMem(int(memAddr+i), 1, &val);

    for (i = 1; 0 != val; i++) {
        kernel->synchconsoleoutput->PutChar(val);
        kernel->machine->ReadMem(memAddr+i, 1, &val);
    } 
    return i;
}