#include "Commands.h"
#include <string>

const std::string DEFAULT_COMMAND_OUTPUT = "";

// DecrementValueCommand
std::string DecrementValueCommand::Execute(std::shared_ptr<BFProgramState> state) {
    (*state->currentData)--;
    return DEFAULT_COMMAND_OUTPUT;
}

// IncrementValueCommand
std::string IncrementValueCommand::Execute(std::shared_ptr<BFProgramState> state) {
   (*state->currentData)++;
    return DEFAULT_COMMAND_OUTPUT;
}

// PrintValueCommand
std::string PrintValueCommand::Execute(std::shared_ptr<BFProgramState> state) {
    std::string res = "";
    res.push_back(state->GetPointerValue());
    return res;
}

// StepBackwardCommand
std::string StepBackwardCommand::Execute(std::shared_ptr<BFProgramState> state) {
    if (state->currentData == state->data.begin()) {
        throw std::runtime_error("Runtime error. Selected cell number less than 0.");
    }
    state->currentData--;
    return DEFAULT_COMMAND_OUTPUT;
}

// StepForwardCommand
std::string StepForwardCommand::Execute(std::shared_ptr<BFProgramState> state) {
    if (state->currentData == --(state->data.end())) {
        state->data.push_back(0);
    }
    state->currentData++;
    return DEFAULT_COMMAND_OUTPUT;
}


std::string LoopCommand::Execute(std::shared_ptr<BFProgramState> state) {
    Invoker inv(commandList_);
    std::string res = "";
    while (state->GetPointerValue()) {
        res += inv.ExecuteCommands(state);
    }
    return res;
}

LoopCommand::LoopCommand(std::shared_ptr<std::list<std::shared_ptr<ICommand>>> commandList) {
    commandList_ = commandList;
}


ICommand::~ICommand() {}