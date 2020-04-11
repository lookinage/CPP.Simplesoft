#include <iostream>
#include <Base.h>
#include <Sets\StaticStorage.h>
#include <Sets\DynamicStorage.h>
#include <Sets\Stack.h>

struct A
{
	__int32 _value;
};

void TestStaticStorage()
{
	Sets::StaticStorage<__int32, 0x3i64> storage = Sets::StaticStorage<__int32, 0x3i64>();
	std::cout << storage.GetCount() << std::endl;
	std::cout << storage[0x0i64] << std::endl;
	std::cout << storage[0x1i64] << std::endl;
	std::cout << storage[0x2i64] << std::endl;
	__int32& v = storage[0x0i64];
	v = 3;
	v = storage[0x0i64];
}
__int32& GetValue(Sets::DynamicStorage<__int32>& storage, __int32 offset)
{
	return storage[offset];
}
void TestDynamicStorage()
{
	Sets::DynamicStorage<__int32> storage(0x3i64);
	storage[0x0i64] = 0x2i64;
	storage[0x1i64] = 0x1i64;
	storage[0x2i64] = 0x0i64;

	bool a = storage == storage;

	std::cout << storage[0x0i64] << std::endl;
	std::cout << storage[0x1i64] << std::endl;
	std::cout << storage[0x2i64] << std::endl;

	storage.EnsureCapacity(0x50i64);

	std::cout << storage[0x0i64] << std::endl;
	std::cout << storage[0x1i64] << std::endl;
	std::cout << storage[0x2i64] << std::endl;
	std::cout << storage[0x3i64] << std::endl;
	std::cout << storage[0x4i64] << std::endl;
	std::cout << storage[0x5i64] << std::endl;

	__int32& v = GetValue(storage, 0x0i64);
	v = 3;
	v = GetValue(storage, 0x0i64);
}
void TestStack()
{
	Sets::Stack<__int32> stack(0x0i64);

	stack.Add(1);
	__int32& v = stack[0];

	stack[0] = 3;
	v = stack[0];

	v = 5;
	v = stack[0];
}

__int32 main()
{
	unsigned __int64 a = 0xFFFFFFFFFFFFFFFF;
	__int8* bytes = new __int8[a];

}