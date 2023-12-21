#pragma once
#include "Operation.h"
class SingleByteInstruction : public Operation_Base
{

public:
	OPERATION_STATE execute(ADDRESSING_MODE addr_mode, PIN& _pin, Register_t& _register, uint8_t Tn) override
	{
		switch (Tn)
		{
		case 0:
			return OPERATION_STATE::EXECUTE;
		case 1:
			//get next opcode (discard)
			_register.PROGRAM_COUNTER.VALUE += 1;
			FetchMemory(_register.PROGRAM_COUNTER);
			return OPERATION_STATE::CALC_OPERAND;
		case 2:
			return OPERATION_STATE::NEXT_OPERATION;
		default:
			return OPERATION_STATE::NONE;
			break;
		}
	}
	
};