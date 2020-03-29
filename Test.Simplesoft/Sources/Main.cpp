#include <iostream>
#include <Base.h>
#include <StaticStorage.h>
#include <DynamicStorage.h>
#include <Stack.h>

struct A
{
	__int8 b;
	__int16 c;
};

__int32 main()
{
	Stack<int> stack;
	int v = stack[0];
	stack.Add(1);
	v = stack[0];

	stack[0] = 3;
	v = stack[0];

	StaticStorage<__int32, 0x3LL> staticStorage = StaticStorage<__int32, 0x3LL>();
	std::cout << staticStorage.GetCount() << std::endl;
	std::cout << staticStorage[0x0LL] << std::endl;
	std::cout << staticStorage[0x1LL] << std::endl;
	std::cout << staticStorage[0x2LL] << std::endl;

	DynamicStorage<__int32> dynamicStorage(0x3LL);
	dynamicStorage[0x0LL] = 0x2LL;
	dynamicStorage[0x1LL] = 0x1LL;
	dynamicStorage[0x2LL] = 0x0LL;

	bool a = dynamicStorage == dynamicStorage;

	std::cout << dynamicStorage[0x0LL] << std::endl;
	std::cout << dynamicStorage[0x1LL] << std::endl;
	std::cout << dynamicStorage[0x2LL] << std::endl;

	dynamicStorage.EnsureCount(0x50LL);

	std::cout << dynamicStorage[0x0LL] << std::endl;
	std::cout << dynamicStorage[0x1LL] << std::endl;
	std::cout << dynamicStorage[0x2LL] << std::endl;
	std::cout << dynamicStorage[0x3LL] << std::endl;
	std::cout << dynamicStorage[0x4LL] << std::endl;
	std::cout << dynamicStorage[0x5LL] << std::endl;
}