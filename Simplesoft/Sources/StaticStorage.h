#pragma once

template<typename T, Integer Count>
struct StaticStorage
{
	private:

	T _data[Count];

	public:

	const Integer GetCount() const
	{
		return Count;
	}

	T& operator[](const Integer offset)
	{
		return _data[offset];
	}
};

template<typename T, Integer Count>
bool operator==(StaticStorage<T, Count>& left, StaticStorage<T, Count>& right)
{
	return memcmp(&left, &right, sizeof(T) * Count) == 0x0;
};
template<typename T, Integer Count>
bool operator!=(StaticStorage<T, Count>& left, StaticStorage<T, Count>& right)
{
	return memcmp(&left, &right, sizeof(T) * Count) != 0x0;
};