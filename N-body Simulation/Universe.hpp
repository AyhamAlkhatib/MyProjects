// Copyright Ayham Alkhatib 2023
#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "CelestialBody.hpp"
class Universe:public sf::Drawable {
 public:
    // ACCESSORS
    float getRadius() const {return _radius;}
    int getParticles() const {return _particles;}
    CelestialBody getCelestialBody(int index) const;
    int vectorSize() const {return _c1.size();}
    sf::Vector2f getWindowSize() const {return _windowSize;}
    // SETTERS
    void setRadius(float radius) {_radius = radius;}
    void setParticles(int particles) {_particles = particles;}
    void setWindowSize(sf::Vector2f windowSize) {_windowSize = windowSize;}
    // Operator overloading
    friend std::istream& operator>>(std::istream& in, Universe& obj);
    friend std::ostream& operator<<(std::ostream& out, const Universe& obj);
    // Public funcs
    void setCelestialBody();
    void step(double seconds);

 protected:
    void draw(sf::RenderTarget&, sf::RenderStates) const override;

 private:
    std::vector<CelestialBody> _c1;
    std::vector<CelestialBody> cOrig;
    CelestialBody _c2;
    sf::Vector2f _windowSize;
    int _particles;
    float _radius;
};
