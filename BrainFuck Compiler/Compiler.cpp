#include "Compiler.h"
#include <stack>

void Compiler::SetCodeString(std::string code) {
	this->code_ = code;
}

Compiler::Compiler(std::string code) {
	SetCodeString(code);
}

bool Compiler::CheckCorrectBrackets() {
	std::stack<char> stack;
	for (char c : code_) {
		switch (c) {
		case '[': stack.push(']'); break;
		case ']':
			if (stack.empty() || stack.top() != c) {
				return false;
			}
			stack.pop();
			break;
		default:
			break;
		}
	}
	return stack.empty();
}

std::shared_ptr<std::vector<std::shared_ptr<ICommand>>> Compiler::Compile() {
	std::shared_ptr<std::vector<std::shared_ptr<ICommand>>> commandList_(new std::vector<std::shared_ptr<ICommand>>);
	if (code_.empty()) {
		throw std::invalid_argument("Compilation error. No code entered.");
	}
	if (!CheckCorrectBrackets()) {
		throw std::invalid_argument("Compilation error. Loop brackets syntax violated.");
	}
	commandList_->resize(code_.length());
	const int code_length = code_.length();
	for (int i = 0; i < code_length; ++i) {
		switch (code_[i]) {
			case '>': {
				std::shared_ptr<ICommand> cmd(new StepForwardCommand());
				(*commandList_)[i] = cmd;
				break;
			}
			case '<': {
				std::shared_ptr<ICommand> cmd(new StepBackwardCommand());
				(*commandList_)[i] = cmd;
				break;
			}
			case '+': {
				std::shared_ptr<ICommand> cmd(new IncrementValueCommand());
				(*commandList_)[i] = cmd;
				break;
			}
			case '-': {
				std::shared_ptr<ICommand> cmd(new DecrementValueCommand());
				(*commandList_)[i] = cmd;
				break;
			}
			case '.': {
				std::shared_ptr<ICommand> cmd(new PrintValueCommand());
				(*commandList_)[i] = cmd;
				break;
			}
			case '[': {
				int loopsize = 1;
				for (int j = i + 1, depth = 1; j < code_length && depth > 0; ++j) {
					switch (code_[j]) {
						case '[': {
							depth++;
							break;
						}
						case ']': {
							depth--;
							break;
						}
					}
					loopsize++;
				}
				std::shared_ptr<ICommand> cmd(new LoopStartCommand(loopsize));
				(*commandList_)[i] = cmd;
				break;
			}
			case ']': {
				int loopsize = 0;
				for (int j = i - 1, depth = 1; j < code_length && depth > 0; --j) {
					switch (code_[j])
					{
						case '[': {
							depth--;
							break;
						}
						case ']': {
							depth++;
							break;
						}
					}
					loopsize++;
				}
				std::shared_ptr<ICommand> cmd(new LoopEndCommand(loopsize));
				(*commandList_)[i] = cmd;
				break;
			}
			default: {
				throw std::invalid_argument("Compilation error. Wrong command found in code.");
			}
		}
	}
	return commandList_;
}