/**
 * Creator: AnormalDog
 * License: MIT
 * 
 * Implementation file, source code of the class IntN, represents
 *   a number with variable size
 */

#include "int_n.hpp"

#include <iostream>
#include <sstream>
#include <cstdint>
#include <iomanip>

IntN::IntN() {
  resizeAndClean(1);
}

IntN::IntN(long long t_number) {
  m_sign = (t_number < 0) ? true : false;
  unsigned long long t_numberAbs = static_cast<unsigned long long>(std::abs(t_number));
  resizeAndClean(0);
  for (std::size_t i = 0; i < sizeof(t_numberAbs); ++i) {
    unsigned char newByteNum = static_cast<unsigned char>(t_numberAbs >> (8 * i));
    m_bytes.emplace_back(std::byte{newByteNum});
  }
  minimize();
}

std::string IntN::get_hex() const {
  std::stringstream auxBuffer;
  if (m_sign == 1) {
    auxBuffer << '-';
  }
  auxBuffer << std::hex << std::setfill('0');
  for (auto iter = m_bytes.rbegin(); iter != m_bytes.rend(); ++iter) {
    auxBuffer << std::setw(2) << std::to_integer<unsigned>(*iter);
  }
  return auxBuffer.str();
}

void IntN::minimize() {
  std::list<std::byte> auxList;
  for (const auto& iter : m_bytes) {
    if (std::to_integer<unsigned>(iter) != 0) auxList.emplace_back(iter);
  }
  if (auxList.size() == 0) {
    resizeAndClean(1);
  }
  else {
    m_bytes = auxList;
  }
}

bool IntN::minusThan(const IntN& t_num1, const IntN& t_num2) {
  if (t_num1.size() != t_num2.size()) throw(IntNUtils::IntNExceptionMismatch());
  else if (t_num1.m_sign > t_num2.m_sign) return true; // -X < Y
  else if (t_num1.m_sign < t_num2.m_sign) return false; // X < -Y

  auto iterNum1 = t_num1.m_bytes.rbegin();
  auto iterNum2 = t_num2.m_bytes.rbegin();
  while (iterNum1 != t_num1.m_bytes.rend() || iterNum2 != t_num2.m_bytes.rend()) {
    const unsigned char byte1Num = std::to_integer<unsigned char>(*iterNum1);
    const unsigned char byte2Num = std::to_integer<unsigned char>(*iterNum2);
    if (byte1Num < byte2Num) return true;
    else if (byte1Num > byte2Num) return false;

    ++iterNum1;
    ++iterNum2;
  }
  return false;
}

bool IntN::equalThan(const IntN& t_num1, const IntN& t_num2) {
  if (t_num1.size() != t_num2.size()) throw(IntNUtils::IntNExceptionMismatch());
  else if (t_num1.m_sign != t_num2.m_sign) return false;
  auto iterNum1 = t_num1.m_bytes.rbegin();
  auto iterNum2 = t_num2.m_bytes.rbegin();
  while (iterNum1 != t_num1.m_bytes.rend() || iterNum2 != t_num2.m_bytes.rend()) {
    const unsigned char byte1Num = std::to_integer<unsigned char>(*iterNum1);
    const unsigned char byte2Num = std::to_integer<unsigned char>(*iterNum2);
    if (byte1Num != byte2Num) return false;

    ++iterNum1;
    ++iterNum2;
  }
  return true;
}

bool operator<(const IntN& t_num1, const IntN& t_num2) noexcept {
  if (t_num1.size() != t_num2.size()) {
    IntN auxNum1 = t_num1;
    IntN auxNum2 = t_num2;
    IntN::makeOperable(auxNum1, auxNum2);
    return IntN::minusThan(auxNum1, auxNum2);
  }
  return IntN::minusThan(t_num1, t_num2);
}

bool operator==(const IntN& t_num1, const IntN& t_num2) noexcept {
  if (t_num1.size() != t_num2.size()) {
    IntN auxNum1 = t_num1;
    IntN auxNum2 = t_num2;
    IntN::makeOperable(auxNum1, auxNum2);
    return IntN::equalThan(auxNum1, auxNum2);
  }
  return IntN::equalThan(t_num1, t_num2);
}

