#pragma once

typedef __int64 Integer;
typedef __int8 Byte;

constexpr Integer MinInteger = 0x8000000000000000I64;
constexpr Integer MaxSignedInteger = 0x7FFFFFFFFFFFFFFFI64;
constexpr Integer MaxUnsignedInteger = 0xFFFFFFFFFFFFFFFFI64;
constexpr Integer Zero = 0x0I64;
constexpr Integer One = 0x1I64;
constexpr Integer Two = 0x2I64;
constexpr Integer Three = 0x3I64;
constexpr Integer Four = 0x4I64;
constexpr Integer Five = 0x5I64;
constexpr Integer Six = 0x6I64;
constexpr Integer Seven = 0x7I64;
constexpr Integer Eight = 0x8I64;
constexpr Integer Nine = 0x9I64;
constexpr Integer Ten = 0xAI64;
constexpr Integer Eleven = 0xBI64;
constexpr Integer Twelve = 0xCI64;
constexpr Integer Thirteen = 0xDI64;
constexpr Integer Fourteen = 0xEI64;
constexpr Integer Fifteen = 0xFI64;
constexpr Integer Sixteen = 0x10I64;
constexpr Integer Seventeen = 0x11I64;
constexpr Integer Eighteen = 0x12I64;
constexpr Integer Nineteen = 0x14I64;

template<typename T>
Integer Simplify
(
	T const& reference
)
{
	Integer result;

	Integer const* const pointer = (Integer const*)&reference;
	result = *pointer;
	for (Integer offset = sizeof(Integer); offset < sizeof(T); offset += sizeof(Integer))
	{
		Integer const* const currentPointer = (Integer*)((Byte*)pointer + offset);
		result ^= *currentPointer;
	}
	return result;
}
Integer GetEnoughCapacity
(
	Integer capacity,
	Integer const count
);