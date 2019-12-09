#pragma once

#include "Exception.h"

namespace Simplesoft
{
	template<typename T, __int64 Count>
	class StaticRow
	{
		T _array[Count];

		public:

		__int64 GetCount() { return Count; }

		T& operator[](__int64 index)
		{
#if Debug
			if (index < 0x0 || index >= Count)
				throw Exception("index is invalid.");
#endif
			return _array[index];
		}
	};
}