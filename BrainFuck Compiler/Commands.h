#ifndef COMMANDS_H
#define COMMANDS_H
#include "BFProgramState.h"
#include "Invoker.h"
#include "CommandOutput.h"

class Invoker;

/* Interface for Command design pattern
Each command has execute and undo methods */
class ICommand {
public:
    virtual CommandOutput Execute(BFProgramState& state) = 0;
    virtual ~ICommand() = 0;
};

class LoopCommandBase : public ICommand {
protected:
    int loopsize_;
public:
    LoopCommandBase(int loopsize);
};

// > command
class StepForwardCommand : public ICommand {
public:
    virtual CommandOutput Execute(BFProgramState& state);
};

// < command
class StepBackwardCommand : public ICommand {
public:
    virtual CommandOutput Execute(BFProgramState& state);
};

// . command
class PrintValueCommand : public ICommand {
public:
    virtual CommandOutput Execute(BFProgramState& state);
};

// [ command
class LoopStartCommand : public LoopCommandBase {
public:
    virtual CommandOutput Execute(BFProgramState& state);
    LoopStartCommand(int loopsize);
};

// ] command
class LoopEndCommand : public LoopCommandBase {
public:
    virtual CommandOutput Execute(BFProgramState& state);
    LoopEndCommand(int loopsize);
};

// + command
class IncrementValueCommand : public ICommand {
public:
    virtual CommandOutput Execute(BFProgramState& state);
};

// - command
class DecrementValueCommand : public ICommand {
public:
    virtual CommandOutput Execute(BFProgramState& state);
};

#endif