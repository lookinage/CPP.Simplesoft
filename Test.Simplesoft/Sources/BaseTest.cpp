#include "BaseTest.h"

Integer SimplifyTest( )
{
	class Object
	{
		Integer _a;
		Integer _b;
		Integer _c;
		Integer _d;

	public:

		Object(Integer a, Integer b, Integer c, Integer d) : _a(a), _b(b), _c(c), _d(d) { }
	};

	Object const instance = { 0x000000000000FFFFI64, 0x00000000FFFF0000I64, 0x0000FFFF00000000I64, 0xFFFF000000000000I64 };
	return Simplify(instance);
}