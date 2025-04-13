/**
 * Creator: AnormalDog
 * License: MIT
 * 
 * Implementation file, source code of the class IntN, represents
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
    IntN(long long t_num);
    // Special methods

  private:
    // Attributes
    std::list<uint8_t> m_bytes;
    constexpr static unsigned char m_defaultSize {8};
};

namespace IntNUtils {

class IntNException : public std::exception {
  public:
    IntNException(const std::string& t_errorMessage) : m_errorMessage(t_errorMessage) {}
    const char* what() const noexcept override {return m_errorMessage.c_str();}
  private:
    std::string m_errorMessage;
};

} // namespace IntNUtils