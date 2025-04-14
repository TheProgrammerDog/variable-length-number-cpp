#include "IntN.hpp"
#include <iostream>
#include <iomanip>

int main() {
  IntN i (-0xFF);
  IntN j (0xFF);
  j.setSize(4);
  std::cout << (i * j).hex() << std::endl;

}