#pragma once

#include "..\Base.h"
#include "DynamicStorage.h"

namespace Sets
{
	template<typename T>
	class Ring
	{
		struct AscendingSequence
		{
			friend class Ring;

		private:

			const Ring* const _Ring;
			Integer const _edge;
			Integer _offset;

			explicit AscendingSequence(const Ring* const Ring, Integer const edge, Integer const offset) : _Ring(Ring), _edge(edge), _offset(offset) { }

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

			Enumerator begin() { return Enumerator(_Ring->_storage, _offset); }
			Enumerator end() { return Enumerator(_Ring->_storage, _edge); }
		};
		struct DescendingSequence
		{
			friend class Ring;

		private:

			const Ring* const _Ring;
			Integer const _edge;
			Integer _offset;

			explicit DescendingSequence(const Ring* const Ring, Integer const edge, Integer const offset) : _Ring(Ring), _edge(edge), _offset(offset) { }

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

			Enumerator begin() { return Enumerator(_Ring->_storage, _offset); }
			Enumerator end() { return Enumerator(_Ring->_storage, _edge); }
		};

		DynamicStorage<T> _storage;
		Integer _startIndex;
		Integer _endIndex;
		Integer _count;

		void IncreaseCapacity()
		{
			int previousCapacity = _storage.GetCount();
			do
			{
				if ((capacity <<= 0x1) > 0x0)
					continue;
				capacity = int.MaxValue;
				break;
			}
			while (capacity < size);
			int startIndex;
			int endIndex;
			int count = _count;
			T[] newStorage = new T[capacity];
			if ((startIndex = _startIndex) < (endIndex = _endIndex))
				Array.Copy(storage, startIndex, newStorage, 0x0, count);
			else
			{
				Array.Copy(storage, startIndex, newStorage, 0x0, previousCapacity - startIndex);
				Array.Copy(storage, 0x0, newStorage, previousCapacity - startIndex, endIndex);
			}
			_storage = newStorage;
			_startIndex = 0x0;
			_endIndex = count;
		}

	public:

		explicit Ring(Integer const capacity) : _storage(capacity), _count(0x0i64)
		{
		}

		Integer GetCount()
		{
			return _count;
		}
		T Get(Integer const offset)
		{
			return  _startIndex + offset < _storage.GetCount() ? _storage[_startIndex + offset] : _storage[offset - _storage.GetCount() + _startIndex];
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
		bool AddEnd(T const value)
		{
			int count;
			int capacity;

			if ((count = _count) == (capacity = _storage.GetCount()))
			{
				IncreaseCapacity(storage, capacity, count + 0x1);
				capacity = (storage = _storage).Length;
			}
			int endIndex;
			storage[endIndex = _endIndex] = element;
			_endIndex = ++endIndex != capacity ? endIndex : 0x0;
			_count = count + 0x1;
		}
		void Set(Integer const offset, T const value)
		{
			_storage[offset] = value;
		}
		bool Remove(T& const value)
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