#pragma once

#include <string>

template<typename T>
class DynamicStorage
{
	Integer _count;
	T* _data;

	public:

	explicit DynamicStorage(const Integer count) : _count(count), _data(new T[count])
	{
	}
	~DynamicStorage()
	{
		delete _data;
	}

	Integer GetCount() const
	{
		return _count;
	}
	T Get(Integer const offset)
	{
		return _data[offset];
	}
	void Set(Integer const offset, T const value)
	{
		_data[offset] = value;
	}
	void EnsureCount(Integer const count)
	{
		Integer newCount;
		T* newData;

		if (count <= _count)
			return;
		if (_count != 0x0LL)
		{
			newCount = _count;
			do
			{
				newCount <<= 0x1LL;
				if (newCount < 0x0LL)
				{
					newCount = 0x7FFFFFFFFFFFFFFFLL;
					break;
				}
			}
			while (newCount < count);
		}
		else
			newCount = 0x1LL;
		newData = new T[newCount];
		memcpy(newData, _data, _count * sizeof(T));
		_count = newCount;
		delete _data;
		_data = newData;
		return;
	}

	T& operator[](Integer const offset) const
	{
		return _data[offset];
	}

	template<typename T>
	friend bool operator==(DynamicStorage<T>& const left, DynamicStorage<T>& const right);
	template<typename T>
	friend bool operator!=(DynamicStorage<T>& const left, DynamicStorage<T>& const right);
};

template<typename T>
bool operator==(DynamicStorage<T>& const left, DynamicStorage<T>& const right)
{
	return left._data == right._data;
};
template<typename T>
bool operator!=(DynamicStorage<T>& const left, DynamicStorage<T>& const right)
{
	return left._data != right._data;
};