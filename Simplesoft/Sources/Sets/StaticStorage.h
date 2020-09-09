#pragma once

namespace Sets
{
	template<typename T, Integer Count>
	struct StaticStorage
	{
		T _elements[Count];

	public:

		const Integer GetCount() const { return Count; }
		T TryGetAt(Integer const offset) { return _elements[offset]; }
		void Set(Integer const offset, T const value) { _elements[offset] = value; }

		T& operator[](Integer const offset) { return _elements[offset]; }
	};

	template<typename T, Integer Count>
	bool operator==(StaticStorage<T, Count> const& left, StaticStorage<T, Count> const& right)
	{
		__int32 compareResult = memcmp
		(
			&left,
			&right,
			sizeof(T) * Count
		);
		return compareResult == 0x0I64;
	};
	template<typename T, Integer Count>
	bool operator!=(StaticStorage<T, Count> const& left, StaticStorage<T, Count> const& right)
	{
		__int32 compareResult = memcmp
		(
			&left,
			&right,
			sizeof(T) * Count
		);
		return compareResult != 0x0I64;
	};
}