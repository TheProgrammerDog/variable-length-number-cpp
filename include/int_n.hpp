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

class IntN {
  public:
    // Constructors
    IntN(long long t_num);
    IntN(unsigned long long t_num);

  private:
    // Atributes
    std::vector<std::byte> m_bytes;
    bool m_sign {0};

    // Private methods
    void scale_size(unsigned long long t_size = 0);

};