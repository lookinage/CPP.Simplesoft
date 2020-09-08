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

		class AscendingSequence
		{
			friend class StandingStack;

			const StandingStack* const _stack;
			Integer const _edge;
			Integer _offset;

			explicit AscendingSequence(const StandingStack* const stack, Integer const edge, Integer const offset) : _stack(stack), _edge(edge), _offset(offset) { }

		public:

			class Enumerator
			{
				friend class AscendingSequence;

				const StandingStack* const _stack;
				Integer _offset;

				explicit Enumerator(const StandingStack* const stack, Integer const offset) : _stack(stack), _offset(offset) { }

			public:

				bool operator==(Enumerator const other) const { return _offset == other._offset; }
				bool operator!=(Enumerator const other) const { return _offset != other._offset; }
				T operator*() const { return _stack->_storage[_offset]; }
				Enumerator& operator++()
				{
					_offset++;
					return *this;
				}
			};

			Enumerator begin() const { return Enumerator(_stack, _offset); }
			Enumerator end() const { return Enumerator(_stack, _edge); }
		};
		class DescendingSequence
		{
			friend class StandingStack;

			const StandingStack* const _stack;
			Integer const _edge;
			Integer _offset;

			explicit DescendingSequence(const StandingStack* const stack, Integer const edge, Integer const offset) : _stack(stack), _edge(edge), _offset(offset) { }

		public:

			class Enumerator
			{
				friend class DescendingSequence;

				const StandingStack* const _stack;
				Integer _offset;

				explicit Enumerator(const StandingStack* const stack, Integer const offset) : _stack(stack), _offset(offset) { }

			public:

				bool operator==(Enumerator const other) const { return _offset == other._offset; }
				bool operator!=(Enumerator const other) const { return _offset != other._offset; }
				T operator*() const { return _stack->_storage[_offset]; }
				Enumerator& operator++()
				{
					_offset--;
					return *this;
				}
			};

			Enumerator begin() const { return Enumerator(_stack, _offset); }
			Enumerator end() const { return Enumerator(_stack, _edge); }
		};

		StandingStack(StandingStack& instance) = delete;
		StandingStack(StandingStack&& instance) = delete;
		explicit StandingStack(Integer const capacity) : _storage(capacity), _count(0x0I64) { }

		Integer GetCount() const { return _count; }
		T GetAt(Integer const offset) const { return _storage[offset]; }
		AscendingSequence GetAscendingSequence(Integer const offset, Integer const edge) const 
		{ 
			return AscendingSequence
			(
				this, 
				edge, 
				offset
			);
		}
		AscendingSequence GetAscendingSequence() const 
		{ 
			return GetAscendingSequence
			(
				0x0I64, 
				_count
			); 
		}
		DescendingSequence GetDescendingSequence(Integer const offset, Integer const edge) const
		{ 
			return DescendingSequence
			(
				this, 
				edge, 
				offset
			); 
		}
		DescendingSequence GetDescendingSequence() const 
		{ 
			return GetDescendingSequence
			(
				_count - 0x1I64, 
				-0x1I64
			); 
		}
		bool TryAdd(T const value)
		{
			Integer offset;

			if ((offset = _count++) != MaxIntegerValue)
			{
				if (_count <= _storage.GetCapacity())
				{
				Adding:
					_storage[offset] = value;
					return true;
				}
				_storage.SetCapacity(GetEnoughCapacity(_storage.GetCapacity(), _count));
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