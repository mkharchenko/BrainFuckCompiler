#include "BFProgramState.h"

BFProgramState::BFProgramState() {
	currentData = 0;
	memset(data, 0, sizeof(data));
}

char BFProgramState::GetPointerValue() {
	return data[currentData];
}