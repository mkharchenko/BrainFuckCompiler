#ifndef BFPROGRAMSTATE_H
#define BFPROGRAMSTATE_H
#include <iostream>

const int BF_DATA_SIZE = 30000;

// Saves data on tape and pointer of running program
struct BFProgramState
{
	char data[BF_DATA_SIZE];
	size_t currentData;
	BFProgramState();
	char GetPointerValue();
};

#endif