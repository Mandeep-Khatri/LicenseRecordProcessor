# License Record Processor

This C++ program processes license records from user input.  
It stores unique license numbers and writes any duplicates to `duplicates.dat`.

## How to Use
1. Compile: `g++ main.cpp -o license_checker`
2. Run: `./license_checker`
3. Input records in the format: `<8-digit-license> <info>`
4. Type `END` to finish.

Duplicates will be saved to `duplicates.dat`.
