#pragma once

#include <Exception.h>

namespace Simplesoft
{
	namespace Sets
	{
		template<typename T>
		class Subset
		{
			struct Slot
			{
				int _nextSlotIndex;
				int _hashCode;
				typename T _element;
			};
			struct Data
			{
				typename Slot* _slots;
				int* _bucketStartIndices;
				int _freeSlotIndex;
				int _usedSlotCount;
				int _count;
			};

			typename Data _storage;

			Subset(typename Data storage) : _storage(storage) { }

			public:

			class Editor
			{
				typename Data _storage;

				public:

				Editor(typename Data storage) : _storage(storage) { }
			};
		};
	}
}