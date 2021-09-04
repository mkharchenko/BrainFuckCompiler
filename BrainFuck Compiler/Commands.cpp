#include "Commands.h"
#include <string>

// DecrementValueCommand
CommandOutput DecrementValueCommand::Execute(std::shared_ptr<BFProgramState> state) {
    (*state->currentData)--;
    return CommandOutput();
}

// IncrementValueCommand
CommandOutput IncrementValueCommand::Execute(std::shared_ptr<BFProgramState> state) {
   (*state->currentData)++;
    return CommandOutput();
}

// PrintValueCommand
CommandOutput PrintValueCommand::Execute(std::shared_ptr<BFProgramState> state) {
    std::string res = "";
    res.push_back(state->GetPointerValue());
    return res;
}

// StepBackwardCommand
CommandOutput StepBackwardCommand::Execute(std::shared_ptr<BFProgramState> state) {
    if (state->currentData == state->data.begin()) {
        throw std::runtime_error("Runtime error. Selected cell number less than 0.");
    }
    state->currentData--;
    return CommandOutput();
}

// StepForwardCommand
CommandOutput StepForwardCommand::Execute(std::shared_ptr<BFProgramState> state) {
    if (state->currentData == --(state->data.end())) {
        state->data.push_back(0);
    }
    state->currentData++;
    return CommandOutput();
}


CommandOutput LoopCommand::Execute(std::shared_ptr<BFProgramState> state) {
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