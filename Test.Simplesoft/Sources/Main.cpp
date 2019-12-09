#include <iostream>
#include <StaticStorage.h>
#include <DynamicStorage.h>
#include <Exception.h>

using namespace Simplesoft;

int Do(StaticStorage<int, 3> storage)
{
	return storage[1];
}

int main()
{
	StaticStorage<int, 3> storage;
	int a = storage[1];
	std::cout << "Hello World!\n" << a;
}