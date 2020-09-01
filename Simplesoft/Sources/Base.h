#pragma once

typedef __int64 Integer;

const Integer MinIntegerValue = 0x8000000000000000i64;
const Integer MaxIntegerValue = 0x7FFFFFFFFFFFFFFFi64;

template<typename T>
Integer Collapse(T const value)
{
	Integer result;

	if (sizeof(T) == 0x1i64)
		return *(__int8*)&value;
	if (sizeof(T) == 0x2i64)
		return *(__int16*)&value;
	if (sizeof(T) == 0x4i64)
		return *(__int32*)&value;
	if (sizeof(T) == 0x8i64)
		return *(__int64*)&value;
	if (sizeof(T) == 0x10i64)
		return *(__int64*)&value ^ *((__int64*)&value + 0x1i64);
	if (sizeof(T) == 0x18i64)
		return *(__int64*)&value ^ *((__int64*)&value + 0x1i64) ^ *((__int64*)&value + 0x2i64);
	if (sizeof(T) == 0x20i64)
		return *(__int64*)&value ^ *((__int64*)&value + 0x1i64) ^ *((__int64*)&value + 0x2i64) ^ *((__int64*)&value + 0x3i64);
	if (sizeof(T) == 0x28i64)
		return *(__int64*)&value ^ *((__int64*)&value + 0x1i64) ^ *((__int64*)&value + 0x2i64) ^ *((__int64*)&value + 0x3i64) ^ *((__int64*)&value + 0x4i64);
	if (sizeof(T) == 0x30i64)
		return *(__int64*)&value ^ *((__int64*)&value + 0x1i64) ^ *((__int64*)&value + 0x2i64) ^ *((__int64*)&value + 0x3i64) ^ *((__int64*)&value + 0x4i64) ^ *((__int64*)&value + 0x5i64);
	if (sizeof(T) == 0x38i64)
		return *(__int64*)&value ^ *((__int64*)&value + 0x1i64) ^ *((__int64*)&value + 0x2i64) ^ *((__int64*)&value + 0x3i64) ^ *((__int64*)&value + 0x4i64) ^ *((__int64*)&value + 0x5i64) ^ *((__int64*)&value + 0x6i64);
	if (sizeof(T) == 0x40i64)
		return *(__int64*)&value ^ *((__int64*)&value + 0x1i64) ^ *((__int64*)&value + 0x2i64) ^ *((__int64*)&value + 0x3i64) ^ *((__int64*)&value + 0x4i64) ^ *((__int64*)&value + 0x5i64) ^ *((__int64*)&value + 0x6i64) ^ *((__int64*)&value + 0x7i64);
	result = 0x0i64;
	for (__int64 offset = 0x0i64; offset != sizeof(T); offset += sizeof(__int64))
		result ^= *(__int64*)((__int8*)&value + offset);
	return result;
}
Integer GetEnoughCapacity(Integer capacity, Integer count)
{
	if (count == 0x0i64)
		return 0x1i64;
	do
	{
		capacity <<= 0x1i64;
		if (capacity < 0x0i64)
		{
			capacity = MaxIntegerValue;
			break;
		}
	}
	while (capacity < count);
	return capacity;
}