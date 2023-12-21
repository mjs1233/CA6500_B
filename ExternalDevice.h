#pragma once
#include "Types.h"
#include "PIN.h"
class ExternalDevice_Base
{
public:
	virtual void init() = 0;
	virtual BYTE execute(PIN& pin) = 0;
};