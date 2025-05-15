// "Copyright 2023 Ayham Alkhatib"
#pragma once
#include <SFML/Graphics.hpp>

void hexaflake(sf::RenderTarget& window, int depth, sf::Vector2f center, float radius);
void hexaFlakeHelper(sf::RenderTarget& window,
    int depth,
    sf::Vector2f center,
    float radius,
    double angle);
void drawMiddleHex(sf::RenderTarget& window, sf::Vector2f center, float radius);

