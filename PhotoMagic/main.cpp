// "Copyright 2023 Ayham Alkhatib"
#include <string>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "PhotoMagic.hpp"


int main(int argc, char*argv[]) {
    sf::Image image1;
    sf::Image image2;
    std::string inFile = argv[1];  // Input file cat.jpg
    std::string outFile = argv[2];  // Output file
    std::string seed = argv[3];
    FibLFSR obj(seed);
    if (!image1.loadFromFile(inFile))
        return -1;
    if (!image2.loadFromFile(inFile))
        return -1;
    PhotoMagic::transform(image2, &obj);
    sf::Vector2u size1 = image1.getSize();
    sf::RenderWindow window1(sf::VideoMode(size1.x, size1.y), "Meow");
    sf::Vector2u size2 = image2.getSize();
    sf::RenderWindow window2(sf::VideoMode(size2.x, size2.y), "Meow");
    sf::Texture texture1;
    sf::Texture texture2;
    texture1.loadFromImage(image1);
    texture2.loadFromImage(image2);
    sf::Sprite sprite1;
    sf::Sprite sprite2;
    sprite1.setTexture(texture1);
    sprite2.setTexture(texture2);
    while (window1.isOpen() && window2.isOpen()) {
    sf::Event event;
    while (window1.pollEvent(event)) {
    if (event.type == sf::Event::Closed)
        window1.close();
    }
    while (window2.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window2.close();
    }
    window1.clear();
    window1.draw(sprite1);
    window1.display();
    window2.clear();
    window2.draw(sprite2);
    window2.display();
    }
    // fredm: saving a PNG segfaults for me, though it does properly
    //   write the file
    if (!image2.saveToFile(outFile))
        return -1;
    return 0;
}

