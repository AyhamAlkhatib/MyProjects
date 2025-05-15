// "Copyright 2023 Ayham Alkhatib"
#include <cmath>
#include <SFML/Graphics.hpp>
#include "hexa.hpp"
int main(int argc, char*argv[]) {
    double length = atof(argv[1]);
    int  depth = atoi(argv[2]);
    int y = 0;
    if (depth > 3 && length > 500) {
        y = 3 * length;
    } else {
     y = (2 * length);
    }
    unsigned int windowSize = y;
    sf::RenderWindow window(sf::VideoMode(windowSize, windowSize), "SFML works!");
    sf::Vector2f center(windowSize / 2, windowSize / 2);
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        float radius = (length * sqrt(6)) / 3;
        int x = pow(3, depth);
        hexaflake(window, depth, center, radius / x);
        window.display();
    }

    return 0;
}
