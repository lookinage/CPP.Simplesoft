#pragma once

template<typename T>
class Subset
{
	struct Slot
	{
		Integer _nextSlotIndex;
		Integer _hashCode;
		T _element;
	};
	struct Data
	{
		Slot* _slots;
		Integer* _bucketStartIndices;
		Integer _freeSlotIndex;
		Integer _usedSlotCount;
		Integer _count;
	};

	Data _storage;

	Subset(Data storage) : _storage(storage) { }

	public:

	struct Element
	{
		Integer const Address;
		T const Value;

		Element(Integer address, T value) : Address(address), Value(value) { }
	};

	class Editor
	{
		typename Data _storage;

		public:

		Editor(typename Data storage) : _storage(storage) { }

		void Clear();
		bool TryRemoveAt(Integer address, T& value);
		bool TryRemove(T value, Integer& address);
		bool TryAdd(T value, Integer& address);
		Element Add(T value);
	};
};