#pragma once

#include "..\Base.h"
#include "DynamicStorage.h"

namespace Sets 
{
	template<typename T>
	class Stack
	{
		struct AscendingSequence
		{
			friend class Stack;

		private:

			const Stack* const _stack;
			Integer const _edge;
			Integer _offset;

			explicit AscendingSequence(const Stack* const stack, Integer const edge, Integer const offset) : _stack(stack), _edge(edge), _offset(offset) { }

		public:

			struct Enumerator
			{
				friend struct AscendingSequence;

				DynamicStorage<T> const _storage;
				Integer _offset;

				explicit Enumerator(DynamicStorage<T> const storage, Integer const offset) : _storage(storage), _offset(offset) { }

			public:

				Enumerator& operator++()
				{
					_offset++;
					return *this;
				}
				bool operator==(Enumerator const other) const
				{
					return _offset == other._offset;
				}
				bool operator!=(Enumerator const other) const
				{
					return _offset != other._offset;
				}
				T operator*() const
				{
					return _storage[_offset];
				}
			};

			Enumerator begin() { return Enumerator(_stack->_storage, _offset); }
			Enumerator end() { return Enumerator(_stack->_storage, _edge); }
		};
		struct DescendingSequence
		{
			friend class Stack;

		private:

			const Stack* const _stack;
			Integer const _edge;
			Integer _offset;

			explicit DescendingSequence(const Stack* const stack, Integer const edge, Integer const offset) : _stack(stack), _edge(edge), _offset(offset) { }

		public:

			struct Enumerator
			{
				friend struct DescendingSequence;

				DynamicStorage<T> const _storage;
				Integer _offset;

				explicit Enumerator(DynamicStorage<T> const storage, Integer const offset) : _storage(storage), _offset(offset) { }

			public:

				Enumerator& operator++()
				{
					_offset--;
					return *this;
				}
				bool operator==(Enumerator const other) const
				{
					return _offset == other._offset;
				}
				bool operator!=(Enumerator const other) const
				{
					return _offset != other._offset;
				}
				T operator*() const
				{
					return _storage[_offset];
				}
			};

			Enumerator begin() { return Enumerator(_stack->_storage, _offset); }
			Enumerator end() { return Enumerator(_stack->_storage, _edge); }
		};

		DynamicStorage<T> _storage;
		Integer _count;

	public:

		explicit Stack(Integer const capacity) : _storage(capacity), _count(0x0i64)
		{
		}

		Integer GetCount()
		{
			return _count;
		}
		T Get(Integer const offset)
		{
			return _storage[offset];
		}
		AscendingSequence GetAscendingSequence(Integer const offset, Integer const edge) const
		{
			return AscendingSequence(this, edge, offset);
		}
		AscendingSequence GetAscendingSequence() const
		{
			return GetAscendingSequence(0x0i64, _count);
		}
		AscendingSequence GetDescendingSequence(Integer const offset, Integer const edge) const
		{
			return AscendingSequence(this, edge, offset);
		}
		AscendingSequence GetDescendingSequence() const
		{
			return GetDescendingSequence(_count - 0x1i64, -0x1i64);
		}
		bool Add(T const value)
		{
			Integer offset;

			if ((offset = _count) == MaxIntegerValue)
				return false;
			_storage.EnsureCapacity(_count = offset + 0x1i64);
			_storage[offset] = value;
			return true;
		}
		void Set(Integer const offset, T const value)
		{
			_storage[offset] = value;
		}
		bool Remove(T& value)
		{
			if (_count == 0x0i64)
				return false;
			value = _storage[--_count];
			return true;
		}
		void Clear()
		{
			_count = 0x0i64;
		}

		T& operator[](Integer const index) const
		{
			return _storage[index];
		}
	};
}