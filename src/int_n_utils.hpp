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
    
  } // namespace IntN_utils

// General exception for IntN and utils
class IntNException : public std::exception {
  public:
    IntNException(const std::string& t_error_message) : m_error_message(t_error_message) {}
    const char* what() const noexcept override {return m_error_message.c_str();}
  private:
    std::string m_error_message;
};

class IntNExceptionSizeMismatch : public IntNException {
  public:
    IntNExceptionSizeMismatch() : IntNException("the sizes of two elements have dismatched at some point") {}
};