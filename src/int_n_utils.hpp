/**
 * Creator: AnormalDog
 * License: MIT
 * 
 * Header file, auxilar and util functions/classes used internally by int_n
 * 
 */

#pragma once

#include "int_n.hpp"

#include <string>
#include <exception>

namespace IntN_utils {

void integer_to_bytes(std::vector<std::byte>& vector, unsigned long long number);
std::pair<std::byte, std::byte> byte_adder(const std::byte& byte1, 
  const std::byte& byte2, const std::byte& carry);
} // namespace IntN_utils

// General exception for IntN and utils
class IntNException : public std::exception {
  public:
    IntNException(const std::string& t_error_message) : m_error_message(t_error_message) {}
    const char* what() const noexcept override {return m_error_message.c_str();}
  private:
    std::string m_error_message;
};

// Exception used when a operation requires same byte size, and it doesn't
class IntNExceptionSizeMismatch : public IntNException {
  public:
    IntNExceptionSizeMismatch() : IntNException("the sizes of two elements have dismatched at some point") {}
};

// Exception when the vector of bytes is smaller than 1 byte (size 0)
class IntNExceptionMinimalSize : public IntNException {
  public:
    IntNExceptionMinimalSize() : IntNException("the size of the vector is smaller than 1, so is empty") {}
};