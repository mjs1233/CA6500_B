#pragma once
#include "Operation.h"

#define FUCK false

constexpr char X = 'X';
constexpr char Y = 'Y';

class InternalExecutionOnMemoryData : public Operation_Base
{

public:
	BYTE ADL = 0;
	BYTE ADH = 0;
	BYTE BAL = 0;
	BYTE BAH = 0;
	BYTE IAL = 0;

	OPERATION_STATE execute(ADDRESSING_MODE addr_mode, PIN& _pin, Register_t& _register, uint8_t Tn) override
	{
		init();
		switch (addr_mode)
		{
		case ADDRESSING_MODE::IMMEDIATE:
			return ImmediateOperation(_pin, _register, Tn);
			break;
		case ADDRESSING_MODE::ZERO_PAGE:
			return ZeroPageOperation(_pin, _register, Tn);
			break;
		case ADDRESSING_MODE::ABSOULTE:
			return AbsoluteOperation(_pin, _register, Tn);
			break;
		case ADDRESSING_MODE::INDIRECT_X:
			IndirectXOperation(_pin, _register, Tn);
			break;
		case ADDRESSING_MODE::ABSOULTE_X:
			AbsoluteXYOperation(_pin, _register, Tn, X);
			break;
		case ADDRESSING_MODE::ABSOULTE_Y:
			AbsoluteXYOperation(_pin, _register, Tn, Y);
			break;
		case ADDRESSING_MODE::ZERO_PAGE_X:
			ZeroPageXYOperation(_pin, _register, Tn, X);
			break;
		case ADDRESSING_MODE::ZERO_PAGE_Y:
			ZeroPageXYOperation(_pin, _register, Tn, Y);
			break;
		case ADDRESSING_MODE::INDIRECT_Y:
			IndirectYOperation(_pin, _register, Tn);
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

	OPERATION_STATE ZeroPageOperation(PIN& _pin, Register_t& _register, uint8_t Tn)
	{
		switch (Tn)
		{
		case 0:
			return OPERATION_STATE::CALC_OPERAND;
			break;
		case 1:
			_register.PROGRAM_COUNTER.VALUE++;
			ADL = FetchMemory(_register.PROGRAM_COUNTER);
			return OPERATION_STATE::CALC_OPERAND;
			break;
		case 2:
			FetchMemory(makeWORD(0, ADL));
			return OPERATION_STATE::EXECUTE;
			break;
		case 3:
			return OPERATION_STATE::NEXT_OPERATION;
			break;
		default:
			return OPERATION_STATE::NONE;
			break;
		}
	}

	OPERATION_STATE AbsoluteOperation(PIN& _pin, Register_t& _register, uint8_t Tn)
	{
		switch (Tn)
		{
		case 0:
			return OPERATION_STATE::CALC_OPERAND;
			break;
		case 1:
			_register.PROGRAM_COUNTER.VALUE++;
			ADL = FetchMemory(_register.PROGRAM_COUNTER);
			return OPERATION_STATE::CALC_OPERAND;
			break;
		case 2:
			_register.PROGRAM_COUNTER.VALUE++;
			ADL = FetchMemory(_register.PROGRAM_COUNTER);
			return OPERATION_STATE::CALC_OPERAND;
			break;
		case 3:
			FetchMemory(makeWORD(ADH, ADL));
			return OPERATION_STATE::EXECUTE;
			break;
		case 4:
			return OPERATION_STATE::NEXT_OPERATION;
			break;
		default:
			return OPERATION_STATE::NONE;
			break;
		}
	}

	OPERATION_STATE AbsoluteXYOperation(PIN& _pin, Register_t& _register, uint8_t Tn, uint8_t target_register)
	{
		static bool page_cross = false;
		BYTE data = target_register == 'X' ? _register.INDEX_X : _register.INDEX_Y;
		switch (Tn)
		{
		case 0:
			return OPERATION_STATE::CALC_OPERAND;
			break;
		case 1:
			_register.PROGRAM_COUNTER.VALUE++;
			BAL = FetchMemory(_register.PROGRAM_COUNTER);
			return OPERATION_STATE::CALC_OPERAND;
			break;
		case 2:
			_register.PROGRAM_COUNTER.VALUE++;
			BAH = FetchMemory(_register.PROGRAM_COUNTER);
			return OPERATION_STATE::CALC_OPERAND;
			break;
		case 3:
			uint16_t temp = static_cast<uint16_t>(BAL) + data;
			if (temp > 255)
			{
				ADL = static_cast<BYTE>(temp);
				FetchMemory(makeWORD(ADH, ADL));
				page_cross = true;
				return OPERATION_STATE::CALC_OPERAND;
			}
			else
			{
				ADL = static_cast<BYTE>(temp);
				ADH = BAH;
				FetchMemory(makeWORD(ADH, ADL));
				page_cross = false;
				return OPERATION_STATE::EXECUTE;
			}
			break;
		case 4:
			if (!page_cross)
			{
				return OPERATION_STATE::NEXT_OPERATION;
			}
			else
			{
				ADH += 1;
				FetchMemory(makeWORD(ADH, ADL));
				return OPERATION_STATE::EXECUTE;
			}
			break;
		case 5:
			return OPERATION_STATE::NEXT_OPERATION;
			break;
		default:
			return OPERATION_STATE::NONE;
			break;
		}
	}

	OPERATION_STATE IndirectXOperation(PIN& _pin, Register_t& _register, uint8_t Tn) {
		switch (Tn)
		{
		case 0:
			return OPERATION_STATE::CALC_OPERAND;
			break;
		case 1:
			_register.PROGRAM_COUNTER.VALUE++;
			BAL = FetchMemory(_register.PROGRAM_COUNTER);
			return OPERATION_STATE::CALC_OPERAND;
			break;
		case 2:
			FetchMemory(makeWORD(0, BAL));
			return OPERATION_STATE::CALC_OPERAND;
			break;
		case 3:
			ADL = FetchMemory(makeWORD(0, BAL + _register.INDEX_X));
			return OPERATION_STATE::CALC_OPERAND;
			break;
		case 4:
			ADH = FetchMemory(makeWORD(00, BAL + _register.INDEX_X + 1));
			return OPERATION_STATE::CALC_OPERAND;
			break;
		case 5:
			FetchMemory(makeWORD(ADH, ADL));
			return OPERATION_STATE::EXECUTE;
			break;
		case 6:
			return OPERATION_STATE::NEXT_OPERATION;
			break;
		default:
			return OPERATION_STATE::NONE;
			break;
		}
	}

	OPERATION_STATE ZeroPageXYOperation(PIN& _pin, Register_t& _register, uint8_t Tn, uint8_t target_register)
	{
		BYTE data = target_register == 'X' ? _register.INDEX_X : _register.INDEX_Y;
		switch (Tn)
		{
		case 0:
			return OPERATION_STATE::CALC_OPERAND;
			break;
		case 1:
			_register.PROGRAM_COUNTER.VALUE++;
			ADL = FetchMemory(_register.PROGRAM_COUNTER);
			return OPERATION_STATE::CALC_OPERAND;
			break;
		case 2:
			FetchMemory(makeWORD(0, BAL));
			return OPERATION_STATE::CALC_OPERAND;
			break;
		case 3:
			FetchMemory(makeWORD(00, BAL + data));
			return OPERATION_STATE::EXECUTE;
			break;
		case 4:
			return OPERATION_STATE::NEXT_OPERATION;
			break;
		default:
			return OPERATION_STATE::NONE;
			break;
		}
	}

	OPERATION_STATE IndirectYOperation(PIN& _pin, Register_t& _register, uint8_t Tn)
	{
		static bool page_cross = false;
		switch (Tn)
		{
		case 0:
			return OPERATION_STATE::CALC_OPERAND;
			break;
		case 1:
			_register.PROGRAM_COUNTER.VALUE++;
			IAL = FetchMemory(_register.PROGRAM_COUNTER);
			return OPERATION_STATE::CALC_OPERAND;
			break;
		case 2:
			BAL = FetchMemory(makeWORD(0, IAL));
			return OPERATION_STATE::CALC_OPERAND;
			break;
		case 3:
			BAH = FetchMemory(makeWORD(0, IAL + 1));
			return OPERATION_STATE::CALC_OPERAND;
			break;
		case 4:
			uint16_t temp = static_cast<uint16_t>(BAL) + _register.INDEX_Y;
			if (temp > 255)
			{
				ADL = static_cast<BYTE>(temp);
				FetchMemory(makeWORD(ADH, ADL));
				page_cross = true;
				return OPERATION_STATE::CALC_OPERAND;
			}
			else
			{
				ADL = static_cast<BYTE>(temp);
				ADH = BAH;
				FetchMemory(makeWORD(ADH, ADL));
				page_cross = false;
				return OPERATION_STATE::EXECUTE;
			}
			break;
		case 5:
			if (!page_cross)
			{
				return OPERATION_STATE::NEXT_OPERATION;
			}
			else
			{
				ADH += 1;
				FetchMemory(makeWORD(ADH, ADL));
				return OPERATION_STATE::EXECUTE;
			}
			break;
		case 6:
			return OPERATION_STATE::NEXT_OPERATION;
			break;
		default:
			return OPERATION_STATE::NONE;
			break;
		}
	}

	void init() {
		ADL = 0;
		ADH = 0;
		BAL = 0;
		BAH = 0;
		IAL = 0;
	}
};