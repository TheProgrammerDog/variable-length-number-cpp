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
    inline std::size_t get_size() const noexcept {return m_bytes.size();}
    // Getters (return the number in certain format/base)
    std::string get_hex() const;

    void minimize(); // remove all empty bytes, letting the minimal size

  private:
    // Atributes
    std::vector<std::byte> m_bytes; // little endian
    bool m_sign {0};

    // Private methods
    bool scale_and_hold(unsigned long long t_size); // Scale and try to save old state
    void scale_and_clean(unsigned long long t_size = 1); // Scale and turns all byte to 0

};