/**
 * Creator: AnormalDog
 * License: MIT
 * 
 * Implementation file, source code of the class IntN, represents a number with
 *   variable size
 */

#include "int_n.hpp"
#include "int_n_utils.hpp"

#include <algorithm>

IntN::IntN(long long t_num) {
  if (t_num < 0) {
    m_sign = 1;
  }
  const unsigned long long numAux = static_cast<unsigned long long>(t_num);
  scale_size(sizeof(t_num));

}

void IntN::scale_size(unsigned long long t_size) {
  if (t_size != m_bytes.size()) {
    m_bytes.resize(t_size);
  }
  if (t_size > 1) std::fill(m_bytes.begin(), m_bytes.end(), 0);
}

void IntN_utils::integer_to_bytes(std::vector<std::byte>& vector, unsigned long long number) {
  if (sizeof(number) > vector.size()) {
    throw(IntNExceptionSizeMismatch());
  }
  
}