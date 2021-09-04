#include "pch.h"
#include "CppUnitTest.h"
#include <list>
#include <string>
#include <memory>
#include "../BrainFuck Compiler/Compiler.h"
#include "../BrainFuck Compiler/Invoker.h"
#include "../BrainFuck Compiler/CommandOutput.h"
#include "../BrainFuck Compiler/BFProgramState.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Tests
{
	// Testing Compiler
	TEST_CLASS(CompilerUnitTests)
	{
	public:
		
		/*Testing the Compile method of Compiler
		Empty code string given to compile
		Throws invalid_argument*/
		TEST_METHOD(Compile_TryCompileEmptyCode_ThrowsInvalidArgumentException)
		{
			// Arrange
			Compiler cmp("");
			// Act
			auto func = [&] { cmp.Compile(); };
			// Assert
			Assert::ExpectException<std::invalid_argument>(func);
		}
		/*Testing the Compile method of Compiler
		String with invalid loop brackets given
		Throws invalid_argument*/
		TEST_METHOD(Compile_TryCompileInvalidCode_ThrowsInvalidArgumentEcxeption) {
			// Arrange
			Compiler cmp("+++.[++[..]+>+.");
			// Act
			auto func = [&] { cmp.Compile(); };
			// Assert
			Assert::ExpectException<std::invalid_argument>(func);
		}
		/*Testing the Compile method of Compiler
		String with invalid command given
		Throws invalid_argument*/
		TEST_METHOD(Compile_TryCompileCodeWithWrongSymbols_ThrowsInvalidArgumentEcxeption) {
			// Arrange
			Compiler cmp("+++.>>a++");
			// Act
			auto func = [&] { cmp.Compile(); };
			// Assert
			Assert::ExpectException<std::invalid_argument>(func);
		}
		/*Testing the Compile method of Compiler
		Ten commands given
		Returns list with ten size*/
		TEST_METHOD(Compile_TryCompileTenCommandCode_ReturnsListTenSize) {
			// Arrange
			Compiler cmp("++.>++++>.");
			int expected = 10;
			// Act
			std::shared_ptr<std::vector<std::shared_ptr<ICommand>>> list = cmp.Compile();
			int actual = list->size();
			// Assert
			Assert::AreEqual(expected, actual);
		}
	};
	// Testing for commands
	TEST_CLASS(CommandsUnitTests) {
	public:
		/*Testing Execute method of StepForwardCommand
		Increments currentData in BFProgramState*/
		TEST_METHOD(StepForwardCommandExecute_GiveSimpleProgramState_IncrementsCurrentData) {
			// Arrange
			std::unique_ptr<BFProgramState> bfc(new BFProgramState);
			StepForwardCommand cmd;
			bfc->data.push_back(0);
			std::list<char>::iterator expected = bfc->currentData;
			expected++;
			// Act
			cmd.Execute(*bfc);
			std::list<char>::iterator actual = bfc->currentData;
			// Assert
			Assert::IsTrue(expected == actual);
		}
		/*Testing Execute method of StepBackwardCommand
		Decrements currentData in BFProgramState*/
		TEST_METHOD(StepBackwardCommandExecute_GiveSimpleProgramState_DecrementsCurrentData) {
			// Arrange
			std::unique_ptr<BFProgramState> bfc(new BFProgramState);
			StepBackwardCommand cmd;
			StepForwardCommand cmd2;
			cmd2.Execute(*bfc);
			std::list<char>::iterator expected = bfc->data.begin();
			// Act
			cmd.Execute(*bfc);
			std::list<char>::iterator actual = bfc->currentData;
			// Assert
			Assert::IsTrue(expected == actual);
		}
		/*Testing Execute method of IncrementValueCommand
		Increments current value of BFProgramState*/
		TEST_METHOD(IncrementValueCommandExecute_GiveSimpleProgramState_IncrementsCurrentValue) {
			// Arrange
			std::unique_ptr<BFProgramState> bfc(new BFProgramState);
			IncrementValueCommand cmd;
			(*bfc->currentData) = 10;
			int expected = 11;
			// Act
			cmd.Execute(*bfc);
			int actual = bfc->GetPointerValue();
			// Assert
			Assert::AreEqual(expected, actual);
		}
		/*Testing Execute method of DecrementValueCommand
		Decrements current value of BFProgramState*/
		TEST_METHOD(DecrementValueCommandExecute_GiveSimpleProgramState_DecrementsCurrentValue) {
			// Arrange
			std::unique_ptr<BFProgramState> bfc(new BFProgramState);
			DecrementValueCommand cmd;
			(*bfc->currentData) = 10;
			int expected = 9;
			// Act
			cmd.Execute(*bfc);
			int actual = bfc->GetPointerValue();
			// Assert
			Assert::AreEqual(expected, actual);
		}
		/*Testing Execute method of PrintValueCommand
		Returns CommandOutput with current char*/
		TEST_METHOD(PrintValueCommandExecute_GiveSimpleProgramState_ReturnsCommandOutputWithChar) {
			// Arrange
			std::unique_ptr<BFProgramState> bfc(new BFProgramState);
			PrintValueCommand cmd;
			(*bfc->currentData) = 40;
			char expected = 40;
			// Act
			CommandOutput co = cmd.Execute(*bfc);
			char actual = co.returned_char;
			// Assert
			Assert::IsTrue(co.anyReturns);
			Assert::AreEqual(expected, actual);
		}
		/*Testing Execute method of LoopStartCommand
		Returns CommandOutput with Step equals to loopsize*/
		TEST_METHOD(LoopStartCommandExecute_GiveEmptyProgramState_ReturnsCommandOutputWithStepEqualsLoopSize) {
			// Arrange
			std::unique_ptr<BFProgramState> bfc(new BFProgramState);
			const int loopsize = 15;
			LoopStartCommand cmd(loopsize);
			int expected = loopsize;
			// Act
			CommandOutput co = cmd.Execute(*bfc);
			int actual = co.step;
			// Assert
			Assert::AreEqual(expected, actual);
		}
		/*Testing Execute method of LoopEndCommand
		Returns CommandOutput with Step equals to negative loopsize*/
		TEST_METHOD(LoopEndCommandExecute_GiveNotEmptyProgramState_ReturnsCommandOutPutWithStepEqualsNegativeLoopSize) {
			// Arrange
			std::unique_ptr<BFProgramState> bfc(new BFProgramState);
			(*bfc->currentData) = 20;
			const int loopsize = 15;
			LoopEndCommand cmd(loopsize);
			int expected = loopsize * -1;
			// Act
			CommandOutput co = cmd.Execute(*bfc);
			int actual = co.step;
			// Assert
			Assert::AreEqual(expected, actual);
		}
		/*Testing Execute method of StepBackwardCommand
		Giving empty programstate
		Throws runtime_error*/
		TEST_METHOD(StepBackWardCommandExecute_GiveEmptyProgramState_ThrowsRuntimeError) {
			// Arrange
			std::unique_ptr<BFProgramState> bfc(new BFProgramState);
			StepBackwardCommand cmd;
			// Act
			auto func = [&] { cmd.Execute(*bfc); };
			// Assert
			Assert::ExpectException<std::runtime_error>(func);
		}
	};
	// Functional tests
	TEST_CLASS(FunctionalTests) {
		/*Testing compile and run process
		Giving code for Hello World!
		Returns Hello World!*/
		TEST_METHOD(HelloWorldCode_ReturnsHelloWorld) {
			// Arrange
			std::string code = "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++.+++++++++++++++++++++++++++++.+++++++..+++.-------------------------------------------------------------------------------.+++++++++++++++++++++++++++++++++++++++++++++++++++++++.++++++++++++++++++++++++.+++.------.--------.-------------------------------------------------------------------.-----------------------.";
			Compiler cmp(code);
			Invoker inv(cmp.Compile());
			std::string expected = "Hello World!\n";
			// Act
			std::string actual = inv.ExecuteCommands();
			// Assert
			Assert::AreEqual(expected, actual);
		}
		/*Testing compile and run process
		Giving different code for Hello World!
		Returns Hello World!*/
		TEST_METHOD(DifferentHelloWorldCode_ReturnsHelloWorld) {
			// Arrange
			std::string code = "++++++++++[>+++++++>++++++++++>+++>+<<<<-]>++.>+.+++++++..+++.>++.<<+++++++++++++++.>.+++.------.--------.>+.>.";
			Compiler cmp(code);
			Invoker inv(cmp.Compile());
			std::string expected = "Hello World!\n";
			// Act
			std::string actual = inv.ExecuteCommands();
			// Assert
			Assert::AreEqual(expected, actual);
		}
		/*Testing compile and run process
		Giving code that subtracts 7 from 40
		Returns 33 (!)*/
		TEST_METHOD(SubtractionOf40And7_Renurns33) {
			// Arrange
			std::string code = "++++++++++++++++++++++++++++++++++++++++>+++++++[<->-]<.";
			Compiler cmp(code);
			Invoker inv(cmp.Compile());
			std::string expected = "!";
			// Act
			std::string actual = inv.ExecuteCommands();
			// Assert
			Assert::AreEqual(expected, actual);
		}
		/*Testing compile and run process
		Giving code that returns english alphabet
		Returns english alphabet*/
		TEST_METHOD(CodeForAlphabet_ReturnsEnglishAlphabet) {
			// Arrange
			std::string code = "++++++++++[->++++++>++++++++++>+++<<<]>+++++>--->++>++[-<<<<+++++++++++++>>>>]+++++<<<<[->.+>.+>.>[->+>+<<]>>[-<<+>>]+<[>-<[-]]>[[-]++++++++++.<<++++++>>[-]]<<-<<<<]";
			Compiler cmp(code);
			Invoker inv(cmp.Compile());
			std::string expected = "Aa Bb Cc Dd Ee Ff \nGg Hh Ii Jj Kk Ll \nMm Nn Oo Pp Qq Rr \nSs Tt Uu Vv Ww Xx \nYy Zz ";
			// Act
			std::string actual = inv.ExecuteCommands();
			// Assert
			Assert::AreEqual(expected, actual);
		}
	};
}
