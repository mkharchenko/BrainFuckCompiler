#ifndef COMPILER_H
#define COMPILER_H
#include <string>
#include <vector>
#include <memory>
#include "Commands.h"

// Compiles program from code to list of commands
class Compiler
{
private:
	std::string code_;
	// Checks loop brackets syntax
	bool CheckCorrectBrackets();
public:
	Compiler(std::string code);
	// Compiles program code to a list of commands and returns it
	std::shared_ptr<std::vector<std::shared_ptr<ICommand>>> Compile();
	// Sets code string
	void SetCodeString(std::string code);
};

#endif