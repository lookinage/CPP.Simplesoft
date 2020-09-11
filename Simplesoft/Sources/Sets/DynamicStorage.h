#pragma once

#include <string>
#include "..\Base.h"

namespace Sets
{
	template<typename T>
	class DynamicStorage
	{
		Integer _capacity;
		T* _elements;

	public:

		explicit DynamicStorage(const Integer capacity) : _capacity(capacity), _elements(new T[capacity]) { }
		~DynamicStorage( ) { delete _elements; }

		Integer GetCapacity( ) const { return _capacity; }
		void SetCapacity(Integer const capacity)
		{
			T* elements;

			memcpy
			(
				elements = new T[capacity],
				_elements,
				_capacity * sizeof(T)
			);
			_capacity = capacity;
			delete _elements;
			_elements = elements;
			return;
		}

		T& operator[](Integer const offset) const { return _elements[offset]; }

		template<typename T>
		friend bool operator==(DynamicStorage<T> const& left, DynamicStorage<T> const& right);
		template<typename T>
		friend bool operator!=(DynamicStorage<T> const& left, DynamicStorage<T> const& right);
	};

	template<typename T>
	bool operator==(DynamicStorage<T> const& left, DynamicStorage<T> const& right)
	{
		bool result = left._elements == right._elements;
		return result;
	};
	template<typename T>
	bool operator!=(DynamicStorage<T> const& left, DynamicStorage<T> const& right)
	{
		return left._elements != right._elements;
	};
}