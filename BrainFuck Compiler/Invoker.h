#ifndef INVOKER_H
#define INVOKER_H
#include <iostream>
#include <list>
#include <string>
#include "Commands.h"
#include "CommandOutput.h"

class ICompilerState;
class ICommand;
struct BrainFuckProgram;

/* Runs compiled program
Taking commandList and executing it
Returns result string of a program*/
class Invoker {
private:
    // vector of commands (compiled program)
    std::shared_ptr<std::list<std::shared_ptr<ICommand>>> commandList_;
    // struct that contains current state of brainfuck program (data array, pointer to currentdata)
    std::shared_ptr<BFProgramState> programstate_;
    // Inits programstate_
    void Init();
    std::string RunProgram();
public:
    Invoker(std::shared_ptr<std::list<std::shared_ptr<ICommand>>> commandList);
    void SetCommandList(std::shared_ptr<std::list<std::shared_ptr<ICommand>>> commandList);
    /* Executing commands from list consistently.
    Each command execution returns CommandOutput with next information:
    - Step to the next command in vector
    - Is there any returns from the command
    - Command return (char)*/
    std::string ExecuteCommands();
    std::string ExecuteCommands(std::shared_ptr<BFProgramState> programstate);
};

#endif