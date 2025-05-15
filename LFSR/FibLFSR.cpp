// "Copyright 2023 Ayham Alkhatib"
#include "FibLFSR.hpp"
#include <vector>
#include <string>
#include <algorithm>
// You will Xor the 15th bit with 13th bit,
// then Xoring the resXorult to the 12th bit,
// then xoring the resXorult to the 10th bit
FibLFSR::FibLFSR(std::string seed) {
    // Vector for storing the bits
    int temp = 0;
    std::string tempStr = "";
    // Converting each char in string to int and storing it in vector nums
    for (size_t i = 0; i < seed.size(); i++) {
        tempStr = seed[i];
        temp = stoi(tempStr);
        nums.push_back(temp);
    }
    vecToStr2();
}

int FibLFSR::step() {
    // Erase the result vector so when it comes back in,
    // you don't add to already eisting vector
    result.clear();
    // Stores the resXorult of the Xors
    int resXor = 0;
    // Xor 15th and 13th bit
    resXor = nums.at(0) ^ nums.at(2);
    // Xoring the resXorult to the 12th bit
    resXor ^= nums.at(3);
    // Xoring the resXorult to the 10th bit
    resXor ^= nums.at(5);
    // Revering the vector so it's easir to know the bits more clearly
    auto itBeg = nums.begin(), itEnd = nums.end();
    std::reverse(itBeg, itEnd);
    // Pushing back the result of Xoring
    result.push_back(resXor);
    // Putting the remaining bits
    for (auto it = nums.begin(); it != (nums.end() - 1); ++it)
        result.push_back(*it);
    // Re-reversing the vector
    itBeg = result.begin(), itEnd = result.end();
    std::reverse(itBeg, itEnd);
    // Copy result to nums so when it enters function again,
    // it has the new sequence of bits
    nums = result;
    // Converting the sequence of bits to a string
    vecToStr1();
    // Returning the rightmost bit
    return nums.at(15);
}
// Converting the sequence of bits to a string
void FibLFSR::vecToStr1() {
    int temp = 0;
    strOfBits = "";
    for (size_t i = 0; i < result.size(); i++) {
        temp = result[i];
        strOfBits += std::to_string(temp);
    }
}

// Overloading the insertion operator
std::ostream &operator<<(std::ostream &out, const FibLFSR &lfsr) {
    out << lfsr.getStr();
    return out;
}

int FibLFSR::generate(int k) {
    int var = 0;
    int temp = 0;
    for (int i = 0; i < k; i++) {
        temp = step();
        var *= 2;
        var += temp;
    }
    return var;
}

void FibLFSR::vecToStr2() {
    int temp = 0;
    strOfBits = "";
    for (size_t i = 0; i < nums.size(); i++) {
        temp = nums[i];
        strOfBits += std::to_string(temp);
    }
}

FibLFSR::~FibLFSR() {
    result.clear();
    nums.clear();
}
