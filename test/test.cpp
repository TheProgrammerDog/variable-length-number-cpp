#include "IntN.hpp"
#include <iostream>
#include <iomanip>

int main() {
  for (IntN i(50); i >= IntN(0); --i) {
    std::cout << i.hex() << std::endl;
  }
  return 0;
}