#include "IntN.hpp"
#include <iostream>
#include <iomanip>

int main() {
  IntN a(-2);
  IntN b(290);
  ++a;
  std::cout << a.hex() << std::endl;
  return 0;
}