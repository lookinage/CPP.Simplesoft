#include <iostream>
#include "BaseTest.h"
#include "SetsTests\StaticStorageTest.h"
#include <Sets\DynamicStorage.h>
#include <Sets\StandingStack.h>
#include <Sets\LyingStack.h>
#include <Sets\Subset.h>
#include <Sets\Surjection.h>

void TestDynamicStorage()
{
	//Integer const count = 0xFI64;

	//Sets::DynamicStorage<Integer> storage = { };
	//for (Integer offset = 0x0I64; offset != count; offset++)
	//{
	//	if (storage.GetCount() != count)
	//		return -0x1I64;
	//	storage[offset] = offset;
	//	for (Integer checkingOffset; checkingOffset != offset; checkingOffset++)
	//		if (storage[checkingOffset] != checkingOffset)
	//			return checkingOffset;
	//}
	//return MaxInteger;
}
void TestStandingStack()
{
	Sets::StandingStack<Integer> stack(0x0I64);
	stack.TryAdd(1);
	stack.TryAdd(3);
	stack.TryAdd(2);
	Integer v = stack.GetAt(2);

	for (Sets::StandingStack<Integer>::AscendingEnumerator enumerator = stack.GetAscendingEnumerator(); !enumerator; ++enumerator)
	{
		std::cout << *enumerator;
	}
}
void TestLyingStack()
{
	Sets::LyingStack<Integer> stack(0x0I64);

	stack.TryAddFirst(1);
	stack.TryAddFirst(3);
	stack.TryAddLast(2);
	Integer v = stack.GetAt(0);
	Integer v2 = stack.GetAt(1);
	Integer v3 = stack.GetAt(2);

	for (Sets::LyingStack<Integer>::DescendingEnumerator enumerator = stack.GetDescendingEnumerator(); !enumerator; ++enumerator)
	{
		std::cout << *enumerator;
	}
}
void TestSubset()
{
	Sets::Subset<Integer> subset(0x0I64);

	Integer address;
	subset.TryAdd(1, address);
	subset.TryAdd(3, address);
	subset.TryAdd(2, address);
	subset.TryRemove(1);

	for (Sets::Subset<Integer>::Enumerator enumerator = subset.GetEnumerator(); !enumerator; ++enumerator)
	{
		std::cout << *enumerator;
	}
}
void TestSurjection()
{
	Sets::Surjection<Integer, Integer> surjection(0x0I64);

	Integer address;
	surjection.TryAdd({ 1, 2 }, address);
	surjection.TryAdd({ 3, 4 }, address);
	surjection.TryAdd({ 2, 3 }, address);
	surjection.TryRemove(1);

	for (Sets::Surjection<Integer, Integer>::Enumerator enumerator = surjection.GetEnumerator(); !enumerator; ++enumerator)
	{
		std::cout << (*enumerator).GetInput() << ' ' << (*enumerator).GetOutput() << ' ';
	}
}

Integer _capacity = 2;
Integer _count = 15;

__int32 main()
{
	Integer capacity = GetEnoughCapacity(_capacity, _count);
	return (__int32)capacity;
	SimplifyTest();
	SetsTests::StaticStorageTest();
}