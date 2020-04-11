#pragma once

#include <string>

namespace Sets
{
	template<typename T>
	class DynamicStorage
	{
		Integer _capacity;
		T* _data;

	public:

		explicit DynamicStorage(const Integer count) : _capacity(count), _data(new T[count])
		{
		}
		~DynamicStorage()
		{
			delete _data;
		}

		static Integer EnsureCapacity(Integer capacity, Integer count)
		{
			if (count == 0x0i64)
				return 0x1i64;
			do
			{
				capacity <<= 0x1i64;
				if (capacity < 0x0i64)
				{
					capacity = MaxIntegerValue;
					break;
				}
			}
			while (capacity < count);
			return capacity;
		}
		Integer GetCapacity() const
		{
			return _capacity;
		}
		T Get(Integer const offset)
		{
			return _data[offset];
		}
		void Set(Integer const offset, T const value)
		{
			_data[offset] = value;
		}
		void EnsureCapacity(Integer const count)
		{
			Integer newCapacity;
			T* newData;

			if (count <= _capacity)
				return;
			memcpy(newData = new T[newCapacity = EnsureCapacity(_capacity, count)], _data, _capacity * sizeof(T));
			_capacity = newCapacity;
			delete _data;
			_data = newData;
			return;
		}

		T& operator[](Integer const offset) const
		{
			return _data[offset];
		}

		template<typename T>
		friend bool operator==(DynamicStorage<T> const left, DynamicStorage<T> const right);
		template<typename T>
		friend bool operator!=(DynamicStorage<T> const left, DynamicStorage<T> const right);
	};

	template<typename T>
	bool operator==(DynamicStorage<T> const left, DynamicStorage<T> const right)
	{
		return left._data == right._data;
	};
	template<typename T>
	bool operator!=(DynamicStorage<T> const left, DynamicStorage<T> const right)
	{
		return left._data != right._data;
	};
}