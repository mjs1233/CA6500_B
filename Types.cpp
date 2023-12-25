#include "Types.h"

WORD makeWORD(BYTE high, BYTE low)
{
	WORD word = {0,0};
	word.HIGH = high;
	word.LOW = low;
	return word;
}


WORD makeWORD(uint16_t value)
{
	WORD word = { 0,0 }; 
	word.VALUE = value;
	return word;
}