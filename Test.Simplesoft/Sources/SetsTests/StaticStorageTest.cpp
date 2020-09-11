#include "StaticStorageTest.h"

namespace SetsTests
{
	Integer StaticStorageTest( )
	{
		Integer const testCount = 0xFI64;

		Sets::StaticStorage<Integer, testCount> storage = { };
		for (Integer offset = 0x0I64; offset != testCount; offset++)
		{
			if (storage.GetCapacity( ) != testCount)
				return MaxUnsignedInteger - 0x1I64;
			storage[offset] = offset;
			for (Integer checkingOffset = 0x0I64; checkingOffset <= offset; checkingOffset++)
				if (storage[checkingOffset] != checkingOffset)
					return checkingOffset;
		}
		return MaxUnsignedInteger;
	}
}