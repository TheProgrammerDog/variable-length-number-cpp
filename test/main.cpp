#include "int_n.hpp"

#include <cstddef>
#include <iostream>
#include <iomanip>

int main() {
  IntN num1(499);
  IntN num2(498);
  std::cout << std::boolalpha;
  std::cout << (num1 < num2) << std::endl;
  std::cout << (num1 == num2) << std::endl;
  return 0;
}