#include "int_n.hpp"

#include <cstddef>
#include <iostream>
#include <iomanip>

int main() {
  IntN num1(-500);
  std::cout << num1.get_hex() << std::endl;
  std::cout << IntN::complement2(num1).get_hex() << std::endl;
  
  return 0;
}