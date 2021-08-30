#ifndef COMMANDOUTPUT_H
#define COMMANDOUTPUT_H

// Used to return information from commands
struct CommandOutput {
	int step;
	bool anyReturns;
	char returned_char;
	CommandOutput(int step = 1, bool anyReturns = false, char returned_char = 0) {
		this->step = step;
		this->anyReturns = anyReturns;
		this->returned_char = returned_char;
	}
};

#endif