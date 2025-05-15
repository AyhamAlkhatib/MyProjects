// "Copyright 2023 Ayham Alkhatib"
#pragma once
#include <string>
#include <vector>
#include <algorithm>
typedef enum {Diag, Down, Right} Direction;
class EDistance {
 public:
    EDistance(std::string str1, std::string str2);
    static int penalty(char a, char b);
    static int min3(int a, int b, int c);
    int optDistance();
    std::string alignment();
 private:
    std::string _s1;
    std::string _s2;
    size_t indexAt(size_t x, size_t y) {
        return y + x * (_s2.size() + 1);
    }

    std::vector<int> matrix;
    std::vector<Direction> backTrace;
};
