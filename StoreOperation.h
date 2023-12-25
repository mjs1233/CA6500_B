#pragma once
#include "Operation.h"

class StoreOperation : public Operation_Base
{
public:
	BYTE ADL = 0;
	BYTE ADH = 0;
	BYTE BAL = 0;
	BYTE BAH = 0;
	BYTE IAL = 0;
	BYTE IAH = 0;



	OPERATION_STATE execute(ADDRESSING_MODE addr_mode, PIN& _pin, Register_t& _register, uint8_t Tn) override
	{
		switch (addr_mode)
		{
		case ADDRESSING_MODE::ZERO_PAGE:
			ZeroPageOperation(_pin, _register, Tn);
			break;
		case ADDRESSING_MODE::ABSOULTE:
			AbsoluteOperation(_pin, _register, Tn);
			break;
		case ADDRESSING_MODE::INDIRECT_X:
			IndirectXOperation(_pin, _register, Tn);
			break;
		case ADDRESSING_MODE::ABSOULTE_X:
			AbsoluteXYOperation(_pin, _register, Tn,'X');
			break;
		case ADDRESSING_MODE::ABSOULTE_Y:
			AbsoluteXYOperation(_pin, _register, Tn, 'Y');
			break;
		case ADDRESSING_MODE::ZERO_PAGE_X:
			ZeroPageXYOperation(_pin, _register, Tn, 'X');
			break;
		case ADDRESSING_MODE::ZERO_PAGE_Y:
			ZeroPageXYOperation(_pin, _register, Tn, 'Y');
			break;
		case ADDRESSING_MODE::INDIRECT_Y:
			IndirectYOperation(_pin, _register, Tn);
			break;
		default:
			break;
		}
	}

private:
	OPERATION_STATE ZeroPageOperation(PIN& _pin, Register_t& _register, uint8_t Tn)
	{
		switch (Tn)
		{
		case 0:
			return OPERATION_STATE::CALC_OPERAND;
		case 1:
			_register.PROGRAM_COUNTER.VALUE++;
			ADL = FetchMemory(_register.PROGRAM_COUNTER);
			return OPERATION_STATE::EXECUTE;
		case 2:
			WriteMemory(makeWORD(0, ADL), _pin.DataBus.getData());
		case 3:
			return OPERATION_STATE::NEXT_OPERATION;
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
		case 1:
			_register.PROGRAM_COUNTER.VALUE++;
			ADL = FetchMemory(_register.PROGRAM_COUNTER);
			return OPERATION_STATE::CALC_OPERAND;
		case 2:
			_register.PROGRAM_COUNTER.VALUE++;
			ADH = FetchMemory(_register.PROGRAM_COUNTER);
			return OPERATION_STATE::EXECUTE;
		case 3:
			WriteMemory(makeWORD(ADH, ADL), _pin.DataBus.getData());
			return OPERATION_STATE::CALC_OPERAND;
		case 4:
			return OPERATION_STATE::NEXT_OPERATION;
		default:
			return OPERATION_STATE::NONE;
			break;
		}
	}

	OPERATION_STATE IndirectXOperation(PIN& _pin, Register_t& _register, uint8_t Tn)
	{
		switch (Tn)
		{
		case 0:
			return OPERATION_STATE::CALC_OPERAND;
		case 1:
			_register.PROGRAM_COUNTER.VALUE++;
			BAL = FetchMemory(_register.PROGRAM_COUNTER);
			return OPERATION_STATE::CALC_OPERAND;
		case 2:
			FetchMemory(makeWORD(0, BAL));
			return OPERATION_STATE::CALC_OPERAND;
		case 3:
			ADL = FetchMemory(makeWORD(0, BAL + _register.INDEX_X));
			return OPERATION_STATE::CALC_OPERAND;
		case 4:
			ADH = FetchMemory(makeWORD(0, BAL + _register.INDEX_X + 1));
			return OPERATION_STATE::EXECUTE;
		case 5:
			WriteMemory(makeWORD(BAH, BAL), _pin.DataBus.getData());
			return OPERATION_STATE::CALC_OPERAND;
		case 6:
			return OPERATION_STATE::NEXT_OPERATION;
		default:
			return OPERATION_STATE::NONE;
		}
	}

