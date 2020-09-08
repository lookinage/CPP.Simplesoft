#pragma once

#include "..\Base.h"
#include "DynamicStorage.h"

namespace Sets
{
	template<typename T>
	class Subset
	{
		struct Element
		{
			Integer _nextElementOffset;
			Integer _simplifiedValue;
			T _value;
		};

		DynamicStorage<Element> _storage;
		Integer* _chainStartOffsets;
		Integer _freeElementOffset;
		Integer _usedElementCount;
		Integer _count;

		void IncreaseCapacity(Integer capacity)
		{
			Integer previousCapacity;

			previousCapacity = _storage.GetCapacity();
			_storage.SetCapacity(capacity);
			delete _chainStartOffsets;
			_chainStartOffsets = new Integer[capacity];
			memset(_chainStartOffsets, 0x0I32, _storage.GetCapacity() * sizeof(Integer));
			for (Integer elementOffset = 0x0I64; elementOffset != previousCapacity; elementOffset++)
			{
				Integer chainOffset = _storage[elementOffset]._simplifiedValue % capacity;
				_storage[elementOffset]._nextElementOffset = _chainStartOffsets[chainOffset] - 0x1I64;
				_chainStartOffsets[chainOffset] = elementOffset + 0x1I64;
			}
		}

	public:

		class Enumerator
		{
			friend class Subset;

			const Subset<T>* const _subset;
			Integer _offset;

			explicit Enumerator(const Subset<T>* const subset, Integer const offset) : _subset(subset), _offset(offset) { }

		public:

			bool operator==(Enumerator const other) const { return _offset == other._offset; }
			bool operator!=(Enumerator const other) const { return _offset != other._offset; }
			T operator*() const { return _subset->_storage[_offset]._value; }
			Enumerator& operator++()
			{
				for (_offset++; _subset->_storage[_offset]._simplifiedValue != -0x1I64 && _offset != _subset->_usedElementCount; _offset++);
				return *this;
			}
		};

		Subset(Integer const capacity) : _storage(capacity), _chainStartOffsets(new Integer[capacity]), _freeElementOffset(-0x1I64), _usedElementCount(0x0I64), _count(0x0I64) { }
		~Subset() { delete _chainStartOffsets; }

		Integer GetCount() const { return _count; }
		bool TryGetAddress(T const value, Integer& address) const
		{
			Integer simplifiedValue;

			simplifiedValue = Simplify(value);
			for (Integer elementOffset = _chainStartOffsets[simplifiedValue % _storage.GetCapacity()] - 0x1I64; elementOffset != -0x1I64; elementOffset = _storage[elementOffset]._nextElementOffset)
			{
				if (value != _storage[elementOffset]._value)
					continue;
				address = elementOffset;
				return true;
			}
			return false;
		}
		bool ContainsAt(Integer const address) const { return address >= 0x0I64 && address < _usedElementCount&& _storage[address]._simplifiedValue != -0x1I64; }
		bool TryGetAt(Integer const address, T& value) const
		{
			if (address < 0x0I64 || address >= _usedElementCount || _storage[address]._simplifiedValue == -0x1I64)
				return false;
			value = _storage[address]._value;
			return true;
		}
		Enumerator begin() const { return Enumerator(this, 0x0I64); }
		Enumerator end() const { return Enumerator(this, _usedElementCount); }
		bool TryAdd(T const value, Integer& address)
		{
			Integer simplifiedValue;
			Integer chainOffset;
			Integer elementOffset;

			if (_count++ == MaxIntegerValue)
			{
				_count--;
				return false;
			}
			if (_count > _storage.GetCapacity())
				IncreaseCapacity(GetEnoughCapacity(_storage.GetCapacity(), _count));
			simplifiedValue = Simplify(value);
			chainOffset = simplifiedValue % _storage.GetCapacity();
			for (elementOffset = _chainStartOffsets[chainOffset] - 0x1I64; elementOffset != -0x1I64; elementOffset = _storage[elementOffset]._nextElementOffset)
			{
				if (value != _storage[elementOffset]._value)
					continue;
				_count--;
				return false;
			}
			if (_freeElementOffset != -0x1)
				_freeElementOffset = _storage[elementOffset = _freeElementOffset]._nextElementOffset;
			else
				elementOffset = _usedElementCount++;
			_storage[elementOffset]._nextElementOffset = _chainStartOffsets[chainOffset] - 0x1I64;
			_storage[elementOffset]._simplifiedValue = simplifiedValue;
			_storage[elementOffset]._value = value;
			_chainStartOffsets[chainOffset] = elementOffset + 0x1I64;
			address = elementOffset;
			return true;
		}
		bool TryRemove(T const value)
		{
			Integer chainOffset;
			Integer lastElementOffset;

			chainOffset = Simplify(value) % _storage.GetCapacity();
			lastElementOffset = -0x1I64;
			for (Integer elementOffset = _chainStartOffsets[chainOffset] - 0x1I64; elementOffset != -0x1I64; lastElementOffset = elementOffset, elementOffset = _storage[elementOffset]._nextElementOffset)
			{
				if (value != _storage[elementOffset]._value)
					continue;
				if (lastElementOffset == -0x1I64)
					_chainStartOffsets[chainOffset] = _storage[elementOffset]._nextElementOffset + 0x1I64;
				else
					_storage[lastElementOffset]._nextElementOffset = _storage[elementOffset]._nextElementOffset;
				_storage[elementOffset]._nextElementOffset = _freeElementOffset;
				_storage[elementOffset]._simplifiedValue = -0x1I64;
				_freeElementOffset = elementOffset;
				_count--;
				return true;
			}
			return false;
		}
		bool TryRemoveAt(Integer const address, T& element)
		{
			Integer simplifiedValue;

			if (address < 0x0I64 || address >= _usedElementCount || (simplifiedValue = _storage[address]._simplifiedValue) == -0x1I64)
				return false;
			element = _storage[address]._value;
			Integer chainOffset = simplifiedValue % _storage.GetCapacity();
			Integer lastElementOffset = -0x1I64;
			for (Integer elementOffset = _chainStartOffsets[chainOffset] - 0x1I64; ; lastElementOffset = elementOffset, elementOffset = _storage[elementOffset]._nextElementOffset)
			{
				if (element != _storage[elementOffset]._value)
					continue;
				if (lastElementOffset == -0x1I64)
					_chainStartOffsets[chainOffset] = _storage[elementOffset]._nextElementOffset + 0x1I64;
				else
					_storage[lastElementOffset]._nextElementOffset = _storage[elementOffset]._nextElementOffset;
				_storage[elementOffset]._nextElementOffset = _freeElementOffset;
				_storage[elementOffset]._simplifiedValue = -0x1I64;
				_freeElementOffset = elementOffset;
				_count--;
				return true;
			}
		}
		void Clear()
		{
			memset(_chainStartOffsets, 0x0I32, _storage.GetCapacity() * sizeof(Integer));
			_freeElementOffset = -0x1I64;
			_usedElementCount = 0x0I64;
			_count = 0x0I64;
		}
	};
}