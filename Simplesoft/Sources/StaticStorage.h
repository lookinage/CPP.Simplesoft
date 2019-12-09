#pragma once

#include "Exception.h"

namespace Simplesoft
{
	template<typename T, __int64 Count>
	class StaticStorage
	{
		T _array[Count];

		public:

		__int64 const GetCount() const { return Count; }

		T& operator[](__int64 index)
		{
			#if _DEBUG
			if (index < 0x0 || index >= Count)
				throw new Exception("index is invalid");
			#endif

			return _array[index];
		}
	};
}