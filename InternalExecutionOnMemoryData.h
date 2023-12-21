#pragma once
#include "Operation.h"
class InternalExecutionOnMemoryData : public Operation_Base
{

public:
	OPERATION_STATE execute(ADDRESSING_MODE addr_mode, PIN& _pin, Register_t& _register, uint8_t Tn) override
	{
		switch (addr_mode)
		{
		case ADDRESSING_MODE::IMMEDIATE:
			return ImmediateOperation(_pin, _register, Tn);
			break;
		case ADDRESSING_MODE::ZERO_PAGE:
			break;
		case ADDRESSING_MODE::ABSOULTE:
			break;
		case ADDRESSING_MODE::INDIRECT_X:
			break;
		case ADDRESSING_MODE::ABSOULTE_X:
			break;
		case ADDRESSING_MODE::ABSOULTE_Y:
			break;
		case ADDRESSING_MODE::ZERO_PAGE_X:
			break;
		case ADDRESSING_MODE::ZERO_PAGE_Y:
			break;
		case ADDRESSING_MODE::INDIRECT_Y:
			break;
		default:
			break;
		}
	}

private:
	OPERATION_STATE ImmediateOperation(PIN& _pin, Register_t& _register, uint8_t Tn)
	{
		switch (Tn)
		{
		case 0:
			return OPERATION_STATE::CALC_OPERAND;
			break;
		case 1:
			_register.PROGRAM_COUNTER.VALUE++;
			FetchMemory(_register.PROGRAM_COUNTER);
			return OPERATION_STATE::EXECUTE;
		case 2:
			return OPERATION_STATE::NEXT_OPERATION;
		default:
			return OPERATION_STATE::NONE;
			break;
		}
	}
};