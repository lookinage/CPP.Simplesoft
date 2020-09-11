#pragma once

#include "..\Base.h"

namespace Sets
{
	template<typename T, Integer Capacity>
	struct StaticStorage
	{
		T _elements[Capacity];

	public:

		StaticStorage( ) :
			_elements( )
		{ }

		const Integer GetCapacity( )
			const
		{
			return Capacity;
		}

		T& operator[](Integer const offset)
		{
			return _elements[offset];
		}
	};

	template<typename T, Integer Capacity>
	bool operator==(StaticStorage<T, Capacity> const& left, StaticStorage<T, Capacity> const& right)
	{
		__int32 compareResult = memcmp
		(
			&left,
			&right,
			sizeof(T) * Capacity
		);
		return compareResult == Zero;
	};
	template<typename T, Integer Capacity>
	bool operator!=(StaticStorage<T, Capacity> const& left, StaticStorage<T, Capacity> const& right)
	{
		__int32 compareResult = memcmp
		(
			&left,
			&right,
			sizeof(T) * Capacity
		);
		return compareResult != Zero;
	};
}