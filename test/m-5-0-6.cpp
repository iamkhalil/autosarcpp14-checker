// Run: $ clang++ -fsyntax-only -std=c++14 -Wconversion -Werror -ferror-limit=0

#include <cstdint>

void func(void)
{
	int16_t s16;
	int32_t s32;

	s16 = s32; // Non-compliant
	s16 = static_cast<int16_t>(s32); // Compliant

	float f;
	double d;

	f = d; // Non-Compliant
	f = static_cast<float>(d); // Compliant

}
