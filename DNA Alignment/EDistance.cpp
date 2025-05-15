// "Copyright 2023 Ayham Alkhatib"
#include "EDistance.hpp"
EDistance::EDistance(std::string str1, std::string str2):
_s1(str1), _s2(str2) {
    for (size_t i = 0; i < ((_s1.size() + 1) * (_s2.size() + 1)); i++) {
        matrix.push_back(0);
        backTrace.push_back(Right);
    }
    int x = 0;
    for (int i = _s1.size(); i >= 0; i--) {
        matrix[indexAt(i, _s2.size())] = x * 2;
        x++;
    }
    x = 0;
    for (int j = _s2.size(); j >= 0; j--) {
        matrix[indexAt(_s1.size(), j)] = x * 2;
        x++;
    }
}
int EDistance::penalty(char a, char b) {
    if (a == b)
        return 0;
    else
        return 1;
}

int EDistance::min3(int a, int b, int c) {
    int lowest = std::min(a, b);
    lowest = std::min(lowest, c);
    return lowest;
}

// TACAGTTACC
int EDistance::optDistance() {
    for (int i = (_s1.size() - 1); i >= 0; i--) {
        for (int j = (_s2.size() - 1); j >= 0; j--) {
            int gapLS = matrix[indexAt(i + 1, j)] + 2;
            int gapRS = matrix[indexAt(i, j + 1)] + 2;
            int match;
            if (penalty(_s1[i], _s2[j]) == 0)
                match = matrix[indexAt(i + 1, j + 1)];
            else
                match = matrix[indexAt(i + 1, j + 1)] + 1;
            matrix[indexAt(i, j)] = min3(match, gapLS, gapRS);
            if (match == matrix[indexAt(i, j)])
                backTrace[indexAt(i, j)] = Diag;
            else if (gapLS == matrix[indexAt(i, j)])
                backTrace[indexAt(i, j)] = Down;
            else
                backTrace[indexAt(i, j)] = Right;
        }
    }
    return matrix[indexAt(0, 0)];
}

// Traversing from top to bottom, legt to right
std::string EDistance::alignment() {
    long unsigned int i = 0;
    long unsigned int j = 0;
    int x = 2;
    char ch = '-';
    std::string sol;
    while (i < _s1.size() && j < _s2.size()) {
        switch (backTrace[indexAt(i, j)]) {
        case Down:
            if (matrix[indexAt(i, j)] == (matrix[indexAt(i + 1, j)] + 2)) {
                sol += _s1[i];
                sol += ' ';
                sol += ch;
                sol += ' ';
                sol += std::to_string(x);
                i++;
            }
            break;
        case Right:
            if (matrix[indexAt(i, j)] == (matrix[indexAt(i, j + 1)] + 2)) {
                sol += ch;
                sol += ' ';
                sol += _s2[j];
                sol += ' ';
                sol += std::to_string(x);
                j++;
            }
            break;
        case Diag:
            sol += _s1[i];
            sol += ' ';
            sol += _s2[j];
            sol += ' ';
            int x = penalty(_s1[i], _s2[j]);
            sol += std::to_string(x);
            i++;
            j++;
            break;
        }
        sol += '\n';
    }
    return sol;
}
