/**
 * Creator: AnormalDog
 * License: MIT
 * 
 * source file, implementation of the class IntN, represents
 *   a number with variable size
 */

#include "IntN.hpp"

#include <algorithm>
#include <sstream>
#include <iomanip>
#include <climits>

IntN::IntN() {
  ResizeAndClean();
}

IntN::IntN(const long long t_num) {
  loadNum(t_num);
}

bool IntN::ResizeAndTrunc(const std::size_t size) {
  if (size == 0) throw(IntNUtils::IntNExceptionSizeMismatch());
  else if (size == m_bytes.size()) return false;
  const bool hasBeenTrunced = (size < m_bytes.size()) ? true : false;
  if ((m_bytes.back() >> 7) == 1) {
    m_bytes.resize(size, UINT8_MAX);
    return hasBeenTrunced;
  }
  m_bytes.resize(size, 0);
  return hasBeenTrunced;
}

std::string IntN::hex() const noexcept {
  std::stringstream auxBuffer;
  auxBuffer << std::hex << std::setfill('0');
  auto iter = m_bytes.rbegin();
  while (iter != m_bytes.rend()) {
    auxBuffer << std::setw(2) << static_cast<unsigned short>(*iter);
    ++iter;
  }
  return auxBuffer.str();
}