// "Copyright 2023 Ayham Alkhatib"
#pragma once
#include <string>
#include <unordered_map>
#include <random>
#include <vector>
#include <algorithm>
#include <iostream>
#include <exception>
#include <chrono>
class RandWriter {
 public:
    RandWriter(std::string text, int k);
    int orderK() const;
    int textSize() const { return static_cast<int>(_text.size()); }
    int kgramSize(std::string kgram) const { return static_cast<int>(kgram.size()); }
    int freq(std::string kgram) const;
    int freq(std::string kgram, char c) const;
    char kRand(std::string kgram);
    std::string generate(std::string kgram, int L);

 private:
    std::string _text;
    int _orderK;
    std::unordered_map<std::string, std::unordered_map<char, int>> stringNumOccurance;
    std::vector<char> randGenerator;
};
