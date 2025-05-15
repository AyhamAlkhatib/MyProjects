// "Copyright 2023 Ayham Alkhatib"
#pragma once
#include <iostream>
#include <vector>
#include <string>
class FibLFSR {
 public:
    explicit FibLFSR(std::string seed);
    // Simulate one step and return the new bit as 0 or 1
    int step();
    // Simulate k steps and return a k-bit integer
    int generate(int k);
    void vecToStr1();
    void vecToStr2();
    // Accessor
    std::string getStr() const { return strOfBits; }
    ~FibLFSR();
 private:
    std::vector<int> result;
    std::vector<int> nums;
    std::string strOfBits;
};
std::ostream& operator<<(std::ostream& out, const FibLFSR& lfsr);
