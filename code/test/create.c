#include "syscall.h"

int main(void)
{
    int success;
    success = Create("hello.txt");
    PrintInt(success);
    Halt();
}