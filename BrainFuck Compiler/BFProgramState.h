#ifndef BFPROGRAMSTATE_H
#define BFPROGRAMSTATE_H
#include <iostream>
#include <list>

// Saves data on tape and pointer of running program
struct BFProgramState
{
	std::list<char> data;
	std::list<char>::iterator currentData;
	BFProgramState();
	char GetPointerValue();
};

#endif