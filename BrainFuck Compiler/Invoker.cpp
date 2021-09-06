#include "Invoker.h"
#include <string>

void Invoker::SetCommandList(std::shared_ptr<std::list<std::shared_ptr<ICommand>>> commandList) {
	this->commandList_ = commandList;
}

Invoker::Invoker(std::shared_ptr<std::list<std::shared_ptr<ICommand>>> commandList) {
	SetCommandList(commandList);
}

void Invoker::Init() {
	programstate_.reset(new BFProgramState);
}

std::string Invoker::RunProgram() {
	std::string result = "";
	for (auto it = (*commandList_).begin(); it != (*commandList_).end(); it++) {
		std::string command_out = (*it)->Execute(programstate_);
		result += command_out;
	}
	return result;
}

std::string Invoker::ExecuteCommands() {
	Init();
	return RunProgram();
}

std::string Invoker::ExecuteCommands(std::shared_ptr<BFProgramState> programstate) {
	programstate_ = programstate;
	return RunProgram();
}