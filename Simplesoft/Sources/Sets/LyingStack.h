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

			if ((actualOffset = _startOffset + offset) >= _capacity)
				return actualOffset - _capacity;
			if (actualOffset < 0x0I64)
				return actualOffset + _capacity;
			return actualOffset;
		}
		inline void IncreaseCapacity()
		{
			T* elements;
			Integer capacity;

			capacity = GetEnoughCapacity(_capacity, _count);
			elements = new T[capacity];
			if (_startOffset != 0x0)
			{
				memcpy
				(
					elements,
					_elements + _startOffset,
					(_capacity - _startOffset) * sizeof(T)
				);
				memcpy
				(
					elements + _capacity - _startOffset,
					_elements,
					(_startOffset) * sizeof(T)
				);
			}
			else
				memcpy
				(
					elements,
					_elements,
					_capacity * sizeof(T)
				);
			delete _elements;
			_elements = elements;
			_capacity = capacity;
			_startOffset = 0x0I64;
			_endOffset = _count - 0x1I64;
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

				Enumerator& operator++()
				{
					if (++_offset == _stack->_capacity)
						_offset = 0x0I64;
					return *this;
				}
				bool operator==(Enumerator const other) const { return _offset == other._offset; }
				bool operator!=(Enumerator const other) const { return _offset != other._offset; }
				T operator*() const { return _stack->_elements[_offset]; }
			};

			Enumerator begin() { return Enumerator(_stack, _offset); }
			Enumerator end() { return Enumerator(_stack, _edge); }
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

				Enumerator& operator++()
				{
					if (--_offset < 0x0I64)
						_offset = _stack->_capacity - 0x1I64;
					return *this;
				}
				bool operator==(Enumerator const other) const { return _offset == other._offset; }
				bool operator!=(Enumerator const other) const { return _offset != other._offset; }
				T operator*() const { return _stack->_elements[_offset]; }
			};

			Enumerator begin() { return Enumerator(_stack, _offset); }
			Enumerator end() { return Enumerator(_stack, _edge); }
		};

		explicit LyingStack(Integer const capacity) : _elements(new T[capacity]), _capacity(capacity), _startOffset(0x0I64), _endOffset(0x0I64), _count(0x0I64) { }
		~LyingStack() { delete _elements; }

		Integer GetCount() const { return _count; }
		T TryGetAt(Integer const offset) { return _elements[GetActualOffset(offset)]; }
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
				GetActualOffset(edge),
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
					if (_endOffset != _capacity)
					{
					Adding:
						_elements[_endOffset++] = value;
						return true;
					}
					_endOffset = 0x0I64;
					goto Adding;
				}
				IncreaseCapacity();
				goto Adding;
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
					Adding:
						_elements[_startOffset] = value;
						return true;
					}
					_startOffset = _capacity - 0x1I64;
					goto Adding;
				}
				IncreaseCapacity();
				goto CheckingOffset;
			}
			_count--;
			return false;
		}
		void Set(Integer const offset, T const value) { _elements[offset] = value; }
		bool TryRemoveLast(T& value)
		{
			if (_count == 0x0I64)
				return false;
			_count--;
			if (--_endOffset < 0x0I64)
				_endOffset = _capacity - 0x1I64;
			value = _elements[_endOffset];
			return true;
		}
		bool TryRemoveFirst(T& value)
		{
			if (_count == 0x0I64)
				return false;
			_count--;
			value = _elements[_startOffset];
			if (++_startOffset == _capacity)
				_startOffset = 0x0I64;
			return true;
		}
		void Clear() { _count = 0x0I64; }

		T& operator[](Integer const offset) const { return _elements[offset]; }
	};
}