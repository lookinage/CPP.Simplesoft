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
	T Get(Integer const offset)
	{
		return _data[offset];
	}
	void Set(Integer const offset, T const value)
	{
		_data[offset] = value;
	}

	T& operator[](Integer const offset)
	{
		return _data[offset];
	}
};

template<typename T, Integer Count>
bool operator==(StaticStorage<T, Count>& const left, StaticStorage<T, Count>& const right)
{
	return memcmp(&left, &right, sizeof(T) * Count) == 0x0;
};
template<typename T, Integer Count>
bool operator!=(StaticStorage<T, Count>& const left, StaticStorage<T, Count>& const right)
{
	return memcmp(&left, &right, sizeof(T) * Count) != 0x0;
};