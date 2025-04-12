#include "int_n.hpp"

#include <cstddef>
#include <iostream>

int main() {
  IntN n(-1000);
  std::cout << n.get_hex() << std::endl;
  n.minimize();
  std::cout << n.get_hex() << std::endl;

}