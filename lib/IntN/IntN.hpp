/**
 * Creator: AnormalDog
 * License: MIT
 * 
 * header file, interface of the class IntN, represents
 *   a number with variable size
 */

#pragma once

#include <list>
#include <cstdint>
#include <string>
#include <exception>

class IntN {
  public:
    // Constructor
    IntN();
    IntN(const long long t_num);
    // Special methods
    ~IntN() = default;
    IntN(const IntN&) = default;
    IntN& operator=(const IntN&) = default;

    // Getters
    std::string hex() const noexcept; // return string with hex in big endian
  private:
    // Attributes
    std::list<uint8_t> m_bytes; // little endian
    constexpr static std::size_t m_defaultSize {sizeof(long long)};
    
    // Private methods
    inline void ResizeAndClean(const std::size_t t_size = IntN::m_defaultSize);
    bool ResizeAndTrunc(const std::size_t t_size = IntN::m_defaultSize);
    inline void loadNum(const long long t_num) noexcept;
};

namespace IntNUtils {

class IntNException : public std::exception {
  public:
    IntNException(const std::string& t_errorMessage) : m_errorMessage(t_errorMessage) {}
    const char* what() const noexcept override {return m_errorMessage.c_str();}
  private:
    std::string m_errorMessage;
};

class IntNExceptionSizeMismatch : public IntNException {
  public:
    IntNExceptionSizeMismatch() : IntNException("Error trying to operate two IntN with different internal sise") {}
};

class IntNExceptionMinimalSize : public IntNException {
  public:
    IntNExceptionMinimalSize() : IntNException("trying to resize a IntN to 0 bytes") {}
};

} // namespace IntNUtils

// Inline methods and functions
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