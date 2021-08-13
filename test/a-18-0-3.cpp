#include <clocale> // Non-Compliant
#include <cstdio>
#include <ctime>
#include <cwchar>
//#include <locale.h> // Non-Compliant

int main()
{

  std::setlocale(LC_ALL, "en_US.UTF-8"); // Non-Compliant
  std::setlocale(LC_NUMERIC, "de_DE");   // Non-Compliant
  std::setlocale(LC_TIME, "ja_JP");      // Non-Compliant

  wchar_t str[100];
  std::time_t t = std::time(NULL);
  std::wcsftime(str, 100, L"%A %c", std::localtime(&t));
  std::wprintf(L"Number: %.2f\nDate: %Ls\n", 3.14, str);
}
