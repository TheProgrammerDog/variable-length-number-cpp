/**
 * Creator: AnormalDog
 * License: MIT
 * 
 * Header file, interface of the class IntN, represents a number with
 *   variable size
 */

#pragma once

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

  private:
    // Atributes
    std::list<std::byte> m_bytes; // little endian
    bool m_sign {false};

    // Private methods
    inline void resizeAndClean(unsigned long long t_num = 1); // Resize and clean the list
    inline bool resizeAndTrunc(unsigned long long t_num = 1); // Resize and Trunc/keep the data
    void minimize(); // Minimize the bytes, discarting zero bytes without value

    static bool minus_than(const IntN& t_num1, const IntN& t_num2);
    static bool equal_than(const IntN& t_num1, const IntN& t_num2);
    inline static void make_operable(IntN& t_num1, IntN& t_num2);

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

void IntN::make_operable(IntN& t_num1, IntN& t_num2) {
  if (t_num1.size() < t_num2.size()) t_num1.resizeAndTrunc(t_num2.size());
  else if (t_num1.size() > t_num2.size()) t_num2.resizeAndTrunc(t_num1.size());
}