bool operator> (const IntN& t_num1, const IntN& t_num2) noexcept {
  if (t_num1.size() != t_num2.size()) {
    IntN auxNum1 = t_num1;
    IntN auxNum2 = t_num2;
    IntN::makeOperable(auxNum1, auxNum2);
    return (!(IntN::equalThan(auxNum1, auxNum2) || IntN::minusThan(auxNum1, auxNum2)));
  }
  return (!(IntN::equalThan(t_num1, t_num2) || IntN::minusThan(t_num1, t_num2)));
}

bool operator<= (const IntN& t_num1, const IntN& t_num2) noexcept {
  if (t_num1.size() != t_num2.size()) {
    IntN auxNum1 = t_num1;
    IntN auxNum2 = t_num2;
    IntN::makeOperable(auxNum1, auxNum2);
    return (IntN::equalThan(auxNum1, auxNum2) || IntN::minusThan(auxNum1, auxNum2));
  }
  return (IntN::minusThan(t_num1, t_num2) || IntN::equalThan(t_num1, t_num2));
}

bool operator>= (const IntN& t_num1, const IntN& t_num2) noexcept {
  if (t_num1.size() != t_num2.size()) {
    IntN auxNum1 = t_num1;
    IntN auxNum2 = t_num2;
    IntN::makeOperable(auxNum1, auxNum2);
    return (!(IntN::minusThan(auxNum1, auxNum2)));
  }
  return (!(IntN::minusThan(t_num1, t_num2)));
}

bool operator!=(const IntN& t_num1, const IntN& t_num2) noexcept {
  if (t_num1.size() != t_num2.size()) {
    IntN auxNum1 = t_num1;
    IntN auxNum2 = t_num2;
    IntN::makeOperable(auxNum1, auxNum2);
    return (!(IntN::equalThan(auxNum1, auxNum2)));
  }
  return (!(IntN::equalThan(t_num1, t_num2)));  
}

IntN IntN::addition(const IntN& t_num1, const IntN& t_num2) {
  if (t_num1.size() != t_num2.size()) throw(IntNUtils::IntNExceptionMismatch());
  std::byte carry{0};
  auto iterNum1 = t_num1.m_bytes.begin();
  auto iterNum2 = t_num2.m_bytes.begin();
  std::list<std::byte> newBytes;
  // iterate each byte, from less to high (remember little endian)
  while (iterNum1 != t_num1.m_bytes.end() || iterNum2 != t_num2.m_bytes.end()) {
    std::pair<std::byte, std::byte> partialSum = byteAdder(*iterNum1, *iterNum2, carry);
    carry = partialSum.second;
    newBytes.emplace_back(partialSum.first);
    ++iterNum1;
    ++iterNum2;
  }
  // if there is overflow
  if (std::to_integer<unsigned short>(carry) != 0) {
    newBytes.emplace_back(carry);
  }
  IntN toReturn;
  toReturn.m_bytes = newBytes;
  toReturn.m_sign = 0;
  return toReturn;
}

IntN operator+(const IntN& t_num1, const IntN& t_num2) {
  if (t_num1.size() != t_num2.size()) {
    IntN auxNum1 = t_num1;
    IntN auxNum2 = t_num2;
    IntN::makeOperable(auxNum1, auxNum2);
    return IntN::addition(auxNum1, auxNum2);
  }
  return IntN::addition(t_num1, t_num2);
}

IntN& IntN::operator++() {
  auto iter = m_bytes.begin();
  while (iter != m_bytes.end()) {
    unsigned short aux = std::to_integer<unsigned short>(*iter) + 1;
    if (aux > 255) {
      aux -= 256;
      *iter = std::byte{static_cast<unsigned char>(aux)};
    }
    else {
      *iter = std::byte{static_cast<unsigned char>(aux)};
      break;
    }
    ++iter;
  }
  return *this;
}

IntN IntN::operator++(int) {
  IntN aux = *this;
  ++(*this);
  return aux;
}

IntN IntN::complement2(const IntN& t_num) {
  IntN auxNum = t_num;
  auxNum.m_sign = 0;
  auxNum.resizeAndTrunc(auxNum.size() + 1);
  auto iter = auxNum.m_bytes.begin();
  while (iter != auxNum.m_bytes.end()) {
    *iter = ~(*iter);
    ++iter;
  }
  ++auxNum;
  return auxNum;
}

IntN operator- (const IntN& t_num1, const IntN& t_num2) {
  
}