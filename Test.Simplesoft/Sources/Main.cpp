#include <iostream>
#include <Base.h>
#include <Sets\StaticStorage.h>
#include <Sets\DynamicStorage.h>
#include <Sets\StandingStack.h>
#include <Sets\LyingStack.h>
#include <Sets\Subset.h>

struct A
{
	__int32 _value;
};

void TestStaticStorage()
{
	Sets::StaticStorage<__int32, 0x3I64> storage = Sets::StaticStorage<__int32, 0x3I64>();
	std::cout << storage.GetCount() << std::endl;
	std::cout << storage[0x0I64] << std::endl;
	std::cout << storage[0x1I64] << std::endl;
	std::cout << storage[0x2I64] << std::endl;
	__int32& v = storage[0x0I64];
	v = 3;
	v = storage[0x0I64];
}
__int32& GetValue(Sets::DynamicStorage<__int32>& storage, __int32 offset)
{
	return storage[offset];
}
void TestDynamicStorage()
{
	Sets::DynamicStorage<__int32> storage(0x3I64);
	storage[0x0I64] = 0x2I64;
	storage[0x1I64] = 0x1I64;
	storage[0x2I64] = 0x0I64;

	bool a = storage == storage;

	std::cout << storage[0x0I64] << std::endl;
	std::cout << storage[0x1I64] << std::endl;
	std::cout << storage[0x2I64] << std::endl;

	storage.SetCapacity(0x50I64);

	std::cout << storage[0x0I64] << std::endl;
	std::cout << storage[0x1I64] << std::endl;
	std::cout << storage[0x2I64] << std::endl;
	std::cout << storage[0x3I64] << std::endl;
	std::cout << storage[0x4I64] << std::endl;
	std::cout << storage[0x5I64] << std::endl;

	__int32& v = GetValue(storage, 0x0I64);
	v = 3;
	v = GetValue(storage, 0x0I64);
}
void TestStandingStack()
{
	Sets::StandingStack<__int32> stack(0x0I64);
	stack.TryAdd(1);
	stack.TryAdd(3);
	stack.TryAdd(2);
	__int32 v = stack.GetAt(2);

	for (Sets::StandingStack<__int32>::AscendingEnumerator enumerator = stack.GetAscendingEnumerator(); !enumerator; ++enumerator)
	{
		std::cout << *enumerator;
	}
}
void TestLyingStack()
{
	Sets::LyingStack<__int32> stack(0x0I64);

	stack.TryAddFirst(1);
	stack.TryAddFirst(3);
	stack.TryAddLast(2);
	__int32 v = stack.GetAt(0);
	__int32 v2 = stack.GetAt(1);
	__int32 v3 = stack.GetAt(2);

	for (Sets::LyingStack<__int32>::DescendingEnumerator enumerator = stack.GetDescendingEnumerator(); !enumerator; ++enumerator)
	{
		std::cout << *enumerator;
	}
}
void TestSubset()
{
	Sets::Subset<__int32> subset(0x0I64);

	Integer address;
	subset.TryAdd(1, address);
	subset.TryAdd(3, address);
	subset.TryAdd(2, address);
	subset.TryRemove(1);

	for (Sets::Subset<__int32>::Enumerator enumerator = subset.GetEnumerator(); !enumerator; ++enumerator)
	{
		std::cout << *enumerator;
	}
}

__int32 main()
{
	TestSubset();
}