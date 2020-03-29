#pragma once

#include "Base.h"
#include "DynamicStorage.h"

template<typename T>
class Stack
{
	struct AscendingSequence
	{
		friend class Stack;

		private:

		Stack* _stack;
		Integer _offset;
		Integer _edge;

		explicit AscendingSequence(Stack* const stack, Integer const offset, Integer const edge) : _stack(stack), _offset(offset), _edge(edge) { }

		public:

		struct Enumerator
		{
			friend struct AscendingSequence;

			DynamicStorage<T> _storage;
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

		Stack* _stack;
		Integer _offset;
		Integer _edge;

		explicit DescendingSequence(Stack* const stack, Integer const offset, Integer const edge) : _stack(stack), _offset(offset), _edge(edge) { }

		public:

		struct Enumerator
		{
			friend struct DescendingSequence;

			DynamicStorage<T> _storage;
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
	__int32 _count;

	public:

	explicit Stack(Integer const capacity) : _storage(capacity), _count(0x0LL)
	{
	}
	explicit Stack() : Stack(0x0LL)
	{
	}

	void Clear()
	{
		_count = 0x0LL;
	}
	bool Remove(T& const element)
	{
		if (_count == 0x0LL)
			return false;
		element = _storage[--_count];
		return true;
	}
	void Add(T const element)
	{
		Integer offset;

		_storage.EnsureCount(_count = (offset = _count) + 0x1LL);
		_storage[offset] = element;
	}
	Integer GetCount()
	{
		return _count;
	}
	AscendingSequence GetAscendingSequence(Integer const offset, Integer const edge)
	{
		return AscendingSequence(this, offset, edge);
	}
	AscendingSequence GetAscendingSequence()
	{
		return GetAscendingSequence(0x0LL, _count);
	}
	AscendingSequence GetDescendingSequence(Integer const offset, Integer const edge)
	{
		return AscendingSequence(this, offset, edge);
	}
	AscendingSequence GetDescendingSequence()
	{
		return GetDescendingSequence(_count - 0x1LL, -0x1LL);
	}

	T& operator[](Integer const index) const
	{
		return _storage[index];
	}
};