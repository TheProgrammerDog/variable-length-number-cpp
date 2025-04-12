/**
 * Creator: AnormalDog
 * License: MIT
 * 
 * Header file, interface of the class IntN,  represents a number with 
 *   variable size
 */

#pragma once

#include <cstddef>
#include <vector>
#include <string>

class IntN {
  public:
    // Constructors
    IntN();
    IntN(long long t_num);
    // Special methods
    IntN(const IntN& t_IntN) = default;
    IntN(IntN&& t_IntN) = default;
    IntN& operator=(const IntN& t_IntN) = default;
    ~IntN() = default;

    // size of the (in bytes) of the number
    inline std::size_t size() const noexcept {return m_bytes.size();}
    // Getters (return the number in certain format/base)
    std::string get_hex() const;

    // Operator overloading
    IntN friend operator+ (const IntN& t_num1, const IntN& t_num2);

    // comparison operators
    bool friend operator< (const IntN& t_num1, const IntN& t_num2);
    bool friend operator==(const IntN& t_num1, const IntN& t_num2);
    bool friend operator!=(const IntN& t_num1, const IntN& t_num2);
    bool friend operator<=(const IntN& t_num1, const IntN& t_num2);
    bool friend operator>=(const IntN& t_num1, const IntN& t_num2);
    bool friend operator> (const IntN& t_num1, const IntN& t_num2);

  private:
    // Atributes
    std::vector<std::byte> m_bytes; // little endian
    bool m_sign {0};

    // Private general methods
    bool scale_and_hold(unsigned long long t_size); // Scale and try to save old state
    void scale_and_clean(unsigned long long t_size = 1); // Scale and turns all byte to 0
    void minimize(); // remove all empty bytes, letting the minimal size
    friend void make_operable(IntN& t_num1, IntN& t_num2); // convert two numbers into the same size

    // Private method, used as comparitions, suppose nums are operable
    bool friend minus_than(const IntN& t_num1, const IntN& t_num2);
    bool friend equal_than(const IntN& t_num1, const IntN& t_num2);
};