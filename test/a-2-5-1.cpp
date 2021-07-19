// Run: $ clang++ -fsyntax-only -std=c++14 -Wtrigraphs -Werror -ferror-limit=0

#include <iostream>

void fn1(void)
{
	std::cout << "Enter date ??/??/??"; // Non-compliant, ??/??/?? becomes \\??
					    // after trigraph translation
}

void fn2(void)
{
	std::cout << "Enter date dd/mm/yy"; // Compliant
}

// Additional checks
std::string s0 = "??= converted to #";  // Non-compliant
std::string s1 = "??' converted to ^";  // Non-compliant
std::string s2 = "??( converted to [";  // Non-compliant
std::string s3 = "??) converted to ]";  // Non-compliant
std::string s4 = "??! converted to |";  // Non-compliant
std::string s5 = "??< converted to {";  // Non-compliant
std::string s6 = "??> converted to }";  // Non-compliant
std::string s7 = "??- converted to ~";  // Non-compliant
