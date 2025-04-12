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
#include <cstdint>
#include <sstream>

IntN::IntN(long long t_num) {
  if (t_num < 0) {
    m_sign = 1;
    t_num *= -1;
  }
  const unsigned long long numAux = static_cast<unsigned long long>(t_num);
  scale_and_clean(sizeof(t_num));
  IntN_utils::integer_to_bytes(m_bytes, numAux);
  minimize();
}

IntN::IntN() {
  scale_and_clean();
}

void IntN::scale_and_clean(unsigned long long t_size) {
  if (t_size == 0) throw(IntNExceptionMinimalSize());
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
        auxVector.emplace_back(iter);
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

IntN operator+(const IntN& t_num1, const IntN& t_num2) {
  IntN copyNum1 = t_num1;
  IntN copyNum2 = t_num2;
  if (copyNum1.size() != copyNum2.size()) make_operable(copyNum1, copyNum2);
  if (copyNum1.m_sign == copyNum2.m_sign) {
    
  }
}

std::pair<std::byte, std::byte> IntN_utils::byte_adder(const std::byte& byte1, const std::byte& byte2, const std::byte& carry) {
  uint8_t carryOutNum{0};
  uint16_t sumOutNum{0};

  sumOutNum = 
    std::to_integer<uint16_t>(byte1) +
    std::to_integer<uint16_t>(byte2) +
    std::to_integer<uint16_t>(carry);

  if (sumOutNum > 255) {
    carryOutNum = 1;
    sumOutNum -= 255;
  }

  std::byte sumOut{static_cast<uint8_t>(sumOutNum)};
  std::byte carryOut{carryOutNum};
  return std::make_pair(sumOut, carryOut);
}

void make_operable(IntN& t_num1, IntN& t_num2) {
  if (t_num1.size() < t_num2.size()) {
    t_num1.scale_and_hold(t_num2.size());
  }
  else if (t_num2.size() < t_num1.size()) {
    t_num2.scale_and_hold(t_num1.size());  
  }
}

bool minus_than(const IntN& t_num1, const IntN& t_num2) {
  if (t_num1.m_sign > t_num2.m_sign) return true;
  else if (t_num2.m_sign > t_num1.m_sign) return false;

  for (int64_t i = (t_num1.size() - 1); i >= 0; --i) {
    const uint8_t byte1 = std::to_integer<uint8_t>(t_num1.m_bytes.at(i));
    const uint8_t byte2 = std::to_integer<uint8_t>(t_num2.m_bytes.at(i));
    if (byte1 < byte2) {
      return true;
    }
    else if (byte2 < byte1) {
      return false;
    }
  }
  return false; // are equal
}

bool equal_than(const IntN& t_num1, const IntN& t_num2) {
  if (t_num1.m_sign != t_num2.m_sign) return false;
  for (std::size_t i = 0; i < t_num1.size(); ++i) {
    const uint8_t byte1 = std::to_integer<uint8_t>(t_num1.m_bytes.at(i));
    const uint8_t byte2 = std::to_integer<uint8_t>(t_num2.m_bytes.at(i));
    if (byte1 != byte2) return false;
  }
  return true;
}

bool operator<(const IntN& t_num1, const IntN& t_num2) {
  IntN copyNum1 = t_num1;
  IntN copyNum2 = t_num2;
  if (copyNum1.size() != copyNum2.size()) make_operable(copyNum1, copyNum2);
  return minus_than(copyNum1, copyNum2);
}

bool operator==(const IntN& t_num1, const IntN& t_num2) {
  IntN copyNum1 = t_num1;
  IntN copyNum2 = t_num2;
  if (copyNum1.size() != copyNum2.size()) make_operable(copyNum1, copyNum2);
  return equal_than(copyNum1, copyNum2);
}

bool operator!=(const IntN& t_num1, const IntN& t_num2) {
  IntN copyNum1 = t_num1;
  IntN copyNum2 = t_num2;
  if (copyNum1.size() != copyNum2.size()) make_operable(copyNum1, copyNum2);
  return (!(equal_than(copyNum1, copyNum2)));
}

bool operator<=(const IntN& t_num1, const IntN& t_num2) {
  IntN copyNum1 = t_num1;
  IntN copyNum2 = t_num2;
  if (copyNum1.size() != copyNum2.size()) make_operable(copyNum1, copyNum2);
  return (minus_than(copyNum1, copyNum2) || equal_than(copyNum1, copyNum2));
}

bool operator>=(const IntN& t_num1, const IntN& t_num2) {
  IntN copyNum1 = t_num1;
  IntN copyNum2 = t_num2;
  if (copyNum1.size() != copyNum2.size()) make_operable(copyNum1, copyNum2);
  return (!(minus_than(copyNum1, copyNum2)));
}

bool operator> (const IntN& t_num1, const IntN& t_num2) {
  IntN copyNum1 = t_num1;
  IntN copyNum2 = t_num2;
  if (copyNum1.size() != copyNum2.size()) make_operable(copyNum1, copyNum2);
  return (!(minus_than(copyNum1, copyNum2) || equal_than(copyNum1, copyNum2)));
}