#include "Commands.h"

LoopCommandBase::LoopCommandBase(int loopsize) {
    this->loopsize_ = loopsize;
}

LoopEndCommand::LoopEndCommand(int loopsize) : LoopCommandBase(loopsize) {}

LoopStartCommand::LoopStartCommand(int loopsize) : LoopCommandBase(loopsize) {}

// DecrementValueCommand
CommandOutput DecrementValueCommand::Execute(BFProgramState& state) {
    state.data[state.currentData]--;
    return CommandOutput();
}

// IncrementValueCommand
CommandOutput IncrementValueCommand::Execute(BFProgramState& state) {
    state.data[state.currentData]++;
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
    return CommandOutput(1, true, state.data[state.currentData]);
}

// StepBackwardCommand
CommandOutput StepBackwardCommand::Execute(BFProgramState& state) {
    if (state.currentData == 0) {
        throw std::runtime_error("Runtime error. Selected cell number less than 0.");
    }
    state.currentData--;
    return CommandOutput();
}

// StepForwardCommand
CommandOutput StepForwardCommand::Execute(BFProgramState& state) {
    state.currentData++;
    if (state.currentData >= BF_DATA_SIZE) {
        throw std::runtime_error("Runtime error. Selected cell number exceeded 30000.");
    }
    return CommandOutput();
}



ICommand::~ICommand() {}