#pragma once

#include "..\Base.h"
#include "DynamicStorage.h"

namespace Sets
{
	template<typename T>
	class LyingStack
	{
		T* _elements;
		Integer _capacity;
		Integer _startOffset;
		Integer _endOffset;
		Integer _count;

		inline Integer GetActualOffset(Integer const offset) const
		{
			Integer actualOffset;

			if ((actualOffset = _startOffset + offset) < _capacity)
				return actualOffset;
			return actualOffset - _capacity;
		}
		inline void IncreaseCapacity()
		{
			T* elements;
			Integer capacity;
			Integer offset;

			capacity = GetEnoughCapacity(_capacity, _count);
			offset = (capacity - _capacity) >> 0x1I64;
			elements = new T[capacity];
			if (_startOffset != 0x0I64)
			{
				memcpy
				(
					elements + offset,
					_elements + _startOffset,
					(_capacity - _startOffset) * sizeof(T)
				);
				memcpy
				(
					elements + offset + _capacity - _startOffset,
					_elements,
					(_startOffset) * sizeof(T)
				);
			}
			else
				memcpy
				(
					elements + offset,
					_elements,
					_capacity * sizeof(T)
				);
			delete _elements;
			_elements = elements;
			_capacity = capacity;
			_startOffset = offset;
			_endOffset = offset + _count - 0x1I64;
			return;
		}

	public:

		class AscendingSequence
		{
			friend class LyingStack;

			const LyingStack* const _stack;
			Integer const _edge;
			Integer _offset;

			explicit AscendingSequence(const LyingStack* const stack, Integer const edge, Integer const offset) : _stack(stack), _edge(edge), _offset(offset) { }

		public:

			class Enumerator
			{
				friend class AscendingSequence;

				const LyingStack* const _stack;
				Integer _offset;

				explicit Enumerator(const LyingStack* const stack, Integer const offset) : _stack(stack), _offset(offset) { }

			public:

				bool operator==(Enumerator const other) const { return _offset == other._offset; }
				bool operator!=(Enumerator const other) const { return _offset != other._offset; }
				T operator*() const { return _stack->_elements[_offset]; }
				Enumerator& operator++()
				{
					if (++_offset == _stack->_capacity)
						_offset = 0x0I64;
					return *this;
				}
			};

			Enumerator begin() const { return Enumerator(_stack, _offset); }
			Enumerator end() const { return Enumerator(_stack, _edge); }
		};
		class DescendingSequence
		{
			friend class LyingStack;

			const LyingStack* const _stack;
			Integer const _edge;
			Integer _offset;

			explicit DescendingSequence(const LyingStack* const stack, Integer const edge, Integer const offset) : _stack(stack), _edge(edge), _offset(offset) { }

		public:

			class Enumerator
			{
				friend class DescendingSequence;

				const LyingStack* const _stack;
				Integer _offset;

				explicit Enumerator(const LyingStack* const stack, Integer const offset) : _stack(stack), _offset(offset) { }

			public:

				bool operator==(Enumerator const other) const { return _offset == other._offset; }
				bool operator!=(Enumerator const other) const { return _offset != other._offset; }
				T operator*() const { return _stack->_elements[_offset]; }
				Enumerator& operator++()
				{
					if (--_offset < 0x0I64)
						_offset = _stack->_capacity - 0x1I64;
					return *this;
				}
			};

			Enumerator begin() const { return Enumerator(_stack, _offset); }
			Enumerator end() const { return Enumerator(_stack, _edge); }
		};

		LyingStack(LyingStack& instance) = delete;
		LyingStack(LyingStack&& instance) = delete;
		explicit LyingStack(Integer const capacity) : _elements(new T[capacity]), _capacity(capacity), _startOffset(0x0I64), _endOffset(0x0I64), _count(0x0I64) { }
		~LyingStack() { delete _elements; }

		Integer GetCount() const { return _count; }
		T GetAt(Integer const offset) const { return _elements[GetActualOffset(offset)]; }
		AscendingSequence GetAscendingSequence(Integer const edge, Integer const offset) const
		{
			return AscendingSequence
			(
				this,
				GetActualOffset(edge),
				GetActualOffset(offset)
			);
		}
		AscendingSequence GetAscendingSequence() const
		{
			return GetAscendingSequence
			(
				_count,
				0x0I64
			);
		}
		DescendingSequence GetDescendingSequence(Integer const edge, Integer const offset) const
		{
			return DescendingSequence
			(
				this,
				GetActualOffset(edge == -0x1I64 ? _capacity - 0x1I64 : edge),
				GetActualOffset(offset)
			);
		}
		DescendingSequence GetDescendingSequence() const
		{
			return GetDescendingSequence
			(
				-0x1I64,
				_count - 0x1I64
			);
		}
		bool TryAddLast(T const value)
		{
			if (_count++ != MaxIntegerValue)
			{
				if (_count <= _capacity)
				{
				Setting:
					_elements[_endOffset++] = value;
					if (_endOffset == _capacity)
						_endOffset = 0x0I64;
					return true;
				}
				IncreaseCapacity();
				goto Setting;
			}
			_count--;
			return false;
		}
		bool TryAddFirst(T const value)
		{
			if (_count++ != MaxIntegerValue)
			{
				if (_count <= _capacity)
				{
				CheckingOffset:
					if (--_startOffset >= 0x0I64)
					{
					Setting:
						_elements[_startOffset] = value;
						return true;
					}
					_startOffset = _capacity - 0x1I64;
					goto Setting;
				}
				IncreaseCapacity();
				goto CheckingOffset;
			}
			_count--;
			return false;
		}
		void Set(Integer const offset, T const value) { _elements[GetActualOffset(offset)] = value; }
		bool TryRemoveLast(T& value)
		{
			if (_count-- != 0x0I64)
			{
				if (--_endOffset >= 0x0I64)
				{
				Setting:
					value = _elements[_endOffset];
					return true;
				}
				_endOffset = _capacity - 0x1I64;
				goto Setting;
			}
			_count++;
			return false;
		}
		bool TryRemoveFirst(T& value)
		{
			if (_count-- != 0x0I64)
			{
				value = _elements[_startOffset];
				if (++_startOffset != _capacity)
					return true;
				_startOffset = 0x0I64;
				return true;
			}
			_count++;
			return false;
		}
		void Clear() 
		{
			_startOffset = _endOffset = _capacity >> 0x1I64;
			_count = 0x0I64;
		}
	};
}