#include "DynamicStorageTest.h"

namespace SetsTests
{
	Integer DynamicStorageTest( )
	{
		Integer const testCount = 0xFI64;

		Sets::DynamicStorage<Integer> storage = Sets::DynamicStorage<Integer>(0x0I64);
		if (storage.GetCapacity( ) != 0x0I64)
			return MaxUnsignedInteger - 0x2I64;
		for (Integer offset = 0x0I64; offset != testCount; offset++)
		{
			if (storage.GetCapacity( ) != testCount)
				return MaxUnsignedInteger - 0x1I64;
			storage[offset] = offset;
			for (Integer checkingOffset = 0x0I64; checkingOffset != offset; checkingOffset++)
				if (storage[checkingOffset] != checkingOffset)
					return checkingOffset;
		}
		return MaxUnsignedInteger;
	}
}