#pragma once

#include "..\Base.h"
#include "DynamicStorage.h"
#include "Relation.h"

namespace Sets
{
	template<typename TInput, typename TOutput>
	class Surjection
	{
		class Element
		{
			friend class Surjection;

			Integer _nextElementOffset;
			Integer _simplifiedInput;
			Relation<TInput, TOutput> _relation;
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
				Integer chainOffset = _storage[elementOffset]._simplifiedInput % capacity;
				_storage[elementOffset]._nextElementOffset = _chainStartOffsets[chainOffset] - 0x1I64;
				_chainStartOffsets[chainOffset] = elementOffset + 0x1I64;
			}
		}

	public:

		class Enumerator
		{
			friend class Surjection;

			Surjection<TInput, TOutput> const& _surjection;
			Integer _offset;
			bool _canContinue;

			explicit Enumerator(Surjection<TInput, TOutput> const& surjection) : _surjection(surjection), _offset(0x0I64), _canContinue(true) { SetValid(); }

			void SetValid()
			{
				for (; ; _offset++)
				{
					if (_offset != _surjection._usedElementCount)
					{
						if (_surjection._storage[_offset]._simplifiedInput != -0x1I64)
							break;
						else
							continue;
					}
					else
					{
						_canContinue = false;
						break;
					}
				}
			}

		public:

			bool operator!() const { return _canContinue; }
			Relation<TInput, TOutput> const& operator*() const { return _surjection._storage[_offset]._relation; }
			Enumerator& operator++()
			{
				_offset++;
				SetValid();
				return *this;
			}
		};

		Surjection(Integer const capacity) : _storage(capacity), _chainStartOffsets(new Integer[capacity]), _freeElementOffset(-0x1I64), _usedElementCount(0x0I64), _count(0x0I64) { }
		~Surjection() { delete _chainStartOffsets; }

		Integer GetCount() const { return _count; }
		bool TryGetAddress(TInput const input, Integer& address) const
		{
			Integer simplifiedInput;

			simplifiedInput = Simplify(input);
			for (Integer elementOffset = _chainStartOffsets[simplifiedInput % _storage.GetCapacity()] - 0x1I64; elementOffset != -0x1I64; elementOffset = _storage[elementOffset]._nextElementOffset)
			{
				if (input != _storage[elementOffset]._relation.GetInput())
					continue;
				address = elementOffset;
				return true;
			}
			return false;
		}
		bool ContainsAt(Integer const address) const { return address >= 0x0I64 && address < _usedElementCount&& _storage[address]._simplifiedInput != -0x1I64; }
		bool TryGetAt(Integer const address, Relation<TInput, TOutput>& relation) const
		{
			if (address < 0x0I64 || address >= _usedElementCount || _storage[address]._simplifiedInput == -0x1I64)
				return false;
			relation = _storage[address]._relation;
			return true;
		}
		Enumerator GetEnumerator() const { return Enumerator(*this); }
		bool TryAdd(Relation<TInput, TOutput> relation, Integer& address)
		{
			Integer simplifiedInput;
			Integer chainOffset;
			Integer elementOffset;

			if (_count++ == MaxIntegerValue)
			{
				_count--;
				return false;
			}
			if (_count > _storage.GetCapacity())
				IncreaseCapacity(GetEnoughCapacity(_storage.GetCapacity(), _count));
			simplifiedInput = Simplify(relation.GetInput());
			chainOffset = simplifiedInput % _storage.GetCapacity();
			for (elementOffset = _chainStartOffsets[chainOffset] - 0x1I64; elementOffset != -0x1I64; elementOffset = _storage[elementOffset]._nextElementOffset)
			{
				if (relation.GetInput() != _storage[elementOffset]._relation.GetInput())
					continue;
				_count--;
				return false;
			}
			if (_freeElementOffset != -0x1)
				_freeElementOffset = _storage[elementOffset = _freeElementOffset]._nextElementOffset;
			else
				elementOffset = _usedElementCount++;
			_storage[elementOffset]._nextElementOffset = _chainStartOffsets[chainOffset] - 0x1I64;
			_storage[elementOffset]._simplifiedInput = simplifiedInput;
			_storage[elementOffset]._relation = relation;
			_chainStartOffsets[chainOffset] = elementOffset + 0x1I64;
			address = elementOffset;
			return true;
		}
		bool TryRemove(TInput const input)
		{
			Integer chainOffset;
			Integer lastElementOffset;

			chainOffset = Simplify(input) % _storage.GetCapacity();
			lastElementOffset = -0x1I64;
			for (Integer elementOffset = _chainStartOffsets[chainOffset] - 0x1I64; elementOffset != -0x1I64; lastElementOffset = elementOffset, elementOffset = _storage[elementOffset]._nextElementOffset)
			{
				if (input != _storage[elementOffset]._relation.GetInput())
					continue;
				if (lastElementOffset == -0x1I64)
					_chainStartOffsets[chainOffset] = _storage[elementOffset]._nextElementOffset + 0x1I64;
				else
					_storage[lastElementOffset]._nextElementOffset = _storage[elementOffset]._nextElementOffset;
				_storage[elementOffset]._nextElementOffset = _freeElementOffset;
				_storage[elementOffset]._simplifiedInput = -0x1I64;
				_freeElementOffset = elementOffset;
				_count--;
				return true;
			}
			return false;
		}
		bool TryRemoveAt(Integer const address, Relation<TInput, TOutput>& relation)
		{
			Integer simplifiedInput;

			if (address < 0x0I64 || address >= _usedElementCount || (simplifiedInput = _storage[address]._simplifiedInput) == -0x1I64)
				return false;
			relation = _storage[address]._relation;
			Integer chainOffset = simplifiedInput % _storage.GetCapacity();
			Integer lastElementOffset = -0x1I64;
			for (Integer elementOffset = _chainStartOffsets[chainOffset] - 0x1I64; ; lastElementOffset = elementOffset, elementOffset = _storage[elementOffset]._nextElementOffset)
			{
				if (relation.GetInput() != _storage[elementOffset]._relation.GetInput())
					continue;
				if (lastElementOffset == -0x1I64)
					_chainStartOffsets[chainOffset] = _storage[elementOffset]._nextElementOffset + 0x1I64;
				else
					_storage[lastElementOffset]._nextElementOffset = _storage[elementOffset]._nextElementOffset;
				_storage[elementOffset]._nextElementOffset = _freeElementOffset;
				_storage[elementOffset]._simplifiedInput = -0x1I64;
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