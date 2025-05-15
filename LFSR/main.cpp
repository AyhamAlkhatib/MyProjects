// "Copyright 2023 Ayham Alkhatib"
#include <iostream>
#include "FibLFSR.hpp"
 int main(int argc, char*argv[]) {
    FibLFSR j("1011011000110110");
     j.step();
    std::cout << j << std::endl;
    std::cout << j.generate(5) << std::endl;
    return 0;
}
