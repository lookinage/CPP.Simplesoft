#include <iostream>
#include <Base.h>
#include <Sets\StaticStorage.h>
#include <Sets\DynamicStorage.h>
#include <Sets\StandingStack.h>
#include <Sets\LyingStack.h>

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
	__int32& v = stack[2];

	auto a =  stack.GetAscendingSequence();

	for (__int32 value : a)
	{
		std::cout << value;
	}

	stack[0] = 3;
	v = stack[0];

	v = 5;
	v = stack[0];
}
void TestLyingStack()
{
	Sets::LyingStack<__int32> stack(0x0I64);

	stack.TryAddFirst(1);
	stack.TryAddFirst(3);
	stack.TryAddFirst(2);
	__int32& v = stack[0];
	__int32& v2 = stack[1];
	__int32& v3 = stack[2];

	auto a = stack.GetDescendingSequence();

	for (__int32 value : a)
	{
		std::cout << value;
	}

	stack[0] = 3;
	v = stack[0];

	v = 5;
	v = stack[0];
}


__int32 main()
{
	void* p = new __int32[0];
	TestLyingStack();
}