// Copyright Ayham Alkhatib 2023
#include <iostream>
#include <fstream>
#include <string>
#include "Universe.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

int main(int argc, char *argv[]) {
    double totalTime = atof(argv[1]);
    double dTime = atof(argv[2]);
    sf::Music music;
    if (!music.openFromFile("2001.wav"))
        throw std::invalid_argument("Can't open music file.");
    music.play();
    sf::Vector2f windowSize(1000, 800);
    sf::RenderWindow window(sf::VideoMode(windowSize.x, windowSize.y)
    , "Solar system !");
    Universe uni;
    uni.setWindowSize(windowSize);
    std::cin >> uni;
    int dt = 0;
    sf::Clock clock;
    std::string timeStr;
    int lsec = 0;
    int seconds = 0;
    int rsec = 0;
    int lmin = 0;
    int rmin = 0;
    int minutes = 0;
    sf::Font font;
    font.loadFromFile("Roboto-Regular.ttf");
    while (window.isOpen()) {
        if (dt >= totalTime) {
            break;
        }
        sf::Time x =  clock.getElapsedTime();
        rsec = x.asSeconds();
        if (rsec == 10) {
            clock.restart();
            lsec += 1;
            seconds += 10;
            if (seconds == 60) {
                rmin += 1;
                minutes += 1;
                lsec = 0;
                seconds = 0;
                if (minutes == 10) {
                    lmin += 1;
                    rmin = 0;
                }
            }
        }
        timeStr = std::to_string(lmin) + std::to_string(rmin) + ":" +
        std::to_string(lsec) + std::to_string(rsec);
        sf::Text min(timeStr, font);
        min.setFillColor(sf::Color::White);
        min.setPosition(20, 20);
        uni.step(dTime);
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
            window.draw(min);
            window.draw(uni);
            window.display();
            window.clear();
            dt += dTime;
        }
        std::cout << uni;
    return 0;
}

