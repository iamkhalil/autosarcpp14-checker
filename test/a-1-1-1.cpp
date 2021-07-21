// Run: $ clang++ -fsyntax-only -std=c++14 -Werror -ferror-limit=0

#include <iostream>
#include <cstdio>

void func(void)
{
	char *str;

	gets(str); // Non-compliant - gets() was removed from c++14
	std::cout << str << std::endl;
}
