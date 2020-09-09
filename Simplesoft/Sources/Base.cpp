#include "Base.h"

Integer GetEnoughCapacity(Integer capacity, Integer const count)
{
	if (capacity == 0x0I64)
		capacity = 0x1I64;
	do
	{
		capacity <<= 0x1I64;
		if (capacity < 0x0I64)
		{
			capacity = MaxIntegerValue;
			break;
		}
	}
	while (capacity < count);
	return capacity;
}