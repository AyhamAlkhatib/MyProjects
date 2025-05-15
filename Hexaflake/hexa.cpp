// "Copyright 2023 Ayham Alkhatib"
#include <iostream>
#include <cmath>
#include "hexa.hpp"

const double DEG_TO_RAD = M_PI / 180;

void hexaflake(sf::RenderTarget& window,
    int depth, sf::Vector2f center,
    float radius) {
    sf::CircleShape hexa(radius, 6);
    // All hexagons are same size
    // If depth == 0 print the base hex
    // Else Draw the hexagons repeatedly
        if (depth == 0) {
        // Draw the base hex
        drawMiddleHex(window, center, radius);
        } else {
            // Draw the 6 hexas around the middle hex
            for (int i = 0; i < 6; i++) {
                // Increase depth by 1 so when it enters the other ()
                // It enters with the right val
                if (i == 0)
                    depth += 1;
                unsigned int thetaDeg = 0;
                thetaDeg = 60 * i;
                sf::Vector2f pt = center;
                hexa.setOrigin(radius, radius);
                pt.x +=  2 * radius * sin(thetaDeg * DEG_TO_RAD);
                pt.y +=  2 * radius * cos(thetaDeg * DEG_TO_RAD);
                hexa.setPosition(pt);
                hexa.setFillColor(sf::Color(0xfd, 0xbb, 0xbb));
                window.draw(hexa);
                    if (i == 5) {
                        drawMiddleHex(window, center, radius);
                    }
                    hexaFlakeHelper(window, depth-1, pt, radius, thetaDeg);
                    hexaFlakeHelper(window, depth-1, pt, radius, thetaDeg);
                }
        }
}

void hexaFlakeHelper(sf::RenderTarget& window,
    int depth, sf::Vector2f center,
    float radius,
    double angle) {
    int temp = (2 * pow(3, depth - 1)) - 2;
    // this get you to the center of the origin
    center.x += temp * radius * sin(angle * DEG_TO_RAD);
    center.y += temp * radius * cos(angle * DEG_TO_RAD);
    sf::CircleShape hexa(radius, 6);
    if (depth > 1) {
        for (int i = 0; i < 6; i++) {
                unsigned int thetaDeg = 0;
                sf::Vector2f pt = center;
                thetaDeg = 60 * i;
                hexa.setOrigin(radius, radius);
                pt.x +=  2 * radius * sin(thetaDeg * DEG_TO_RAD);
                pt.y +=  2 * radius * cos(thetaDeg * DEG_TO_RAD);
                hexa.setPosition(pt);
                hexa.setFillColor(sf::Color(0xfd, 0xbb, 0xbb));
                window.draw(hexa);
                    if (i == 5) {
                        drawMiddleHex(window, center, radius);
                    }
            hexaflake(window, depth - 1, center, radius);
            hexaFlakeHelper(window, depth-1, pt, radius, thetaDeg);
}
}
}
void drawMiddleHex(sf::RenderTarget& window,
    sf::Vector2f center,
    float radius) {
    sf::CircleShape hexa(radius, 6);
    hexa.setOrigin(radius, radius);
    hexa.setPosition(center);
    hexa.setFillColor(sf::Color(0xfd, 0xbb, 0xbb));
    window.draw(hexa);
}

