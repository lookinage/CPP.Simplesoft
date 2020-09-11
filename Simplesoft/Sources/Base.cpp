#include "Base.h"

Integer GetEnoughCapacity
(
	Integer const capacity, 
	Integer const count
)
{
	Integer result;

	result = capacity == Zero ? One : capacity;
	do
	{
		result += result;
		if (result < Zero)
		{
			result = MaxUnsignedInteger;
			break;
		}
	}
	while (result < count);
	return result;
}