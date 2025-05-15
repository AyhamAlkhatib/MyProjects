// "Copyright 2023 Ayham Alkhatib"
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "PhotoMagic.hpp"
void PhotoMagic::transform(sf::Image& image, FibLFSR* obj) {
    // p is a pixelimage.getPixel(x, y);
    sf::Color p;
    sf::Color result;
    for (unsigned int x = 0; x< image.getSize().x; x++) {
        for (unsigned int y = 0; y < image.getSize().y; y++) {
            // Extract color from the pixel
            p = image.getPixel(x, y);
            // XOR them by calling generate(8) func on obj
            // Store the result in a new color var
            result.r = p.r ^ obj->generate(8);
            result.g = p.g ^ obj->generate(8);
            result.b = p.b ^ obj->generate(8);
            image.setPixel(x, y, result);
        }
    }
}


