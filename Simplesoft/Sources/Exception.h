#pragma once

namespace Simplesoft
{
	class Exception
	{
		const char* _message;

		public:

		Exception(const char* message);

		const char* GetMessage() const;
	};
}