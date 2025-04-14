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
    inline std::size_t size() const noexcept {return m_bytes.size();}
    inline bool isNegative() const noexcept {return ((m_bytes.back() >> 7) == 0x01) ? true : false;};

    // Setters
    inline bool setSize(const size_t t_size) { return ResizeAndTrunc(t_size);}

    // Logical operator overloading
    friend bool operator< (const IntN& t_num1, const IntN& t_num2);
    friend bool operator==(const IntN& t_num1, const IntN& t_num2);
    friend bool operator!=(const IntN& t_num1, const IntN& t_num2);
    friend bool operator<=(const IntN& t_num1, const IntN& t_num2);
    friend bool operator> (const IntN& t_num1, const IntN& t_num2);
    friend bool operator>=(const IntN& t_num1, const IntN& t_num2);

  private:
    // Attributes
    std::list<uint8_t> m_bytes; // little endian
    constexpr static std::size_t m_defaultSize {sizeof(long long)};
    
    // Private methods
    void ResizeAndClean(const std::size_t t_size = IntN::m_defaultSize);
    bool ResizeAndTrunc(const std::size_t t_size = IntN::m_defaultSize);
    void loadNum(const long long t_num) noexcept;
    static std::pair<IntN, IntN> getOperable(const IntN& t_num1, const IntN& t_num2);

    // Logical private methods
    static bool minusThan(const IntN& t_num1, const IntN& t_num2);
    static bool equalThan(const IntN& t_num1, const IntN& t_num2);
    static bool minusEqualThan(const IntN& t_num1, const IntN& t_num2);

    // Arithmetic private methods
    static std::pair<uint8_t, uint8_t> byteAdder(const uint8_t t_byte1, const uint8_t t_byte2, const uint8_t t_carry_in);
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

// Inline is the cake