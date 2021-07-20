// Run: $ Clang++ -fsyntax-only -std=c++14 -Wunsequenced -Werror -ferror-limit=0

#include <cstdint>
// The following notes give some guidance on how dependence on order of
// evaluation may occur, and therefore may assist in adopting the rule.

// 1) Increment or decrement operators
// As an example of what can go wrong, consider
void f1(std::uint8_t (&arr)[10], std::uint8_t idx) noexcept(false)
{
	std::uint16_t x = arr[idx] + idx++;
}
// This will give different results depending on whether arr[idx] is evaluated
// before idx++ or vice versa. The problem could be avoided by putting the
// increment operation in a separate statement. For example:
void f2(std::uint8_t (&arr)[10], std::uint8_t idx) noexcept(false)
{
	std::uint8_t x = arr[idx] + idx;
	idx++;
}

// 2) Function arguments
// The order of evaluation of function arguments is unspecified.
extern std::uint8_t func(std::uint8_t x, std::uint8_t y);
void f3() noexcept(false)
{
	std::uint8_t i = 0;
 	std::uint8_t x = func(i++, i);
}
// This will give different results depending on which of the functions two
// parameters is evaluated first.

// 3) Function pointers
// If a function is called via a function pointer there shall be no
// dependence
// on the order in which function-designator and function arguments are
// evaluated.
struct S
{
	void taskStartFn(S* obj) noexcept(false);
};
void f4(S* p) noexcept(false)
{
	p->taskStartFn(p++);
}

// 4) Nested assignment statements
// Assignments nested within expressions cause additional side effects. The best
// way to avoid any possibility of this leading to a dependence on order of
// evaluation is not to embed assignments within expressions. For example, the
// following is not recommended:
void f8(std::int32_t& x) noexcept(false)
{
	std::int32_t y = 4;
	x = y = y++; // It is undefined whether the final value of y is 4 or 5
}
