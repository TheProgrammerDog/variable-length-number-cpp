#include "IntN.hpp"
#include <iostream>
#include <iomanip>

int main() {
  IntN a(290);
  IntN b(290);
  a.setSize(4);
  b.setSize(16);
  std::cout << std::boolalpha << (a != b) << std::endl;

  return 0;
}