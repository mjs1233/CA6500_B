#pragma once
#include "Operation.h"

class PushProcessorStatusInstruction : public Operation_Base
{
public:

	OPERATION_STATE execute(ADDRESSING_MODE addr_mode, PIN& _pin, Register_t& _register, uint8_t Tn) override
	{
		switch (Tn)
		{
		case 0:
			return OPERATION_STATE::CALC_OPERAND;
		case 1:
			_register.PROGRAM_COUNTER.VALUE++;
			FetchMemory(_register.PROGRAM_COUNTER);
			return OPERATION_STATE::CALC_OPERAND;
		case 2:
			WriteMemory(makeWORD((uint16_t)_register.STACK_POINTER + 0x100), _register.PROGRAM_STATUS.data);
			_register.STACK_POINTER -= 1;
			return OPERATION_STATE::CALC_OPERAND;
		case 3:
			return OPERATION_STATE::NEXT_OPERATION;
		default:
			return OPERATION_STATE::NONE;
			break;
		}
	}
};


class PushRegisterAInstruction : public Operation_Base
{
public:

	OPERATION_STATE execute(ADDRESSING_MODE addr_mode, PIN& _pin, Register_t& _register, uint8_t Tn) override
	{
		switch (Tn)
		{
		case 0:
			return OPERATION_STATE::CALC_OPERAND;
		case 1:
			_register.PROGRAM_COUNTER.VALUE++;
			FetchMemory(_register.PROGRAM_COUNTER);
			return OPERATION_STATE::CALC_OPERAND;
		case 2:
			WriteMemory(makeWORD((uint16_t)_register.STACK_POINTER + 0x100), _register.ACCUMULATOR);
			_register.STACK_POINTER -= 1;
			return OPERATION_STATE::CALC_OPERAND;
		case 3:
			return OPERATION_STATE::NEXT_OPERATION;
		default:
			return OPERATION_STATE::NONE;
			break;
		}
	}
};


class PullProcessorStatusInstruction : public Operation_Base
{
public:

	OPERATION_STATE execute(ADDRESSING_MODE addr_mode, PIN& _pin, Register_t& _register, uint8_t Tn) override
	{
		switch (Tn)
		{
		case 0:
			return OPERATION_STATE::CALC_OPERAND;
		case 1:
			_register.PROGRAM_COUNTER.VALUE += 1;
			FetchMemory(_register.PROGRAM_COUNTER);
			return OPERATION_STATE::CALC_OPERAND;
		case 2:
			FetchMemory(makeWORD((uint16_t)_register.STACK_POINTER + 0x100));
			return OPERATION_STATE::CALC_OPERAND;
		case 3:
			_register.STACK_POINTER += 1;
			_register.PROGRAM_STATUS.data = FetchMemory(makeWORD((uint16_t)_register.STACK_POINTER + 0x100));
			return OPERATION_STATE::CALC_OPERAND;
		case 4:
			return OPERATION_STATE::NEXT_OPERATION;
		default:
			return OPERATION_STATE::NONE;
			break;
		}
	}
};


class PullRegisterAInstruction : public Operation_Base
{
public:

	OPERATION_STATE execute(ADDRESSING_MODE addr_mode, PIN& _pin, Register_t& _register, uint8_t Tn) override
	{
		switch (Tn)
		{
		case 0:
			return OPERATION_STATE::CALC_OPERAND;
		case 1:
			_register.PROGRAM_COUNTER.VALUE += 1;
			FetchMemory(_register.PROGRAM_COUNTER);
			return OPERATION_STATE::CALC_OPERAND;
		case 2:
			FetchMemory(makeWORD((uint16_t)_register.STACK_POINTER + 0x100));
			return OPERATION_STATE::CALC_OPERAND;
		case 3:
			_register.STACK_POINTER += 1;
			_register.ACCUMULATOR = FetchMemory(makeWORD((uint16_t)_register.STACK_POINTER + 0x100));
			return OPERATION_STATE::CALC_OPERAND;
		case 4:
			return OPERATION_STATE::NEXT_OPERATION;
		default:
			return OPERATION_STATE::NONE;
			break;
		}
	}
};



class JumptoSubroutineInstruction : public Operation_Base
{
public:
	BYTE ADL = 0;
	OPERATION_STATE execute(ADDRESSING_MODE addr_mode, PIN& _pin, Register_t& _register, uint8_t Tn) override
	{
		switch (Tn)
		{
		case 0:
			return OPERATION_STATE::CALC_OPERAND;
		case 1:
			_register.PROGRAM_COUNTER.VALUE += 1;
			ADL = FetchMemory(_register.PROGRAM_COUNTER);

		}
	}
};