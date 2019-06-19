#include "syscall.h"

int main(void)
{
    int i;

    PrintInt(0);
    PrintInt(0);
    PrintInt(0);
    for (i = 0; i < 10; i++){
        PrintInt(i);
    }
    Halt();
}