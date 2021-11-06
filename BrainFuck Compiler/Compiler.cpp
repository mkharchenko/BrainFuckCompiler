#include "Compiler.h"
#include <stack>
#include <list>

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

std::shared_ptr<std::list<std::shared_ptr<ICommand>>> Compiler::ConvertCodeToCommandList() {
	std::shared_ptr<std::list<std::shared_ptr<ICommand>>> commandList(new std::list<std::shared_ptr<ICommand>>);
	const int code_length = code_.length();
	for (int i = 0; i < code_length; ++i) {
		switch (code_[i]) {
			case '>': {
				std::shared_ptr<ICommand> cmd(new StepForwardCommand());
				(*commandList).push_back(cmd);
				break;
			}
			case '<': {
				std::shared_ptr<ICommand> cmd(new StepBackwardCommand());
				(*commandList).push_back(cmd);
				break;
			}
			case '+': {
				std::shared_ptr<ICommand> cmd(new IncrementValueCommand());
				(*commandList).push_back(cmd);
				break;
			}
			case '-': {
				std::shared_ptr<ICommand> cmd(new DecrementValueCommand());
				(*commandList).push_back(cmd);
				break;
			}
			case '.': {
				std::shared_ptr<ICommand> cmd(new PrintValueCommand());
				(*commandList).push_back(cmd);
				break;
			}
			case '[': {
				std::string loop_code = "";
				i++;
				for (int depth = 1; i < code_length && depth > 0; ++i) {
					switch (code_[i]) {
					case '[': {
						depth++;
						break;
					}
					case ']': {
						depth--;
						break;
					}
					}
					if (depth > 0) {
						loop_code.push_back(code_[i]);
					}
				}
				i--;
				Compiler cmp(loop_code);
				std::shared_ptr<ICommand> cmd(new LoopCommand(cmp.Compile()));
				(*commandList).push_back(cmd);
				break;
			}
			default: {
				throw std::invalid_argument("Compilation error. Wrong command found in code.");
			}
		}
	}
	return commandList;
}

std::shared_ptr<std::list<std::shared_ptr<ICommand>>> Compiler::Compile() {
	if (code_.empty()) {
		throw std::invalid_argument("Compilation error. No code entered.");
	}
	if (!CheckCorrectBrackets()) {
		throw std::invalid_argument("Compilation error. Loop brackets syntax violated.");
	}
	const std::shared_ptr<std::list<std::shared_ptr<ICommand>>> commandList = ConvertCodeToCommandList();
	return commandList;
}