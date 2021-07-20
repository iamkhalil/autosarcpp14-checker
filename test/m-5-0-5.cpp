// Run: $ clang++ -fsyntax-only -std=c++14 -Wconversion -Werror -ferror-limit=0

void foo(int, double);

void bar(void)
{
	float f;
	int i;

	i = f; // Non-compliant
	f = i; // Non-compliant
	i = static_cast<int>(f);   // Compliant
	f = static_cast<float>(i); // Compliant
	
	double d = 42.7;
	int x = 1137;

	foo(d, x); // Non-Compliant
	foo(static_cast<int>(d), static_cast<double>(x)); // Compliant
}
