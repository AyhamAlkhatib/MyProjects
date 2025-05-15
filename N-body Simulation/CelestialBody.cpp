// Copyright Ayham Alkhatib 2023
#include <string>
#include <vector>
#include <cstdlib>
#include <fstream>
#include <cmath>
#include <SFML/Graphics.hpp>
#include "CelestialBody.hpp"


std::istream& operator>>(std::istream& in, CelestialBody& obj) {
    in >> obj._pos.x >> obj._pos.y >> obj._vel.x >> obj._vel.y
       >> obj.mass >> obj._fileName;
    obj.windowLocation(obj.getRadius(), obj);
    return in;
}


std::ostream& operator<<(std::ostream& out, const CelestialBody& obj) {
    out << obj.getPos().x << "  " << obj.getPos().y << "  "
        << obj.getVel().x << "  " << obj.getVel().y << "  "
        << obj.getMass() << "  " << obj.getFileName() << std::endl;
    return out;
}


void CelestialBody::draw(sf::RenderTarget& window, sf::RenderStates state) const {
    sf::Image image;
    if (!image.loadFromFile(getFileName())) {
        exit(1);
    }
    sf::Texture texture;
    texture.loadFromImage(image);
    sf::Sprite sprite;
    sprite.setTexture(texture);
    sf::Vector2f particleLoc(_windowSize);
    // Getting the center of the universe
    particleLoc.x /= 2;
    particleLoc.y /= 2;
    // Adding the particles so they can be at the specified position
    particleLoc.x += getNewP().x;
    particleLoc.y += getNewP().y;
    sprite.setPosition(particleLoc);
    window.draw(sprite, state);
}


void CelestialBody::windowLocation(float radius, CelestialBody &c1) {
    // Getting window size
    sf::Vector2f tempv = c1.getWindowSize();
    // Dividing half of the window to 1/2 in order to get
    // The center (0,0) the universe.
    tempv.x /= 2;
    tempv.y /= 2;
    // Dividing center of the window by the radius
    tempv.x = (tempv.x) / c1._radius;
    tempv.y = (tempv.y) / c1._radius;
    // Real distance from center to particle
    sf::Vector2f tempv1(c1.getPos());
    // Multiplying the distance to the result we got above
    tempv.x *= tempv1.x;
    tempv.y *= tempv1.y;
    tempv.y *= -1;

    // Storing the position so it can appear in our original window
    c1.setNewP(tempv);
}

CelestialBody& CelestialBody::operator=(const CelestialBody& obj) {
    this->_numParticles = obj.getNumParticles();
    this->_pos = obj.getPos();
    this->_vel = obj.getVel();
    this->_newPos = obj.getNewP();
    this->mass = obj.getMass();
    this->_fileName = obj.getFileName();
    this->_windowSize = obj.getWindowSize();
    this->_radius = obj.getRadius();
    return *this;
}

void CelestialBody::calculate(const CelestialBody& _c2) {
    float distance = sqrt(pow(this->_pos.x - _c2.getPos().x, 2) +
    pow(this->_pos.y - _c2.getPos().y, 2));
    float force = (this->getMass()) / pow(distance , 2);
    force *= _c2.getMass();
    force *= 6.6742E-11;
    _netForce.x += force * ((_c2.getPos().x - _pos.x) / distance);
    _netForce.y += force * ((_c2.getPos().y - _pos.y) / distance);
}
void CelestialBody::newVelPos(double seconds) {
    _acceleration.x = _netForce.x / mass;
    _acceleration.y = _netForce.y / mass;
    _vel.x = (_vel.x + seconds * _acceleration.x);
    _vel.y = (_vel.y + seconds * _acceleration.y);
    _pos.x = _pos.x + seconds * _vel.x;
    _pos.y = _pos.y + seconds * _vel.y;
    windowLocation(_radius, *this);
    _netForce.x = 0;
    _netForce.y = 0;
    // Change the co-ors to the window location
}
