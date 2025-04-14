#include "IntN.hpp"
#include <iostream>
#include <iomanip>

int main() {
  IntN a(-1);
  IntN b(290);
  --a;
  ++a;
  std::cout << a.hex() << std::endl;
  return 0;
}