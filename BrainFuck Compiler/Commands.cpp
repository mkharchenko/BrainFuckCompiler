#include "Commands.h"

LoopCommandBase::LoopCommandBase(int loopsize) {
    this->loopsize_ = loopsize;
}

LoopEndCommand::LoopEndCommand(int loopsize) : LoopCommandBase(loopsize) {}

LoopStartCommand::LoopStartCommand(int loopsize) : LoopCommandBase(loopsize) {}

// DecrementValueCommand
CommandOutput DecrementValueCommand::Execute(BFProgramState& state) {
    (*state.currentData)--;
    return CommandOutput();
}

// IncrementValueCommand
CommandOutput IncrementValueCommand::Execute(BFProgramState& state) {
    (*state.currentData)++;
    return CommandOutput();
}

// LoopEndCommand
CommandOutput LoopEndCommand::Execute(BFProgramState& state) {
    if (state.GetPointerValue()) {
        return CommandOutput(this->loopsize_ * -1);
    }
    else {
        return CommandOutput();
    }
}

// LoopStartCommand
CommandOutput LoopStartCommand::Execute(BFProgramState& state) {
    if (state.GetPointerValue()) {
        return CommandOutput();
    }
    else {
        return CommandOutput(this->loopsize_);
    }
}

// PrintValueCommand
CommandOutput PrintValueCommand::Execute(BFProgramState& state) {
    return CommandOutput(1, true, state.GetPointerValue());
}

// StepBackwardCommand
CommandOutput StepBackwardCommand::Execute(BFProgramState& state) {
    if (state.currentData == state.data.begin()) {
        throw std::runtime_error("Runtime error. Selected cell number less than 0.");
    }
    state.currentData--;
    return CommandOutput();
}

// StepForwardCommand
CommandOutput StepForwardCommand::Execute(BFProgramState& state) {
    if (state.currentData == --(state.data.end())) {
        state.data.push_back(0);
    }
    state.currentData++;
    return CommandOutput();
}



ICommand::~ICommand() {}