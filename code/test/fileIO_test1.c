#include "syscall.h"

int main(void)
{
    char test[] = "abcdefghijklmnopqrstuvwxyz";
    int success = Create("file1.txt");
    OpenFileId fid;
    int i;

    Print("Create file\n");
    if (success != 1) {
        Print("Failed on creating file\n");
        Halt();
    }
    Print("open file\n");
    fid = Open("file1.txt");
    if (fid <= 0) {
        Print("Failed on opening file\n");
        Halt();
    }
    Print("write file\n");
    for (i = 0; i < 26; i++) {
        Print("Index:");
        PrintInt(i);
        Print("\n");
        int count = Write(test + i, 1, fid);
        if (count != 1) {
            Print("Failed on writing file\n");
            Halt();
        }
    }
    success = Close(fid);
    if (success != 1) {
        Print("Failed on closing file\n");
        Halt();
    }
    Halt();
}