// Run: clang++ -fsyntax-only -std=c++14 -Wnull-conversion -Werror -ferror-limit=0

#include <cstddef>
#include <cstdint>

void f1(int32_t);
void f2(int32_t *);

void f3()
{
	f1(NULL); // Non-compliant - NUll used as an integer.
	f2(NULL); // Compliant
}

int tmp = NULL;	// Non-compliant
size_t x = NULL; // Non-compliant
