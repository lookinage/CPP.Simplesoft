#include "Exception.h"

namespace Simplesoft
{
	Exception::Exception(const char* message) { _message = message; }

	const char* Exception::GetMessage() const { return _message; }
}