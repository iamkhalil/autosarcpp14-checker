#include <ctime>
#include <iostream>

void func(void) {
  clock();                              // Non-compliant
  time_t current_time = time(NULL);     // Non-compliant
  difftime(current_time, current_time); // Non-compliant
  tm time_struct;
  mktime(&time_struct); // Non-compliant

  time_t raw_time;
  struct tm *time_info;
  time(&raw_time);                  // Non-Compliant
  time_info = localtime(&raw_time); // Non-compliant
  std::cout << "Current local time and date: " << asctime(time_info) << '\t'
            << ctime(&raw_time) << '\n'; // Non-compliant

  struct tm *ptr;
  ptr = gmtime(&raw_time); // Non-compliant
}

void func_with_std(void) {
  std::clock();                              // Non-compliant
  time_t current_time = std::time(NULL);     // Non-compliant
  std::difftime(current_time, current_time); // Non-compliant
  tm time_struct;
  std::mktime(&time_struct); // Non-compliant

  time_t raw_time;
  struct tm *time_info;
  std::time(&raw_time);                  // Non-compliant
  time_info = std::localtime(&raw_time); // Non-compliant
  std::cout << "Current local time and date: " << std::asctime(time_info)
            << std::ctime(&raw_time) << '\n'; // Non-compliant
  struct tm *ptr;
  ptr = std::gmtime(&raw_time); // Non-compliant
}
