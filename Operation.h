#pragma once
#include <memory>


#include "PIN.h"
#include "Types.h"
#include "Register.h"
#include "ExternalDeviceControl.h"
#include "MemoryHandle.h"



enum class RW : bool
{
	WRITE = 0,
	READ = 1
};

enum class ADDRESSING_MODE
{
	IMMEDIATE,
	ZERO_PAGE,
	ABSOULTE,
	INDIRECT_X,
	ABSOULTE_X,
	ABSOULTE_Y,
	ZERO_PAGE_X,
	ZERO_PAGE_Y,
	INDIRECT_Y
};

enum class OPERATION_TYPE
{
	NONE = 0,
	SINGLE_BYTE = 1,
	INTERNAL_EXECUTION_ON_MEMORY_DATA = 2,
	//add
};


enum class OPERATION_STATE
{
	NONE,
	EXECUTE,
	CALC_OPERAND,
	NEXT_OPERATION
};


class Operation_Base
{
public:
	virtual OPERATION_STATE execute(ADDRESSING_MODE addr_mode, PIN& _pin, Register_t& _register, uint8_t Tn) = 0;
};

