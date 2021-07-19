// Run: $ clang++ -fsyntax-only -std=c++14 -Wcomment -Werror -ferror-limit=0

#include <cstdint>

void fn() noexcept
{
	std::int8_t idx = 0;
	// Incrementing idx before the loop starts // Requirement X.X.X \\
	++idx; // Non-compliant - ++idx was unexpectedly commented-out because of \
	character occurrence in the end of C++ comment

	constexpr std::int8_t limit = 10;
	for (; idx <= limit; ++idx)
	{
		// ...
	}
}
