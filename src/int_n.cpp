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

#include <iostream>
#include <iomanip>
#include <sstream>

IntN::IntN(long long t_num) {
  if (t_num < 0) {
    m_sign = 1;
    t_num *= -1;
  }
  const unsigned long long numAux = static_cast<unsigned long long>(t_num);
  std::cout << numAux << std::endl;
  scale_and_clean(sizeof(t_num));
  IntN_utils::integer_to_bytes(m_bytes, numAux);
  minimize();
}

IntN::IntN() {
  scale_and_clean();
}

void IntN::scale_and_clean(unsigned long long t_size) {
  if (t_size != m_bytes.size()) {
    m_bytes.resize(t_size);
  }
  if (t_size > 0) {
    for (auto& iter : m_bytes) {
      iter &= std::byte{0};
    }
  }
}
bool IntN::scale_and_hold(unsigned long long t_size) {
  std::vector<std::byte> auxVector(std::move(m_bytes));
  scale_and_clean(t_size);
  for (std::size_t i = 0; i < std::min(auxVector.size(), static_cast<std::size_t>(t_size)); ++i) {
    m_bytes[i] = auxVector[i];
  }
  if (static_cast<std::size_t>(t_size) >= auxVector.size()) {
    return true; // Copy was completed
  }
  return false; // Incomplete copy
}


void IntN_utils::integer_to_bytes(std::vector<std::byte>& vector, unsigned long long number) {
  if (sizeof(number) != vector.size()) {
    throw(IntNExceptionSizeMismatch());
  }
  for (std::size_t i = 0; i < sizeof(number); ++i) {
    std::byte aux {static_cast<unsigned char>(number >> (sizeof(number) * i))};
    vector[i] = aux;
  }
}

std::string IntN::get_hex() const {
  std::stringstream auxBuffer;
  //if (m_sign == 1) {
  //  auxBuffer << '-';
  //}
  auxBuffer << std::hex << std::setfill('0');

  for (auto iter = m_bytes.rbegin(); iter != m_bytes.rend(); ++iter) {
    auxBuffer << std::setw(2) << std::to_integer<unsigned>(*iter);
  }
  return auxBuffer.str();
}

void IntN::minimize() {
  if (m_bytes.size() > 1) { // if the size is more than 1 byte
    std::vector<std::byte> auxVector;
    for (const auto& iter : m_bytes) {
      if (std::to_integer<unsigned char>(iter) != 0) {
        auxVector.push_back(iter);
      }
    }
    if (auxVector.size() < m_bytes.size()) { // if same size, nothing to minimize
      m_bytes = auxVector;
    }
    if (m_bytes.size() < 1) { // to avoid 0 size
      scale_and_clean();
    }
  }
}