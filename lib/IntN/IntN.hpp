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

    // Assignment
    friend IntN& operator+=(IntN& t_num1, const IntN& t_num2);
    friend IntN& operator-=(IntN& t_num1, const IntN& t_num2);
    friend IntN& operator*=(IntN& t_num1, const IntN& t_num2);

    // Getters
    std::string hex() const noexcept; // return string with hex in big endian
    inline std::size_t size() const noexcept {return m_bytes.size();}
    inline bool isNegative() const noexcept {return ((m_bytes.back() >> 7) == 0x01) ? true : false;};

    // Setters
    bool setSize(const size_t t_size);

    // Comparison operator overloading
    friend bool operator< (const IntN& t_num1, const IntN& t_num2);
    friend bool operator==(const IntN& t_num1, const IntN& t_num2);
    friend bool operator!=(const IntN& t_num1, const IntN& t_num2);
    friend bool operator<=(const IntN& t_num1, const IntN& t_num2);
    friend bool operator> (const IntN& t_num1, const IntN& t_num2);
    friend bool operator>=(const IntN& t_num1, const IntN& t_num2);

    // Arithmetic operator overloading
    friend IntN operator+ (const IntN& t_num1, const IntN& t_num2);
    friend IntN operator- (const IntN& t_num1, const IntN& t_num2);
    friend IntN operator* (const IntN& t_num1, const IntN& t_num2);

    friend IntN leftByteWise(const IntN& t_num1, const std::size_t shift);
    friend IntN rightByteWise(const IntN& t_num1, const std::size_t shift);

    // Increment/decrement operator overloading
    IntN& operator++();
    IntN  operator++(int);
    IntN& operator--();
    IntN  operator--(int);

  private:
    // Attributes
    std::list<uint8_t> m_bytes; // little endian
    constexpr static std::size_t m_defaultSize {sizeof(long long)};
    
    // Private methods
    void ResizeAndClean(const std::size_t t_size = IntN::m_defaultSize);
    bool ResizeAndTrunc(const std::size_t t_size = IntN::m_defaultSize);
    void loadNum(const long long t_num) noexcept;
    static std::pair<IntN, IntN> getOperable(const IntN& t_num1, const IntN& t_num2);

    // Comparison private methods
    static bool minusThan(const IntN& t_num1, const IntN& t_num2);
    static bool equalThan(const IntN& t_num1, const IntN& t_num2);
    static bool minusEqualThan(const IntN& t_num1, const IntN& t_num2);

    // Arithmetic private methods
    void complement2();
    static std::pair<uint8_t, uint8_t> byteAdder(const uint8_t t_byte1, const uint8_t t_byte2, const uint8_t t_carry_in);
    static std::pair<uint8_t, uint8_t> byteMultiplier(const uint8_t t_byte1, const uint8_t t_byte2, const uint8_t t_carry_in);
    static IntN addition(const IntN& t_num1, const IntN& t_num2);
    static IntN multiplication(const IntN& t_num1, const IntN& t_num2);
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

class IntNExceptionLimitReached : public IntNException {
  public:
    IntNExceptionLimitReached() : IntNException("Numerical limit has been reached") {}
};

class IntNExceptionShiftLimit : public IntNException {
  public:
    IntNExceptionShiftLimit(): IntNException("Maximal shift reached(" + std::to_string(sizeof(uint64_t) * 8) + ")") {}
};

} // namespace IntNUtils