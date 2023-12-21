#pragma once
#include "Types.h"
class Register_t
{
public:
	BYTE ACCUMULATOR = 0;
	BYTE INDEX_X = 0;
	BYTE INDEX_Y = 0;
	WORD PROGRAM_COUNTER = { 0,0 };
	BYTE STACK_POINTER = 0;
	union PROGRAM_STATUS_REGISTER
	{
		struct
		{
			uint8_t C : 1;//carry
			uint8_t Z : 1;//zero
			uint8_t I : 1;//IRQB disable
			uint8_t D : 1;//decimal mode
			uint8_t B : 1;//BRK command
			uint8_t U : 1;//always true
			uint8_t V : 1;//overflow
			uint8_t N : 1;//negative
		};
		uint8_t data = 0;
	}PROGRAM_STATUS;
};