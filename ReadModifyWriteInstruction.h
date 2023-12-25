#pragma once

#include "Operation.h"

class ReadModifyWriteOperation : public Operation_Base {
public:
	BYTE ADL = 0;
	BYTE ADH = 0;
	BYTE BAL = 0;
	BYTE BAH = 0;
	BYTE buffer = 0;

	ReadModifyWriteOperation() = default;

	virtual OPERATION_STATE execute(ADDRESSING_MODE addr_mode, PIN& _pin, Register_t& _register, uint8_t Tn) override {
		switch (addr_mode)
		{
		case ADDRESSING_MODE::ZERO_PAGE:
			return ZeroPageOperation(_pin, _register, Tn);
			break;
		case ADDRESSING_MODE::ABSOULTE:
			return AbsoluteOperation(_pin, _register, Tn);
			break;
		case ADDRESSING_MODE::ABSOULTE_X:
			return AbsoluteXOperation(_pin, _register, Tn);
			break;
		case ADDRESSING_MODE::ZERO_PAGE_X:
			return ZeroPageXOperation(_pin, _register, Tn);
			break;
		default:
			return OPERATION_STATE::NONE;
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
			break;
		case 1:
			_register.PROGRAM_COUNTER.VALUE++;
			ADL = FetchMemory(_register.PROGRAM_COUNTER);
			return OPERATION_STATE::CALC_OPERAND;
			break;
		case 2:
			buffer = FetchMemory(makeWORD(0, ADL));
			return OPERATION_STATE::CALC_OPERAND;
			break;
		case 3:
			WriteMemory(makeWORD(0, ADL), buffer);
			_pin.DataBus.setData(buffer);
			return OPERATION_STATE::EXECUTE;
			break;
		case 4:
			WriteMemory(makeWORD(0, ADL), _pin.DataBus.getData());
			return OPERATION_STATE::CALC_OPERAND;
			break;
		case 5:
			return OPERATION_STATE::NEXT_OPERATION;
			break;
		default:
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
			ADH = FetchMemory(_register.PROGRAM_COUNTER);
			return OPERATION_STATE::CALC_OPERAND;
			break;
		case 3:
			buffer = FetchMemory(makeWORD(ADH, ADL));
			return OPERATION_STATE::CALC_OPERAND;
			break;
		case 4:
			WriteMemory(makeWORD(ADH, ADL), buffer);
			_pin.DataBus.setData(buffer);
			return OPERATION_STATE::EXECUTE;
			break;
		case 5:
			WriteMemory(makeWORD(ADH, ADL), _pin.DataBus.getData());
			return OPERATION_STATE::CALC_OPERAND;
			break;
		case 6:
			return OPERATION_STATE::NEXT_OPERATION;
			break;
		default:
			return OPERATION_STATE::NONE;
			break;
		}
	}

	OPERATION_STATE ZeroPageXOperation(PIN& _pin, Register_t& _register, uint8_t Tn)
	{
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
			ADL = BAL + _register.INDEX_X;
			buffer = FetchMemory(makeWORD(0, ADL));
			return OPERATION_STATE::CALC_OPERAND;
			break;
		case 4:
			WriteMemory(makeWORD(0, ADL), buffer);
			_pin.DataBus.setData(buffer);
			return OPERATION_STATE::CALC_OPERAND;
			break;
		case 5:
			WriteMemory(makeWORD(0, ADL), _pin.DataBus.getData());
			return OPERATION_STATE::EXECUTE;
			break;
		case 6:
			WriteMemory(makeWORD(0, ADL), _pin.DataBus.getData());
			return OPERATION_STATE::CALC_OPERAND;
			break;
		case 7:
			return OPERATION_STATE::NEXT_OPERATION;
			break;
		default:
			break;
		}
	}

	OPERATION_STATE AbsoluteXOperation(PIN& _pin, Register_t& _register, uint8_t Tn)
	{
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
			ADL = BAL + _register.INDEX_X;
			uint16_t temp = static_cast<uint16_t>(BAL);
			if (temp + _register.INDEX_X > 255)
			{
				ADH = BAH + 1;
			}
			else
			{
				ADH = BAH;
			}
			FetchMemory(makeWORD(ADH, ADL));
			return OPERATION_STATE::CALC_OPERAND;
			break;
		case 4:
			buffer = FetchMemory(makeWORD(ADH, ADL));
			return OPERATION_STATE::CALC_OPERAND;
			break;
		case 5:
			WriteMemory(makeWORD(ADH, ADL), buffer);
			_pin.DataBus.setData(buffer);
			return OPERATION_STATE::EXECUTE;
			break;
		case 6:
			WriteMemory(makeWORD(ADH, ADL), _pin.DataBus.getData());
			return OPERATION_STATE::CALC_OPERAND;
			break;
		case 7:
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
		buffer = 0;
	}

};