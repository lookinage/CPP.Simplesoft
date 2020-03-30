#pragma once

typedef __int8 Byte;
typedef __int64 Integer;

template<typename T>
Integer Collapse(T& const value)
{
	Integer result;

	if (sizeof(T) == 0x1LL)
		return *(__int8*)&value;
	if (sizeof(T) == 0x2LL)
		return *(__int16*)&value;
	if (sizeof(T) == 0x4LL)
		return *(__int32*)&value;
	if (sizeof(T) == 0x8LL)
		return *(Integer*)&value;
	if (sizeof(T) == 0x10LL)
		return *(Integer*)&value ^ *((Integer*)&value + 0x1LL);
	if (sizeof(T) == 0x18LL)
		return *(Integer*)&value ^ *((Integer*)&value + 0x1LL) ^ *((Integer*)&value + 0x2LL);
	if (sizeof(T) == 0x20LL)
		return *(Integer*)&value ^ *((Integer*)&value + 0x1LL) ^ *((Integer*)&value + 0x2LL) ^ *((Integer*)&value + 0x3LL);
	if (sizeof(T) == 0x28LL)
		return *(Integer*)&value ^ *((Integer*)&value + 0x1LL) ^ *((Integer*)&value + 0x2LL) ^ *((Integer*)&value + 0x3LL) ^ *((Integer*)&value + 0x4LL);
	if (sizeof(T) == 0x30LL)
		return *(Integer*)&value ^ *((Integer*)&value + 0x1LL) ^ *((Integer*)&value + 0x2LL) ^ *((Integer*)&value + 0x3LL) ^ *((Integer*)&value + 0x4LL) ^ *((Integer*)&value + 0x5LL);
	if (sizeof(T) == 0x38LL)
		return *(Integer*)&value ^ *((Integer*)&value + 0x1LL) ^ *((Integer*)&value + 0x2LL) ^ *((Integer*)&value + 0x3LL) ^ *((Integer*)&value + 0x4LL) ^ *((Integer*)&value + 0x5LL) ^ *((Integer*)&value + 0x6LL);
	if (sizeof(T) == 0x40LL)
		return *(Integer*)&value ^ *((Integer*)&value + 0x1LL) ^ *((Integer*)&value + 0x2LL) ^ *((Integer*)&value + 0x3LL) ^ *((Integer*)&value + 0x4LL) ^ *((Integer*)&value + 0x5LL) ^ *((Integer*)&value + 0x6LL) ^ *((Integer*)&value + 0x7LL);
	result = 0x0LL;
	for (Integer offset = 0x0; offset != sizeof(T); offset += sizeof(Integer))
		result ^= *(Integer*)((__int8*)&value + offset);
	return result;
}