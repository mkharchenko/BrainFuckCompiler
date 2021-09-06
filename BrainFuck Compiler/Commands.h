#ifndef COMMANDS_H
#define COMMANDS_H
#include "BFProgramState.h"
#include "Invoker.h"
#include <list>

class Invoker;

/* Interface for Command design pattern
Each command has execute and undo methods */
class ICommand {
public:
    virtual std::string Execute(std::shared_ptr<BFProgramState> state) = 0;
    virtual ~ICommand() = 0;
};

// > command
class StepForwardCommand : public ICommand {
public:
    virtual std::string Execute(std::shared_ptr<BFProgramState> state);
};

// < command
class StepBackwardCommand : public ICommand {
public:
    virtual std::string Execute(std::shared_ptr<BFProgramState> state);
};

// . command
class PrintValueCommand : public ICommand {
public:
    virtual std::string Execute(std::shared_ptr<BFProgramState> state);
};

// + command
class IncrementValueCommand : public ICommand {
public:
    virtual std::string Execute(std::shared_ptr<BFProgramState> state);
};

// - command
class DecrementValueCommand : public ICommand {
public:
    virtual std::string Execute(std::shared_ptr<BFProgramState> state);
};

// Loop command
class LoopCommand : public ICommand {
private:
    std::shared_ptr<std::list<std::shared_ptr<ICommand>>> commandList_;
public:
    LoopCommand(std::shared_ptr<std::list<std::shared_ptr<ICommand>>> commandList);
    virtual std::string Execute(std::shared_ptr<BFProgramState> state);
};

#endif