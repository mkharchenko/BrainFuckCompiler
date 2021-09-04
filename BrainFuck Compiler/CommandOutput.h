#ifndef COMMANDOUTPUT_H
#define COMMANDOUTPUT_H
#include <string>

// Used to return information from commands
struct CommandOutput {
	std::string returned_result;
	CommandOutput(std::string returned_result = "") {
		this->returned_result = returned_result;
	}
};

#endif