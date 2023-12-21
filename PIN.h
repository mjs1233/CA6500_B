#pragma once
#include "BUS.h"
#include "Types.h"
class PIN
{
public:
	BUS<WORD> AddressBus;
	BUS<WORD> DataBus;
	BUS<RW> ReadWritePin;

};