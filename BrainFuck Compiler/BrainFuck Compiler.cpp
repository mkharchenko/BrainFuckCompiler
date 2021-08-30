#include <iostream>
#include <string>
#include "Invoker.h"
#include "Compiler.h"

int main()
{
	std::string code;
	std::cout << "Enter BrainFuck code:\n";
	std::cin >> code;
	Compiler cmp(code);
	std::string result;
	std::shared_ptr<std::vector<std::shared_ptr<ICommand>>> commandList;
	try {
		commandList = cmp.Compile(); // step 1 - compile
		Invoker inv(commandList);
		result = inv.ExecuteCommands(); // step 2 - run
	}
	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
		return -1;
	}
	std::cout << std::endl << "Program output:\n" << result;
	return 0;
}