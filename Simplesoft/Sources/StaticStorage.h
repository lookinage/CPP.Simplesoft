#pragma once

template<typename T, Integer Count>
class StaticStorage
{
	T _data[Count];

	public:

	const Integer GetCount() const
	{
		return Count;
	}

	inline T& operator[](const Integer index)
	{
		return _data[index];
	}
};

template<typename T, Integer Count>
inline bool operator==(StaticStorage<T, Count>& left, StaticStorage<T, Count>& right)
{
	return memcmp(&left, &right, sizeof(T) * Count) == 0x0;
};
template<typename T, Integer Count>
inline bool operator!=(StaticStorage<T, Count>& left, StaticStorage<T, Count>& right)
{
	return memcmp(&left, &right, sizeof(T) * Count) != 0x0;
};