	OPERATION_STATE AbsoluteXYOperation(PIN& _pin, Register_t& _register, uint8_t Tn, uint8_t target_register)
	{
		BYTE data = target_register == 'X' ? _register.INDEX_X : _register.INDEX_Y;
		switch (Tn)
		{
		case 0:
			return OPERATION_STATE::CALC_OPERAND;
		case 1:
			_register.PROGRAM_COUNTER.VALUE++;
			BAL = FetchMemory(_register.PROGRAM_COUNTER);
			return OPERATION_STATE::CALC_OPERAND;
		case 2:
			_register.PROGRAM_COUNTER.VALUE++;
			BAH = FetchMemory(_register.PROGRAM_COUNTER);
			return OPERATION_STATE::CALC_OPERAND;
		case 3:
			uint16_t temp = static_cast<uint16_t>(BAL) + data;
			ADL = static_cast<uint8_t>(temp);
			if (temp > 255)
			{
				ADH = BAH + 1;
			}
			else
			{
				ADH = BAH;
			}
			FetchMemory(makeWORD(ADH, ADL));
			return OPERATION_STATE::EXECUTE;
		case 4:
			WriteMemory(makeWORD(ADH, ADL), _pin.DataBus.getData());
			return OPERATION_STATE::CALC_OPERAND;
		case 5:
			return OPERATION_STATE::NEXT_OPERATION;
		default:
			return OPERATION_STATE::NONE;
		};
	}


	OPERATION_STATE ZeroPageXYOperation(PIN& _pin, Register_t& _register, uint8_t Tn, uint8_t target_register)
	{
		BYTE data = target_register == 'X' ? _register.INDEX_X : _register.INDEX_Y;
		switch (Tn)
		{
		case 0:
			return OPERATION_STATE::CALC_OPERAND;
		case 1:
			_register.PROGRAM_COUNTER.VALUE++;
			BAL = FetchMemory(_register.PROGRAM_COUNTER);
			return OPERATION_STATE::CALC_OPERAND;
		case 2:
			FetchMemory(makeWORD(0, BAL));
			return OPERATION_STATE::EXECUTE;
		case 3:
			WriteMemory(makeWORD(0, BAL + data),_pin.DataBus.getData());
			return OPERATION_STATE::CALC_OPERAND;
		case 4:
			return OPERATION_STATE::NEXT_OPERATION;
		default:

		}
	}



	OPERATION_STATE IndirectYOperation(PIN& _pin, Register_t& _register, uint8_t Tn)
	{
		switch (Tn)
		{
		case 0:
			return OPERATION_STATE::CALC_OPERAND;
		case 1:
			_register.PROGRAM_COUNTER.VALUE++;
			IAL = FetchMemory(_register.PROGRAM_COUNTER);
			return OPERATION_STATE::CALC_OPERAND;
		case 2:
			BAL = FetchMemory(makeWORD(0, IAL));
			return OPERATION_STATE::CALC_OPERAND;
		case 3:
			BAH = FetchMemory(makeWORD(0, IAL + 1));
			return OPERATION_STATE::CALC_OPERAND; 
		case 4:
			ADL = BAL + _register.INDEX_Y;
			ADH = BAH;
			FetchMemory(makeWORD(ADH, ADL));
			return OPERATION_STATE::EXECUTE;
		case 5:
			WriteMemory(makeWORD(ADH, ADL),_pin.DataBus.getData());
			return OPERATION_STATE::CALC_OPERAND;
		case 6:
			return OPERATION_STATE::NEXT_OPERATION;
		default:
			return OPERATION_STATE::NONE;
		}
	}
};