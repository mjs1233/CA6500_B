#pragma once
#include "Types.h"
#include "PIN.h"
#include "Register.h"


BYTE FetchMemory(WORD address);
void WriteMemory(WORD address, BYTE data);