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
g++ -I include/ src/int_n.cpp test/main.cpp -o test.out