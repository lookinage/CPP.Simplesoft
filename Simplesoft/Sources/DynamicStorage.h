#pragma once

#include <string>

template<typename T>
class DynamicStorage
{
	Integer _count;
	T* _data;

	public:

	DynamicStorage(DynamicStorage&&) = delete;
	DynamicStorage(DynamicStorage&) = delete;
	DynamicStorage(const Integer count) : _count(count), _data(new T[count])
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

	void EnsureCount(const Integer desiredCount)
	{
		Integer newCount;
		T* newData;

		if (desiredCount <= _count)
			return;
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
		while (newCount < desiredCount);
		newData = new T[newCount];
		memcpy(newData, _data, _count * sizeof(T));
		_count = newCount;
		delete _data;
		_data = newData;
		return;
	}

	T& operator[](const Integer index) const
	{
		return _data[index];
	}

	template<typename T>
	friend bool operator==(DynamicStorage<T>& left, DynamicStorage<T>& right);
	template<typename T>
	friend bool operator!=(DynamicStorage<T>& left, DynamicStorage<T>& right);
};

template<typename T>
inline bool operator==(DynamicStorage<T>& left, DynamicStorage<T>& right)
{
	return left._data == right._data;
};
template<typename T>
inline bool operator!=(DynamicStorage<T>& left, DynamicStorage<T>& right)
{
	return left._data != right._data;
};