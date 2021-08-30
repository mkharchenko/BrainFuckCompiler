#include "Invoker.h"
#include <string>

void Invoker::SetCommandList(std::shared_ptr<std::vector<std::shared_ptr<ICommand>>> commandList) {
	this->commandList_ = commandList;
}

Invoker::Invoker(std::shared_ptr<std::vector<std::shared_ptr<ICommand>>> commandList) {
	SetCommandList(commandList);
}

void Invoker::Init() {
	programstate_.reset(new BFProgramState);
}

std::string Invoker::ExecuteCommands() {
	Init();
	std::string result = "";
	for (int i = 0; i < commandList_->size() && i >= 0;) {
		CommandOutput co = (*commandList_)[i]->Execute(*programstate_);
		i += co.step;
		if (co.anyReturns) {
			result.push_back(co.returned_char);
		}
	}
	programstate_.reset();
	return result;
}