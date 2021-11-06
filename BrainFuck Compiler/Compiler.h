#ifndef COMPILER_H
#define COMPILER_H
#include <string>
#include <list>
#include <memory>
#include "Commands.h"

// Compiles program from code to list of commands
class Compiler
{
private:
	std::string code_;
	// Checks loop brackets syntax
	bool CheckCorrectBrackets();
	/*Converts brainfuck symbol
	into Command object*/
	std::shared_ptr<std::list<std::shared_ptr<ICommand>>> ConvertCodeToCommandList();
public:
	Compiler(std::string code);
	// Compiles program code to a list of commands and returns it
	std::shared_ptr<std::list<std::shared_ptr<ICommand>>> Compile();
	// Sets code string
	void SetCodeString(std::string code);
};

#endif