#pragma once

typedef __int8 Byte;
typedef __int64 Integer;

template<typename T>
__int64 Collapse(T& const value)
{
	__int64 result;

	if (sizeof(T) == 0x1LL)
		return *(__int8*)&value;
	if (sizeof(T) == 0x2LL)
		return *(__int16*)&value;
	if (sizeof(T) == 0x4LL)
		return *(__int32*)&value;
	if (sizeof(T) == 0x8LL)
		return *(__int64*)&value;
	if (sizeof(T) == 0x10LL)
		return *(__int64*)&value ^ *((__int64*)&value + 0x1LL);
	if (sizeof(T) == 0x18LL)
		return *(__int64*)&value ^ *((__int64*)&value + 0x1LL) ^ *((__int64*)&value + 0x2LL);
	if (sizeof(T) == 0x20LL)
		return *(__int64*)&value ^ *((__int64*)&value + 0x1LL) ^ *((__int64*)&value + 0x2LL) ^ *((__int64*)&value + 0x3LL);
	if (sizeof(T) == 0x28LL)
		return *(__int64*)&value ^ *((__int64*)&value + 0x1LL) ^ *((__int64*)&value + 0x2LL) ^ *((__int64*)&value + 0x3LL) ^ *((__int64*)&value + 0x4LL);
	if (sizeof(T) == 0x30LL)
		return *(__int64*)&value ^ *((__int64*)&value + 0x1LL) ^ *((__int64*)&value + 0x2LL) ^ *((__int64*)&value + 0x3LL) ^ *((__int64*)&value + 0x4LL) ^ *((__int64*)&value + 0x5LL);
	if (sizeof(T) == 0x38LL)
		return *(__int64*)&value ^ *((__int64*)&value + 0x1LL) ^ *((__int64*)&value + 0x2LL) ^ *((__int64*)&value + 0x3LL) ^ *((__int64*)&value + 0x4LL) ^ *((__int64*)&value + 0x5LL) ^ *((__int64*)&value + 0x6LL);
	if (sizeof(T) == 0x40LL)
		return *(__int64*)&value ^ *((__int64*)&value + 0x1LL) ^ *((__int64*)&value + 0x2LL) ^ *((__int64*)&value + 0x3LL) ^ *((__int64*)&value + 0x4LL) ^ *((__int64*)&value + 0x5LL) ^ *((__int64*)&value + 0x6LL) ^ *((__int64*)&value + 0x7LL);
	result = 0x0LL;
	for (__int64 offset = 0x0; offset != sizeof(T); offset += 0x8LL)
		result ^= *(__int64*)((__int8*)&value + offset);
	return result;
}