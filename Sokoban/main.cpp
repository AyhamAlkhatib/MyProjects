// Copyright Ayham Alkhatib 2023
#include <iostream>
#include <string>
#include <fstream>
#include "Sokoban.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
int main(int argc, char*argv[]) {
    sf::Font font;
    font.loadFromFile("Roboto-Regular.ttf");
    std::fstream file_obj;
    file_obj.open(argv[1]);
    Sokoban game;
    file_obj >> game;
    sf::RenderWindow window(sf::VideoMode(game.getWindowSize().x,
    game.getWindowSize().y), "Sokoban Game");
    sf::Clock clock;
    std::string timeStr;
    int lsec = 0;
    int seconds = 0;
    int rsec = 0;
    int lmin = 0;
    int rmin = 0;
    int minutes = 0;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed ) {
                window.close();
            } else if ((event.type == sf::Event::KeyPressed && game.isWon() == 0)) {
                switch(event.key.code) {
                    case sf::Keyboard:: W:
                        game.setDir("Up");
                        game.movePlayer(Up);
                        break;
                    case sf::Keyboard:: S:
                        game.setDir("Down");
                        game.movePlayer(Down);
                        break;
                    case sf::Keyboard:: A:
                        game.setDir("Left");
                        game.movePlayer(Left);
                        break;
                    case sf::Keyboard:: D:
                        game.setDir("Right");
                        game.movePlayer(Right);
                        break;
                    case sf::Keyboard:: R:
                        game.restartGame(Reset);
                        break;
                    default:
                        throw std::invalid_argument("Wrong button!");
                        break;
                }
        }
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
        window.clear();
        window.draw(game);
        window.draw(min);
        window.display();
    }
    //game.freeMemory();
    return 0;
}