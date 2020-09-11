#pragma once

#include "..\Base.h"
#include "DynamicStorage.h"

namespace Sets
{
	template<typename T>
	class StandingStack
	{
		DynamicStorage<T> _storage;
		Integer _count;

	public:

		class AscendingEnumerator
		{
			friend class StandingStack;

			StandingStack const& _stack;
			Integer const _edge;
			Integer _offset;

			explicit AscendingEnumerator
			(
				StandingStack const& stack,
				Integer const edge,
				Integer const offset
			) 
				: 
				_stack(stack), 
				_edge(edge), 
				_offset(offset) 
			{ }

		public:

			bool operator!() const { return _offset != _edge; }
			T const& operator*() const { return _stack._storage[_offset]; }
			AscendingEnumerator& operator++()
			{
				_offset++;
				return *this;
			}
		};
		class DescendingEnumerator
		{
			friend class StandingStack;

			StandingStack const& _stack;
			Integer const _edge;
			Integer _offset;

			explicit DescendingEnumerator(StandingStack const& stack, Integer const edge, Integer const offset) : _stack(stack), _edge(edge), _offset(offset) { }

		public:

			bool operator!() const { return _offset != _edge; }
			T const& operator*() const { return _stack._storage[_offset]; }
			DescendingEnumerator& operator++()
			{
				_offset--;
				return *this;
			}
		};

		explicit StandingStack(Integer const capacity) : _storage(capacity), _count(0x0I64) { }

		Integer GetCount() const { return _count; }
		T GetAt(Integer const offset) const { return _storage[offset]; }
		AscendingEnumerator GetAscendingEnumerator(Integer const offset, Integer const edge) const
		{
			return AscendingEnumerator
			(
				*this,
				edge,
				offset
			);
		}
		AscendingEnumerator GetAscendingEnumerator() const
		{
			return GetAscendingEnumerator
			(
				0x0I64,
				_count
			);
		}
		DescendingEnumerator GetDescendingEnumerator(Integer const offset, Integer const edge) const
		{
			return DescendingEnumerator
			(
				*this,
				edge,
				offset
			);
		}
		DescendingEnumerator GetDescendingEnumerator() const
		{
			return GetDescendingEnumerator
			(
				_count - 0x1I64,
				-0x1I64
			);
		}
		bool TryAdd(T const value)
		{
			Integer offset;

			if ((offset = _count++) != MaxUnsignedInteger)
			{
				if (_count <= _storage.GetCapacity())
				{
				Adding:
					_storage[offset] = value;
					return true;
				}
				_storage.SetCapacity(GetEnoughCapacity
				(
					_storage.GetCapacity(),
					_count
				));
				goto Adding;
			}
			_count--;
			return false;
		}
		void Set(Integer const offset, T const value) { _storage[offset] = value; }
		bool TryRemove(T& value)
		{
			if (_count != 0x0I64)
			{
				value = _storage[--_count];
				return true;
			}
			return false;
		}
		void Clear() { _count = 0x0I64; }
	};
}