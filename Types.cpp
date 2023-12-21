#include "Types.h"

WORD makeWORD(BYTE high, BYTE low)
{
	WORD word = {0,0};
	word.HIGH = high;
	word.LOW = low;
	return word;
}