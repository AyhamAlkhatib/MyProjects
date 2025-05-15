// Copyright Ayham Alkhatib 2023
#include <fstream>
#include <memory>
#include <cmath>
#include "Universe.hpp"


std::istream& operator>>(std::istream& in, Universe& obj)  {
    in >> obj._particles >> obj._radius;
    obj._c2.setWindowSize(obj._windowSize);
    obj._c2.setPlanets(obj._particles);
    obj._c2.setRadius(obj._radius);
    for (int i  = 0; i < obj._particles; i++) {
        in >> obj._c2;
        obj._c1.push_back(obj._c2);
    }
    for (int i = 0; i < obj._particles; i++) {
        obj.cOrig.push_back(obj._c1.at(i));
    }
    // Copying original celastialBody as a copy for later us
    return in;
}

std::ostream& operator<<(std::ostream& out, const Universe& obj) {
    out << obj.getParticles() << "  " << std::endl << obj.getRadius() << std::endl;
    // vectorSize() is the size of vector<celastialbody>
    for (int i = 0; i < obj.vectorSize(); i++) {
        out << obj.getCelestialBody(i);
    }
    return out;
}

void Universe::draw(sf::RenderTarget& window, sf::RenderStates state) const {
    for (int i = 0; i < _particles; i++) {
        window.draw(_c1.at(i), state);
    }
}
void Universe::setCelestialBody() {
    for (int i = 0; i < _particles; i++) {
        cOrig.at(i) = _c1.at(i);
    }
}
CelestialBody Universe::getCelestialBody(int index) const {
    CelestialBody c = _c1.at(index);
    return c;
}

void Universe::step(double seconds) {
    setCelestialBody();
    {
        std::shared_ptr<CelestialBody> x = std::make_shared<CelestialBody>();
    for (int i = 0; i < getParticles(); i++) {
        for (int j = 0; j < getParticles(); j++) {
            *x = cOrig.at(j);
            if (_c1.at(i).getPos() == x->getPos()) {
                continue;
            }
            _c1.at(i).calculate(*x);
        }
        _c1.at(i).newVelPos(seconds);
    }
    }
}
