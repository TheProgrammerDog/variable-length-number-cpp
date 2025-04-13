/**
 * Creator: AnormalDog
 * License: MIT
 * 
 * Header file, interface of the class IntN, represents a number with
 *   variable size
 */

#pragma once

#include <exception>
#include <cstddef>
#include <string>
#include <list>

class IntN {
  public:
    // Constructor
    IntN();
    IntN(long long t_number);

    // Special methods
    IntN(const IntN& t_IntN) = default;
    IntN(IntN&& t_IntN) = default;
    IntN& operator=(const IntN& t_IntN) = default;
    ~IntN() = default;

    // Getters
    inline std::size_t size() const noexcept {return m_bytes.size();}
    std::string get_hex() const;

    // Comparison operator overloading
    friend bool operator< (const IntN& t_num1, const IntN& t_num2) noexcept;
    friend bool operator==(const IntN& t_num1, const IntN& t_num2) noexcept;
    friend bool operator> (const IntN& t_num1, const IntN& t_num2) noexcept;
    friend bool operator<=(const IntN& t_num1, const IntN& t_num2) noexcept;
    friend bool operator>=(const IntN& t_num1, const IntN& t_num2) noexcept;
    friend bool operator!=(const IntN& t_num1, const IntN& t_num2) noexcept;

    // Arithmetic operator overloading
    friend IntN operator+ (const IntN& t_num1, const IntN& t_num2);
    friend IntN operator- (const IntN& t_num1, const IntN& t_num2);
    IntN& operator++();
    IntN operator++ (int);

  private:
    // Atributes
    std::list<std::byte> m_bytes; // little endian
    bool m_sign {false};

    // Private methods - size related
    inline void resizeAndClean(unsigned long long t_num = 1); // Resize and clean the list
    inline bool resizeAndTrunc(unsigned long long t_num = 1); // Resize and Trunc/keep the data
    void minimize(); // Minimize the bytes, discarting zero bytes without value

    inline static void makeOperable(IntN& t_num1, IntN& t_num2);
    // Private methods - logical related
    static bool minusThan(const IntN& t_num1, const IntN& t_num2);
    static bool equalThan(const IntN& t_num1, const IntN& t_num2);
    // Private methods - arithmetic related
    static IntN addition(const IntN& t_num1, const IntN& t_num2);
    inline static std::pair<std::byte, std::byte> byteAdder(const std::byte& t_num1, const std::byte& t_num2, const std::byte& t_carryIn);
    static IntN complement2(const IntN& t_num);
    inline bool resizeAndTruncComplement(unsigned long long t_num = 1);

};

namespace IntNUtils {

class IntNException : public std::exception {
  public:
    IntNException(const std::string& t_message) : m_errorMessage(t_message) {}
    const char* what() const noexcept override {return m_errorMessage.c_str();}
  private:
    std::string m_errorMessage;
};

class IntNExceptionMismatch : public IntNException {
  public:
    IntNExceptionMismatch() : IntNException("two number are trying to operate with different sizes") {}
};

} // namespace

// Inline functions
void IntN::resizeAndClean(unsigned long long t_num) {
  m_bytes.clear();
  m_bytes.resize(t_num, std::byte{0});
}

bool IntN::resizeAndTrunc(unsigned long long t_num) {
  bool fitted = (t_num >= m_bytes.size()) ? true : false;
  m_bytes.resize(t_num, std::byte{0});
  return fitted;
}

void IntN::makeOperable(IntN& t_num1, IntN& t_num2) {
  if (t_num1.size() < t_num2.size()) t_num1.resizeAndTrunc(t_num2.size());
  else if (t_num1.size() > t_num2.size()) t_num2.resizeAndTrunc(t_num1.size());
}

std::pair<std::byte, std::byte> IntN::byteAdder(const std::byte& t_num1, const std::byte& t_num2, const std::byte& t_carryIn) {
  unsigned short addition = 
    std::to_integer<unsigned short>(t_num1) + 
    std::to_integer<unsigned short>(t_num2) + 
    std::to_integer<unsigned short>(t_carryIn);
  if (addition > 255) {
    std::byte add {static_cast<unsigned char>(addition - 256)};
    std::byte carry {static_cast<unsigned char>(1)};
    return std::make_pair(add, carry);
  }

  std::byte add {static_cast<unsigned char>(addition)};
  std::byte carry {static_cast<unsigned char>(0)};
  return std::make_pair(add, carry);
}

bool IntN::resizeAndTruncComplement(unsigned long long t_num = 1) {
  bool fitted = (t_num >= m_bytes.size()) ? true : false;
  m_bytes.resize(t_num, std::byte{255});
  return fitted;
}