#pragma once
#include <cinttypes>
union WORD
{
	struct
	{
		uint8_t LOW;
		uint8_t HIGH;
	};

	uint16_t VALUE;
};

typedef uint8_t BYTE;

WORD makeWORD(BYTE high, BYTE low);
WORD makeWORD(uint16_t value);