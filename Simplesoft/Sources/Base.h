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
		return *(Integer*)&value;
	if (sizeof(T) == 0x10i64)
		return *(Integer*)&value ^ *((Integer*)&value + 0x1i64);
	if (sizeof(T) == 0x18i64)
		return *(Integer*)&value ^ *((Integer*)&value + 0x1i64) ^ *((Integer*)&value + 0x2i64);
	if (sizeof(T) == 0x20i64)
		return *(Integer*)&value ^ *((Integer*)&value + 0x1i64) ^ *((Integer*)&value + 0x2i64) ^ *((Integer*)&value + 0x3i64);
	if (sizeof(T) == 0x28i64)
		return *(Integer*)&value ^ *((Integer*)&value + 0x1i64) ^ *((Integer*)&value + 0x2i64) ^ *((Integer*)&value + 0x3i64) ^ *((Integer*)&value + 0x4i64);
	if (sizeof(T) == 0x30i64)
		return *(Integer*)&value ^ *((Integer*)&value + 0x1i64) ^ *((Integer*)&value + 0x2i64) ^ *((Integer*)&value + 0x3i64) ^ *((Integer*)&value + 0x4i64) ^ *((Integer*)&value + 0x5i64);
	if (sizeof(T) == 0x38i64)
		return *(Integer*)&value ^ *((Integer*)&value + 0x1i64) ^ *((Integer*)&value + 0x2i64) ^ *((Integer*)&value + 0x3i64) ^ *((Integer*)&value + 0x4i64) ^ *((Integer*)&value + 0x5i64) ^ *((Integer*)&value + 0x6i64);
	if (sizeof(T) == 0x40i64)
		return *(Integer*)&value ^ *((Integer*)&value + 0x1i64) ^ *((Integer*)&value + 0x2i64) ^ *((Integer*)&value + 0x3i64) ^ *((Integer*)&value + 0x4i64) ^ *((Integer*)&value + 0x5i64) ^ *((Integer*)&value + 0x6i64) ^ *((Integer*)&value + 0x7i64);
	result = 0x0i64;
	for (Integer offset = 0x0; offset != sizeof(T); offset += sizeof(Integer))
		result ^= *(Integer*)((__int8*)&value + offset);
	return result;
}