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
#include <iostream>
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
  }
  else m_bytes.resize(size, 0);
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

IntN& IntN::operator++() {
  auto iter = m_bytes.begin();
  std::pair<uint8_t, uint8_t> partialSum {0, 0};
  while (iter != m_bytes.end()) {
    partialSum = byteAdder(*iter, 1, 0);
    *iter = partialSum.first;
    if (partialSum.second == 0x00) break;
    ++iter;
  }
  return *this;
}

IntN IntN::operator++(int) {
  IntN prev = *this;
  ++(*this);
  return prev;
}

IntN& IntN::operator--() {
  auto iter = m_bytes.begin();
  std::pair<uint8_t, uint8_t> partialSub {0, 0};
  while (iter != m_bytes.end()) {
    partialSub = byteAdder(*iter, 0xFF, partialSub.second);
    *iter = partialSub.first;
    ++iter;
  }
  return *this;
}

IntN IntN::operator--(int) {
  IntN prev = *this;
  --(*this);
  return prev;
}

IntN IntN::addition(const IntN& t_num1, const IntN& t_num2) {
  if (t_num1.size() != t_num2.size()) throw(IntNUtils::IntNExceptionSizeMismatch());
  auto iterNum1 = t_num1.m_bytes.begin();
  auto iterNum2 = t_num2.m_bytes.begin();
  std::pair<uint8_t, uint8_t> partialSum{0,0};
  std::list<uint8_t> auxList;
  while (iterNum1 != t_num1.m_bytes.end() || iterNum2 != t_num2.m_bytes.end()) {
    partialSum = byteAdder(*iterNum1, *iterNum2, partialSum.second);
    auxList.emplace_back(partialSum.first);
    ++iterNum2;
    ++iterNum1;
  }
  IntN toReturn;
  toReturn.m_bytes = auxList;
  return toReturn;
}

bool IntN::setSize(const size_t t_size) {
  IntN prev = *this;
  if (ResizeAndTrunc(t_size)) {
    if (*this == prev) return true;
    else return false;
  }
  return true;
}

void IntN::complement2() {
  auto iter = m_bytes.begin();
  while (iter != m_bytes.end()) {
    *iter = ~(*iter);
    ++iter;
  }
  ++(*this);
}

IntN operator+(const IntN& t_num1, const IntN& t_num2) {
  std::pair<IntN, IntN> vars;
  if (t_num1.size() == t_num2.size()) vars = {t_num1, t_num2};
  else vars = IntN::getOperable(t_num1, t_num2);
  return IntN::addition(vars.first, vars.second);
}

IntN operator-(const IntN& t_num1, const IntN& t_num2) {
  std::pair<IntN, IntN> vars;
  if (t_num1.size() == t_num2.size()) vars = {t_num1, t_num2};
  else vars = IntN::getOperable(t_num1, t_num2);
  vars.second.complement2();
  return IntN::addition(vars.first, vars.second);  
}

std::pair<uint8_t, uint8_t> IntN::byteMultiplier(const uint8_t t_byte1, const uint8_t t_byte2, const uint8_t t_carry_in) {
  const uint16_t partialMult = static_cast<uint16_t>(t_byte1) * static_cast<uint16_t>(t_byte2) + static_cast<uint16_t>(t_carry_in);
  std::pair<uint8_t, uint8_t> mulCarry;
  mulCarry.first = static_cast<uint8_t>(partialMult);
  mulCarry.second = static_cast<uint8_t>(partialMult >> 8);
  return mulCarry;
}

IntN IntN::multiplication(const IntN& t_num1, const IntN& t_num2) {
  // assumes t_num1 is bigger than t_num2 (in bytes) (better perfomance)
  IntN auxNum1 = t_num1;
  IntN auxNum2 = t_num2;
  // Be sure both number are positives for correct multiplication
  // This make sure there is not overflow during byteMultiplier
  if (auxNum1.isNegative()) auxNum1.complement2(); 
  if (auxNum2.isNegative()) auxNum2.complement2();
  std::pair<uint8_t, uint8_t> partialMul(0, 0);
  std::list<IntN> toAdd; // List of all the sums will be made
  std::list<uint8_t> partialMulAllBytes; // aux list to make the Intn for the su,
  auto multipler = auxNum1.m_bytes.begin();
  auto multiplicand = auxNum2.m_bytes.begin();
  while (multiplicand != auxNum2.m_bytes.end()) {
    while (multipler != auxNum1.m_bytes.end()) {
      partialMul = byteMultiplier(*multipler, *multiplicand, partialMul.second);
      partialMulAllBytes.emplace_back(partialMul.first);
      ++multipler;
    }
    // Creating the new IntN for the sum
    IntN aux;
    aux.setSize(t_num1.size()); // make sure all are the same size for better perfomance
    aux.m_bytes = partialMulAllBytes; // Copy the bytes
     // Emplace back onto the list
    toAdd.emplace_back(aux);
    // Clear for next iteration
    partialMulAllBytes.clear();
    multipler = auxNum1.m_bytes.begin();
    ++multiplicand;
  }
  IntN result(0);
  // Sum all results
  for (const auto& iter : toAdd) {
    result = result + iter;
  }
  // Return
  if (t_num1.isNegative() != t_num2.isNegative()) result.complement2();
  return result;
}

IntN operator* (const IntN& t_num1, const IntN& t_num2) {
  if (t_num1.size() > t_num2.size()) return IntN::multiplication(t_num1, t_num2);
  else if (t_num2.size() > t_num1.size()) return IntN::multiplication(t_num2, t_num1);
  return IntN::multiplication(t_num1, t_num2);
}

IntN& operator+=(IntN& t_num1, const IntN& t_num2) {
  t_num1 = t_num1 + t_num2;
  return t_num1;
}

IntN& operator-=(IntN& t_num1, const IntN& t_num2) {
  t_num1 = t_num1 - t_num2;
  return t_num1;
}

IntN& operator*=(IntN& t_num1, const IntN& t_num2) {
  t_num1 = t_num1 * t_num2;
  return t_num1;
}