// "Copyright 2023 Ayham Alkhatib"
#include "RandWriter.hpp"
RandWriter::RandWriter(std::string text, int k) : _text(text), _orderK(k) {
    if (k < 0 || k > textSize()) {
        throw std::invalid_argument("Weird k value.");
    }
    std::unordered_map<std::string, char> stringNumOccurance2;
    std::unordered_map<std::string, char> stringNumOccurance1;
    char letter;
    if (_orderK == 0) {
        // Go through the whole string and storing each character by itself
        for (int i = 0; i < textSize(); i++) {
            std::string kStr;
            char ch = text[i];
            kStr = text[i];
            stringNumOccurance1[kStr] = 1;
            auto it2 = stringNumOccurance1.begin();
            bool equality = false;
            for (auto it = stringNumOccurance2.begin(); it != stringNumOccurance2.end(); ++it) {
                if ((it->first == it2->first) && (it->second == it2->second)) {
                    equality = true;
                }
            }
            if (!equality) {
                stringNumOccurance[kStr][ch] = 1;
            } else {
                stringNumOccurance[kStr][ch] += 1;
            }
            // pushing back new value
            stringNumOccurance2[kStr] = 1;
            // clearing this map because I only need one key in it
            stringNumOccurance1.clear();
        }
    } else {
        for (int i = 0; i < textSize(); i++) {
            std::string kStr;
            if ((i + _orderK + 1) <= textSize()) {
                for (int j = i; j < (k + i); j++) {
                    kStr += text[j];
                    letter = text[j + 1];
                }
            } else {
                int front = 0;
                for (int j = i; j < (k + i); j++) {
                    if ((j) < textSize()) {
                        kStr += text[j];
                        if ((j + 1) >= textSize())
                            letter = text[0];
                        else
                            letter = text[j + 1];
                    } else {
                        kStr += text[front];
                        letter = text[front + 1];
                        front++;
                    }
                }
            }
            // One map I push before comparison of hte other map
            stringNumOccurance1[kStr] = 1;
            auto it2 = stringNumOccurance1.begin();
            bool equality = false;
            // Going through the numOccurance, if it is not there then we insert a new one
            for (auto it = stringNumOccurance2.begin(); it != stringNumOccurance2.end(); ++it) {
                if ((it->first == it2->first) && (it->second == it2->second)) {
                    equality = true;
                }
            }
            if (!equality) {
                stringNumOccurance[kStr][letter] = 1;
            } else {
                stringNumOccurance[kStr][letter] += 1;
            }
            // pushing back new value
            stringNumOccurance2[kStr] = 1;
            // clearing this map because I only need one key in it
            stringNumOccurance1.clear();
        }
    }
}
int RandWriter::orderK() const {
    return _orderK;
}

int RandWriter::freq(std::string kgram) const {
    int occurance = 0;
    if (_orderK != kgramSize(kgram)) {
        throw std::invalid_argument("Order and string length not equal");
    } else if (_orderK == 0) {
        return textSize();
    } else {
        for (auto itr1 = stringNumOccurance.begin(); itr1 != stringNumOccurance.end(); itr1++) {
            if (itr1->first == kgram) {
                for (auto itr2 = itr1->second.begin(); itr2 != itr1->second.end(); itr2++) {
                    occurance += itr2->second;
                }
            }
        }
    }
    return occurance;
}

int RandWriter::freq(std::string kgram, char c) const {
    int occurance = 0;
    if (_orderK != kgramSize(kgram)) {
        throw std::invalid_argument("Order and string length not equal");
    } else if (_orderK == 0) {
        for (auto itr1 = stringNumOccurance.begin(); itr1 != stringNumOccurance.end(); itr1++) {
            for (auto itr2 = itr1->second.begin(); itr2 != itr1->second.end(); itr2++) {
                if (itr2->first == c) {
                    occurance += itr2->second;
                }
            }
        }
    } else {
        for (auto itr1 = stringNumOccurance.begin(); itr1 != stringNumOccurance.end(); itr1++) {
            if (itr1->first == kgram) {
                for (auto itr2 = itr1->second.begin(); itr2 != itr1->second.end(); itr2++) {
                    if (itr2->first == c) {
                        occurance += itr2->second;
                    }
                }
            }
        }
    }
    return occurance;
}

char RandWriter::kRand(std::string kgram) {
    randGenerator.clear();
    auto p = find_if(stringNumOccurance.begin(), stringNumOccurance.end(), [kgram] (auto& elem) {
     return elem.first == kgram;
    });
    if (_orderK != kgramSize(kgram) || p == stringNumOccurance.end()) {
        throw std::invalid_argument("Order and string length not equal or no such kgram exist!");
    } else if (_orderK == 0 && kgram != "") {
        throw std::invalid_argument("Order and string length not equal or no such kgram exist!");
    } else if (_orderK == 0) {
        for (auto itr1 = stringNumOccurance.begin(); itr1 != stringNumOccurance.end(); itr1++) {
                for (auto itr2 = itr1->second.begin(); itr2 != itr1->second.end(); itr2++) {
                    for (int i = 0; i < itr2->second; i++) {
                    randGenerator.push_back(itr2->first);
                    }
                }
        }
    } else {
        for (auto itr1 = stringNumOccurance.begin(); itr1 != stringNumOccurance.end(); itr1++) {
            if (itr1->first == kgram) {
                for (auto itr2 = itr1->second.begin(); itr2 != itr1->second.end(); itr2++) {
                    for (int i = 0; i < itr2->second; i++) {
                    randGenerator.push_back(itr2->first);
                    }
                }
            }
        }
    }
    // Getting a random char
    std::minstd_rand0 gen(std::chrono::system_clock::now().time_since_epoch().count());
    std::shuffle(randGenerator.begin(), randGenerator.end(), gen);
    int randomIndex = random() % randGenerator.size();
    return randGenerator.at(randomIndex);
}
// Throw an exception when kgram isn't in the original text
std::string RandWriter::generate(std::string kgram, int L) {
    auto p = find_if(stringNumOccurance.begin(), stringNumOccurance.end(), [kgram] (auto& elem) {
     return elem.first == kgram;
    });
    std::string randText;
    randText += kgram;
    if (_orderK != kgramSize(kgram) || p == stringNumOccurance.end()) {
        throw std::invalid_argument("Order and string length not equal or kgram not in text");
    } else if (_orderK == 0) {
        for (int i = 0; i < L; i++) {
            randText += kRand("");
        }
    } else {
        for (int i = 0; i < (L - _orderK); i++) {
            std::string par;
            // Taking the last k letters to generate the next letter
            for (int j = i; j < (_orderK + i); j++) {
                par += randText[j];
            }
        randText += kRand(par);
        }
    }
    return randText;
}
