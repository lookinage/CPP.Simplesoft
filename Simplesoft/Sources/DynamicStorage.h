#pragma once

#include "Exception.h"

namespace Simplesoft
{
	template<typename T>
	class DynamicStorage
	{
		T* _data;

		public:

		DynamicStorage(DynamicStorage&&) = delete;
		DynamicStorage(DynamicStorage&) = delete;
		DynamicStorage(__int64 count) : _data((T*)new char[sizeof(__int64) + sizeof(T) * count])
		{
			*(__int64*)_data = count;
			_data = (T*)((char*)_data + sizeof(__int64));
		}

		__int64 GetCount() { return *((__int64*)_data - 0x1); }

		T& operator[](__int64 index)
		{
			#if _DEBUG
			if (index < 0x0 || index >= GetCount())
				throw new Exception("index is invalid.");
			#endif

			return _data[index];
		}
	};
}