// "Copyright 2023 Ayham Alkhatib"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include "RandWriter.hpp"
int main(int argc, char* argv[]) {
    int k = atoi(argv[1]), l = atoi(argv[2]);
    std::string str1;
    std::string str2;
    std::string gen;
    while (std::getline(std::cin, str1)) {
        str2 += str1;
        str2 += "\n";
    }
    str2.pop_back();
    for (int i = 0; i < k; i++) {
        gen += str2[i];
    }
    RandWriter ex(str2, k);
    std::cout << ex.generate(gen, l) << std::endl;
    return 0;
}
