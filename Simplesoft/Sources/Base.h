#pragma once

typedef __int64 Integer;

const Integer MinIntegerValue = 0x8000000000000000I64;
const Integer MaxIntegerValue = 0x7FFFFFFFFFFFFFFFI64;

template<typename T>
Integer Simplify(T&& value)
{
	Integer result;

	if (sizeof(T) == 0x1I64)
		return *(__int8*)&value;
	if (sizeof(T) == 0x2I64)
		return *(__int16*)&value;
	if (sizeof(T) == 0x4I64)
		return *(__int32*)&value;
	if (sizeof(T) == 0x8I64)
		return *(__int64*)&value;
	if (sizeof(T) == 0x10I64)
		return *(__int64*)&value ^ *((__int64*)&value + 0x1I64);
	if (sizeof(T) == 0x18I64)
		return *(__int64*)&value ^ *((__int64*)&value + 0x1I64) ^ *((__int64*)&value + 0x2I64);
	if (sizeof(T) == 0x20I64)
		return *(__int64*)&value ^ *((__int64*)&value + 0x1I64) ^ *((__int64*)&value + 0x2I64) ^ *((__int64*)&value + 0x3I64);
	if (sizeof(T) == 0x28I64)
		return *(__int64*)&value ^ *((__int64*)&value + 0x1I64) ^ *((__int64*)&value + 0x2I64) ^ *((__int64*)&value + 0x3I64) ^ *((__int64*)&value + 0x4I64);
	if (sizeof(T) == 0x30I64)
		return *(__int64*)&value ^ *((__int64*)&value + 0x1I64) ^ *((__int64*)&value + 0x2I64) ^ *((__int64*)&value + 0x3I64) ^ *((__int64*)&value + 0x4I64) ^ *((__int64*)&value + 0x5I64);
	if (sizeof(T) == 0x38I64)
		return *(__int64*)&value ^ *((__int64*)&value + 0x1I64) ^ *((__int64*)&value + 0x2I64) ^ *((__int64*)&value + 0x3I64) ^ *((__int64*)&value + 0x4I64) ^ *((__int64*)&value + 0x5I64) ^ *((__int64*)&value + 0x6I64);
	if (sizeof(T) == 0x40I64)
		return *(__int64*)&value ^ *((__int64*)&value + 0x1I64) ^ *((__int64*)&value + 0x2I64) ^ *((__int64*)&value + 0x3I64) ^ *((__int64*)&value + 0x4I64) ^ *((__int64*)&value + 0x5I64) ^ *((__int64*)&value + 0x6I64) ^ *((__int64*)&value + 0x7I64);
	result = 0x0I64;
	for (__int64 offset = 0x0I64; offset != sizeof(T); offset += sizeof(__int64))
		result ^= *(__int64*)((__int8*)&value + offset);
	return result;
}
Integer GetEnoughCapacity(Integer capacity, Integer const count);