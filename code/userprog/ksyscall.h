#include "synchconsole.h"

#define NAME_SIZE 26
#define MAX_TABLE 10
#define BUFFER_SIZE 128

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

int SysCreate(char *name)
{
    int val, i;
    char s[NAME_SIZE];
    i = 0; 
    kernel->machine->ReadMem((int)name, 1, &val);
    while ((val != 0) && (i < NAME_SIZE-1)) {
        s[i++] = val;
        kernel->machine->ReadMem(((int)name+i), 1, &val);
    }
    s[i] = '\0';
    return kernel->fileSystem->Create(s);
}

OpenFileId SysOpen(char *name)
{
    int val, i;
    char s[NAME_SIZE];
    OpenFile *f;
    i = 0; 
    kernel->machine->ReadMem((int)name, 1, &val);
    while ((val != 0) && (i < NAME_SIZE-1)) {
        s[i++] = val;
        kernel->machine->ReadMem(((int)name+i), 1, &val);
    }
    s[i] = '\0';
    return kernel->fileSystem->OpenFid(s);
}

int
SysRead(char *usraddr, int nBytes, OpenFileId id)
{
    int val, i;
    i = 0;
    cout << "nBytes = " << nBytes << endl;
    cout << "id = " << id << endl;
    for (i = 0; nBytes > 4; nBytes-=4, i+=4) {
        kernel->fileSystem->Read(id, (char *)&val, 4);
        kernel->machine->WriteMem(((int)usraddr) + i, 4, val);
    }
    for (; nBytes > 0; nBytes--, i++) {
        kernel->fileSystem->Read(id, (char *)&val, 1);
        kernel->machine->WriteMem(((int)usraddr) + i, 1, val);
    }
    return i;
}


int
SysWrite(char *buffer, int size, OpenFileId id)
{
    int val, i = 0;
    for (i = 0; size > 4; size-=4, i+=4) {
        kernel->machine->ReadMem((int)buffer+i, 4, &val);
        kernel->fileSystem->Write(id, (char*)val, 4);
    }
    for (; size > 0; size--, i++) {
        kernel->machine->ReadMem((int)buffer+i, 1, &val);
        kernel->fileSystem->Write(id, (char*)&val, 1);
    }
    return 1;
}

int
SysClose(OpenFileId id)
{
    kernel->fileSystem->CloseFid(id);
    return 1;
}