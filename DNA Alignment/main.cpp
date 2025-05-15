// "Copyright 2023 Ayham Alkhatib"
#include <iostream>
#include <fstream>
#include "EDistance.hpp"
#include <SFML/System.hpp>

int main(int argc, char *argv[]) {
    sf::Clock clock;
    std::string str1, str2;
    std::cin >> str1 >> str2;
    EDistance dis(str1, str2);
    std::cout << "Edit distance = " << dis.optDistance() << std::endl;
    std::cout << dis.alignment();
    sf:: Time t = clock.getElapsedTime();
    std::cout << "Execution time is " << t.asSeconds() <<
    " seconds" << std::endl;
    return 0;
}
