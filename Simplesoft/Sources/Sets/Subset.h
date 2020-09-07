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
			Integer _nextElementIndex;
			Integer _simplifiedValue;
			T _value;
		};

		DynamicStorage<Element> _storage;
		Integer* _chainStartIndices;
		Integer _freeElementIndex;
		Integer _usedElementCount;
		Integer _count;

		void IncreaseCapacity(Integer capacity)
		{
			Integer previousCapacity;

			previousCapacity = _storage.GetCapacity();
			_storage.SetCapacity(capacity);
			delete _chainStartIndices;
			_chainStartIndices = new Integer[capacity];
			for (Integer elementIndex = 0x0I64; elementIndex != previousCapacity; elementIndex++)
			{
				Integer chainIndex = _storage[elementIndex]._simplifiedValue % capacity;
				_storage[elementIndex]._nextElementIndex = _chainStartIndices[chainIndex] - 0x1I64;
				_chainStartIndices[chainIndex] = elementIndex + 0x1I64;
			}
		}

	public:

		class AscendingSequence
		{
			friend class Subset;

			const Subset* const _subset;
			Integer const _edge;
			Integer _offset;

			explicit AscendingSequence(const Subset* const subset, Integer const edge, Integer const offset) : _subset(subset), _edge(edge), _offset(offset) { }

		public:

			class Enumerator
			{
				friend class AscendingSequence;

				DynamicStorage<T> const _storage;
				Integer _offset;

				explicit Enumerator(DynamicStorage<T> const storage, Integer const offset) : _storage(storage), _offset(offset) { }

			public:

				Enumerator& operator++()
				{
					for (_offset++; _offset != _used;)
						_offset = 0x0I64;
					return *this;
				}
				bool operator==(Enumerator const other) const { return _offset == other._offset; }
				bool operator!=(Enumerator const other) const { return _offset != other._offset; }
				T operator*() const { return _storage[_offset]; }
			};

			Enumerator begin() { return Enumerator(_subset->_storage, _offset); }
			Enumerator end() { return Enumerator(_subset->_storage, _edge); }
		};
		class DescendingSequence
		{
			friend class Subset;

			const Subset* const _subset;
			Integer const _edge;
			Integer _offset;

			explicit DescendingSequence(const Subset* const stack, Integer const edge, Integer const offset) : _subset(stack), _edge(edge), _offset(offset) { }

		public:

			class Enumerator
			{
				friend class DescendingSequence;

				DynamicStorage<T> const _storage;
				Integer _offset;

				explicit Enumerator(DynamicStorage<T> const storage, Integer const offset) : _storage(storage), _offset(offset) { }

			public:

				Enumerator& operator++()
				{
					if (--_offset < 0x0I64)
						_offset = _storage.GetCapacity() - 0x1I64;
					return *this;
				}
				bool operator==(Enumerator const other) const { return _offset == other._offset; }
				bool operator!=(Enumerator const other) const { return _offset != other._offset; }
				T operator*() const { return _storage[_offset]; }
			};

			Enumerator begin() { return Enumerator(_subset->_storage, _offset); }
			Enumerator end() { return Enumerator(_subset->_storage, _edge); }
		};

		Subset(Integer const capacity) : _storage(capacity) { _chainStartIndices = new Integer[capacity]; }
		~Subset() { delete _chainStartIndices; }

		Integer GetCount() const { return _count; }
		bool TryGetAddress(T const value, Integer& address) const
		{
			Integer simplifiedValue;

			simplifiedValue = Simplify(value);
			for (Integer elementIndex = _chainStartIndices[simplifiedValue % _storage.GetCapacity()] - 0x1I64; elementIndex != -0x1I64; elementIndex = _storage[elementIndex]._nextElementIndex)
			{
				if (value != _storage[elementIndex]._value)
					continue;
				address = elementIndex;
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
		bool TryAdd(T const value, Integer& address)
		{
			Integer simplifiedValue;
			Integer chainIndex;
			Integer elementIndex;

			if (_count++ == MaxIntegerValue)
			{
				_count--;
				return false;
			}
			if (_count > _storage.GetCapacity())
				IncreaseCapacity(GetEnoughCapacity(_storage.GetCapacity(), _count));
			simplifiedValue = Simplify(value);
			chainIndex = simplifiedValue % _storage.GetCapacity();
			for (elementIndex = _chainStartIndices[chainIndex] - 0x1I64; elementIndex != -0x1I64; elementIndex = _storage[elementIndex]._nextElementIndex)
			{
				if (value != _storage[elementIndex]._value)
					continue;
				_count--;
				return false;
			}
			if (_freeElementIndex != -0x1)
				_freeElementIndex = _storage[elementIndex = _freeElementIndex]._nextElementIndex;
			else
				elementIndex = _usedElementCount++;
			_storage[elementIndex]._nextElementIndex = _chainStartIndices[chainIndex] - 0x1I64;
			_storage[elementIndex]._simplifiedValue = simplifiedValue;
			_storage[elementIndex]._value = value;
			_chainStartIndices[chainIndex] = elementIndex + 0x1I64;
			address = elementIndex;
			return true;
		}
		bool TryRemove(T const value)
		{
			Integer chainIndex;
			Integer lastElementIndex;

			chainIndex = Simplify(value) % _storage.GetCapacity();
			lastElementIndex = -0x1I64;
			for (Integer elementIndex = _chainStartIndices[chainIndex] - 0x1I64; elementIndex != -0x1I64; lastElementIndex = elementIndex, elementIndex = _storage[elementIndex]._nextElementIndex)
			{
				if (value != _storage[elementIndex]._value)
					continue;
				if (lastElementIndex == -0x1I64)
					_chainStartIndices[chainIndex] = _storage[elementIndex]._nextElementIndex + 0x1I64;
				else
					_storage[lastElementIndex]._nextElementIndex = _storage[elementIndex]._nextElementIndex;
				_storage[elementIndex]._nextElementIndex = _freeElementIndex;
				_storage[elementIndex]._simplifiedValue = -0x1I64;
				_freeElementIndex = elementIndex;
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
			Integer chainIndex = simplifiedValue % _storage.GetCapacity();
			Integer lastElementIndex = -0x1I64;
			for (Integer elementIndex = _chainStartIndices[chainIndex] - 0x1I64; ; lastElementIndex = elementIndex, elementIndex = _storage[elementIndex]._nextElementIndex)
			{
				if (element != _storage[elementIndex]._value)
					continue;
				if (lastElementIndex == -0x1I64)
					_chainStartIndices[chainIndex] = _storage[elementIndex]._nextElementIndex + 0x1I64;
				else
					_storage[lastElementIndex]._nextElementIndex = _storage[elementIndex]._nextElementIndex;
				_storage[elementIndex]._nextElementIndex = _freeElementIndex;
				_storage[elementIndex]._simplifiedValue = -0x1I64;
				_freeElementIndex = elementIndex;
				_count--;
				return true;
			}
		}
		void Clear()
		{
			memset(_chainStartIndices, 0x0I32, _storage.GetCapacity() * sizeof(Integer));
			_freeElementIndex = -0x1I64;
			_usedElementCount = 0x0I64;
			_count = 0x0I64;
		}
	};
}