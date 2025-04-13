# variable-length-number-cpp
## Variable length number for cpp, using little endian notation
Trying to use modern c++ programing  
The actual limit size is of 18.446.744.073.709.551.615 bytes (or your memory)  
  
Special member functions  
- Default constructor
- Copy constructor
- Move constructor
- Copy assigment operator
- Move assigment operator
- Destructor  
  
Compile command  
g++ -I lib/IntN/ lib/IntN/IntN.cpp test/test.cpp -o test.out  

/**
 * Creator: AnormalDog
 * License: MIT
 * 
 * Implementation file, source code of the class IntN, represents
 *   a number with variable size
 */