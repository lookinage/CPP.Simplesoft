#include <iostream>
#include <Base.h>
#include <StaticStorage.h>
#include <DynamicStorage.h>
#include <Stack.h>

struct A
{
	__int32 _value;
};

void TestStaticStorage()
{
	StaticStorage<__int32, 0x3LL> storage = StaticStorage<__int32, 0x3LL>();
	std::cout << storage.GetCount() << std::endl;
	std::cout << storage[0x0LL] << std::endl;
	std::cout << storage[0x1LL] << std::endl;
	std::cout << storage[0x2LL] << std::endl;
	__int32& v = storage[0x0LL];
	v = 3;
	v = storage[0x0LL];
}
__int32& GetValue(DynamicStorage<__int32>& storage, __int32 offset)
{
	return storage[offset];
}
void TestDynamicStorage()
{
	DynamicStorage<__int32> storage(0x3LL);
	storage[0x0LL] = 0x2LL;
	storage[0x1LL] = 0x1LL;
	storage[0x2LL] = 0x0LL;

	bool a = storage == storage;

	std::cout << storage[0x0LL] << std::endl;
	std::cout << storage[0x1LL] << std::endl;
	std::cout << storage[0x2LL] << std::endl;

	storage.EnsureCount(0x50LL);

	std::cout << storage[0x0LL] << std::endl;
	std::cout << storage[0x1LL] << std::endl;
	std::cout << storage[0x2LL] << std::endl;
	std::cout << storage[0x3LL] << std::endl;
	std::cout << storage[0x4LL] << std::endl;
	std::cout << storage[0x5LL] << std::endl;

	__int32& v = GetValue(storage, 0x0LL);
	v = 3;
	v = GetValue(storage, 0x0LL);
}
void TestStack()
{
	Stack<__int32> stack;

	stack.Add(1);
	__int32& v = stack[0];

	stack[0] = 3;
	v = stack[0];

	v = 5;
	v = stack[0];
}

__int32 main()
{
	TestStack();
}