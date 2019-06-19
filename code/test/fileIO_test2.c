#include "syscall.h"

int main(void)
{
	// you should run fileIO_test1 first before running this one
	char test[26];
	char check[] = "abcdefghijklmnopqrstuvwxyz";
	OpenFileId fid;
	int count, success, i;
	fid = Open("file1.txt");
	Print("fid = ");
	PrintInt(fid);
	if (fid < 0) {Print("Failed on opening file"); Halt();}
	count = Read(test, 26, fid);
	if (count != 26) {Print("Failed on reading file"); Halt();}
	success = Close(fid);
	if (success != 1) {Print("Failed on closing file"); Halt();}
	for (i = 0; i < 26; ++i) {
		if (test[i] != check[i]) {Print("Failed: reading wrong result"); Halt();}
	}
	Print("Passed! ^_^");
	Halt();
}

