#pragma once
#include <vector>

#include "BUS.h"
#include "Types.h"
#include "PIN.h"
#include "Operation.h"
#include "SingleByteInstruction.h"
class CPU
{
	int32_t Tn = 0;
	Register_t _register;
	PIN pin;
	std::vector<std::unique_ptr<Operation_Base>> operations;

	BYTE opCode = 0;
	OPERATION_STATE operation_state = OPERATION_STATE::NONE;
	OPERATION_TYPE operation_type = OPERATION_TYPE::NONE;
	ADDRESSING_MODE addressing_mode = ADDRESSING_MODE::IMMEDIATE;

public:
	CPU()
	{
		//make shared each operation class
		//then push operation class to operations vector 
		operations.push_back(std::make_unique<SingleByteInstruction>());
		//...
	}


	void execute_clock()
	{

		operation_state = operations[static_cast<int32_t>(operation_type)]->execute(addressing_mode, pin, _register, Tn);
	
		if (operation_state == OPERATION_STATE::NEXT_OPERATION)
		{
			fetchNextInstruction();
			Tn = 0;
			//run operation with new instruction
			operation_state = operations[static_cast<int32_t>(operation_type)]->execute(addressing_mode, pin, _register, Tn);
		}
		
		
		if (operation_state == OPERATION_STATE::EXECUTE)
		{
			//run execution function
		}
	
	}

private:

	void fetchNextInstruction()
	{
		operation_type = getOperationType(opCode);
		addressing_mode = getAddressingMode(opCode);
	}


	OPERATION_TYPE getOperationType(BYTE opCode)
	{
		return OPERATION_TYPE::NONE;
	}

	ADDRESSING_MODE getAddressingMode(BYTE opCode)
	{
		return ADDRESSING_MODE::IMMEDIATE;
	}
	
};

