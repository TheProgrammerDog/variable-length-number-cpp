#include "IntN.hpp"
#include <iostream>
#include <iomanip>


int main() {
  IntN i (9223372036854775807);
  i.setSize(30);
  IntN j (9223372036854775807);
  j.setSize(30);
  IntN mul;
  mul = i * j;

  //std::cout << i.hex() << std::endl << rightByteWise(i, 3).hex() << std::endl;
  std::cout << std::endl << mul.hex() << std::endl;

}