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
  if (isNegative()) {
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

std::pair<IntN, IntN> IntN::getOperable(const IntN& t_num1, const IntN& t_num2) {
  IntN num1Aux = t_num1;
  IntN num2Aux = t_num2;
  if (t_num1.size() < t_num2.size()) num1Aux.ResizeAndTrunc(num2Aux.size());
  else if (t_num2.size() < t_num1.size()) num2Aux.ResizeAndTrunc(num1Aux.size());
  return std::make_pair(num1Aux, num2Aux);
}

bool IntN::minusThan(const IntN& t_num1, const IntN& t_num2) {
  if (t_num1.size() != t_num2.size()) throw(IntNUtils::IntNExceptionSizeMismatch());
  else if (t_num1.isNegative() && !t_num2.isNegative()) return true;
  else if (!t_num1.isNegative() && t_num2.isNegative()) return false;
  
  auto iterNum1 = t_num1.m_bytes.rbegin();
  auto iterNum2 = t_num2.m_bytes.rbegin();
  while (iterNum1 != t_num1.m_bytes.rend() || iterNum2 != t_num2.m_bytes.rend()) {
    if (*iterNum1 > *iterNum2) return false;
    else if (*iterNum1 < *iterNum2) return true;
    ++iterNum1;
    ++iterNum2;
  }
  return false;
}

bool IntN::equalThan(const IntN& t_num1, const IntN& t_num2) {
  if (t_num1.size() != t_num2.size()) throw(IntNUtils::IntNExceptionSizeMismatch());

  auto iterNum1 = t_num1.m_bytes.rbegin();
  auto iterNum2 = t_num2.m_bytes.rbegin();
  while (iterNum1 != t_num1.m_bytes.rend() || iterNum2 != t_num2.m_bytes.rend()) {
    if (*iterNum1 != *iterNum2) return false;
    ++iterNum1;
    ++iterNum2;
  }
  return true;
}

bool IntN::minusEqualThan(const IntN& t_num1, const IntN& t_num2) {
  if (t_num1.size() != t_num2.size()) throw(IntNUtils::IntNExceptionSizeMismatch());
  else if (t_num1.isNegative() && !t_num2.isNegative()) return true;
  else if (!t_num1.isNegative() && t_num2.isNegative()) return false;
  
  auto iterNum1 = t_num1.m_bytes.rbegin();
  auto iterNum2 = t_num2.m_bytes.rbegin();
  while (iterNum1 != t_num1.m_bytes.rend() || iterNum2 != t_num2.m_bytes.rend()) {
    if (*iterNum1 > *iterNum2) return false;
    else if (*iterNum1 < *iterNum2) return true;
    ++iterNum1;
    ++iterNum2;
  }
  return true;
}

void IntN::ResizeAndClean(const std::size_t size) {
  if (size == 0) throw(IntNUtils::IntNExceptionSizeMismatch());
  m_bytes.clear();
  m_bytes.resize(size, 0);
}

void IntN::loadNum(const long long t_num) noexcept {
  m_bytes.clear();
  for (std::size_t i = 0; i < sizeof(t_num); ++i) {
    // the 8 is the number of bits in a byte :)
    m_bytes.emplace_back((t_num) >> 8 * i);
  }
}

bool operator< (const IntN& t_num1, const IntN& t_num2) {
  if (t_num1.size() != t_num2.size()) {
    std::pair<IntN, IntN> auxPair = IntN::getOperable(t_num1, t_num2);
    return IntN::minusThan(auxPair.first, auxPair.second);
  }
  return IntN::minusThan(t_num1, t_num2);
}

bool operator== (const IntN& t_num1, const IntN& t_num2) {
  if (t_num1.size() != t_num2.size()) {
    std::pair<IntN, IntN> auxPair = IntN::getOperable(t_num1, t_num2);
    return IntN::equalThan(auxPair.first, auxPair.second);
  }
  return IntN::equalThan(t_num1, t_num2);
}

bool operator!=(const IntN& t_num1, const IntN& t_num2) {
  if (t_num1.size() != t_num2.size()) {
    std::pair<IntN, IntN> auxPair = IntN::getOperable(t_num1, t_num2);
    return !(IntN::equalThan(auxPair.first, auxPair.second));
  }
  return !(IntN::equalThan(t_num1, t_num2));
}

bool operator<=(const IntN& t_num1, const IntN& t_num2) {
  if (t_num1.size() != t_num2.size()) {
    std::pair<IntN, IntN> auxPair = IntN::getOperable(t_num1, t_num2);
    return IntN::minusEqualThan(auxPair.first, auxPair.second);
  }
  return IntN::minusEqualThan(t_num1, t_num2);
}
bool operator>=(const IntN& t_num1, const IntN& t_num2) {
  if (t_num1.size() != t_num2.size()) {
    std::pair<IntN, IntN> auxPair = IntN::getOperable(t_num1, t_num2);
    return !(IntN::minusThan(auxPair.first, auxPair.second));
  }
  return !(IntN::minusThan(t_num1, t_num2));
}

bool operator> (const IntN& t_num1, const IntN& t_num2) {
  if (t_num1.size() != t_num2.size()) {
    std::pair<IntN, IntN> auxPair = IntN::getOperable(t_num1, t_num2);
    return !(IntN::minusEqualThan(auxPair.first, auxPair.second));
  }
  return !(IntN::minusEqualThan(t_num1, t_num2));
}

std::pair<uint8_t, uint8_t> IntN::byteAdder(const uint8_t t_byte1, const uint8_t t_byte2, const uint8_t t_carryIn) {
  const uint16_t partialAdder = static_cast<uint16_t>(t_byte1) + static_cast<uint16_t>(t_byte2) + static_cast<uint16_t>(t_carryIn);
  if (partialAdder > 0xFF) {
      return std::make_pair(static_cast<uint8_t>(partialAdder - 0x100), 0x01);
  }
  return std::make_pair(static_cast<uint8_t>(partialAdder), 0x00);
}