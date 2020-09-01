#pragma once

#include "..\Base.h"
#include "DynamicStorage.h"

namespace Sets
{
	template<typename T>
	class LyingStack
	{
		struct AscendingSequence
		{
			friend class LyingStack;

		private:

			const LyingStack* const _stack;
			Integer const _edge;
			Integer _offset;

			explicit AscendingSequence(const LyingStack* const stack, Integer const edge, Integer const offset) : _stack(stack), _edge(edge), _offset(offset) { }

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
					if (++_offset == _storage.GetCapacity())
						_offset = 0x0i64;
					return *this;
				}
				bool operator==(Enumerator const other) const { return _offset == other._offset; }
				bool operator!=(Enumerator const other) const { return _offset != other._offset; }
				T operator*() const { return _storage[_offset]; }
			};

			Enumerator begin() { return Enumerator(_stack->_storage, _offset); }
			Enumerator end() { return Enumerator(_stack->_storage, _edge); }
		};
		struct DescendingSequence
		{
			friend class LyingStack;

		private:

			const LyingStack* const _stack;
			Integer const _edge;
			Integer _offset;

			explicit DescendingSequence(const LyingStack* const Ring, Integer const edge, Integer const offset) : _stack(Ring), _edge(edge), _offset(offset) { }

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
					if (--_offset < 0x0i64)
						_offset = _storage.GetCapacity() - 0x1i64;
					return *this;
				}
				bool operator==(Enumerator const other) const { return _offset == other._offset; }
				bool operator!=(Enumerator const other) const { return _offset != other._offset; }
				T operator*() const { return _storage[_offset]; }
			};

			Enumerator begin() { return Enumerator(_stack->_storage, _offset); }
			Enumerator end() { return Enumerator(_stack->_storage, _edge); }
		};

		DynamicStorage<T> _storage;
		Integer _startIndex;
		Integer _endIndex;
		Integer _count;

	public:

		explicit LyingStack(Integer const capacity) : _storage(capacity), _count(0x0i64) { }

		Integer GetCount() { return _count; }
		T Get(Integer const offset) { return  _startIndex + offset < _storage.GetCapacity() ? _storage[_startIndex + offset] : _storage[offset - _storage.GetCapacity() + _startIndex]; }
		AscendingSequence GetAscendingSequence(Integer const offset, Integer const edge) const { return AscendingSequence(this, edge, offset); }
		AscendingSequence GetAscendingSequence() const { return GetAscendingSequence(0x0i64, _count); }
		AscendingSequence GetDescendingSequence(Integer const offset, Integer const edge) const { return AscendingSequence(this, edge, offset); }
		AscendingSequence GetDescendingSequence() const { return GetDescendingSequence(_count - 0x1i64, -0x1i64); }
		bool AddLast(T const value)
		{
			if (_count == MaxIntegerValue)
				return false;
			if (_count++ == _storage.GetCapacity())
				_storage.EnsureCapacity(_count);
			_storage[_endIndex] = value;
			if (++_endIndex == _storage.GetCapacity())
				_endIndex = 0x0i64;
			return true;
		}
		bool AddFirst(T const value)
		{
			if (_count == MaxIntegerValue)
				return false;
			if (_count++ == _storage.GetCapacity())
				_storage.EnsureCapacity(_count);
			if (--_startIndex < 0x0i64)
				_startIndex = _storage.GetCapacity() - 0x1i64;
			_storage[_startIndex] = value;
			return true;
		}
		void Set(Integer const offset, T const value) { _storage[offset] = value; }
		bool RemoveLast(T& const value)
		{
			if (_count == 0x0i64)
				return false;
			_count--;
			if (--_endIndex < 0x0i64)
				_endIndex = _storage.GetCapacity() - 0x1i64;
			value = _storage[_endIndex];
			return true;
		}
		bool RemoveFirst(T& const value)
		{
			if (_count == 0x0i64)
				return false;
			_count--;
			value = _storage[_startIndex];
			if (++_startIndex == _storage.GetCapacity())
				_startIndex = 0x0i64;
			return true;
		}
		void Clear() { _count = 0x0i64; }

		T& operator[](Integer const index) const { return _storage[index]; }
	};
}