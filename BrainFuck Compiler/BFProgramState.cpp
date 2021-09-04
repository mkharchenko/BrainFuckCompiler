#include "BFProgramState.h"

BFProgramState::BFProgramState() {
	data.push_back(0);
	currentData = data.begin();
}

char BFProgramState::GetPointerValue() {
	return *currentData;
}