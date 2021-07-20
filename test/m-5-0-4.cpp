// Run: $ clang++ -fsyntax-only -std=c++14 -Wsign-conversion -Werror -ferror-limit=0

#include <cstdint>

void func(void)
{
	int x = 42;
	unsigned int y = x;  // Non-compliant

	int8_t s8;
	uint8_t u8;

	s8 = u8; // Non-compliant
	s8 = static_cast<int8_t>(u8); // Compliant

	u8 = s8 + u8; // Non-Compliant
	u8 = static_cast<uint8_t>(s8) + u8; // Compliant
}
