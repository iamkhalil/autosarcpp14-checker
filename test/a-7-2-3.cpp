#include <cstdint>

enum E1 : std::int32_t // Non-compliant
{
  E10,
  E11,
  E12
};

enum class E2 : std::int32_t // Compliant
{
  E20,
  E21,
  E22
};
