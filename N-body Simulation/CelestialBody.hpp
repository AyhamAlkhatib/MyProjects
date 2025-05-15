// Copyright Ayham Alkhatib 2023
#pragma once

#include <iostream>

#include <string>

#include <SFML/Graphics.hpp>
class CelestialBody: public sf::Drawable {
 public:
    // Accessors
    int getNumParticles() const {return _numParticles;}
    sf::Vector2f getPos() const {return _pos;}
    sf::Vector2f getVel() const {return _vel;}
    float getMass() const {return mass;}
    std::string getFileName()const {return _fileName;}
    float getRadius() const {return _radius;}
    sf::Vector2f getWindowSize() const {return _windowSize;}
    sf::Vector2f getNewP() const {return _newPos;}
    sf::Vector2f getNetfore() const {return _netForce;}
    sf::Vector2f getAcceleration() const {return _acceleration;}
    // Setters
    void setNewP(sf::Vector2f newPos) {_newPos = newPos;}
    void setPos(sf::Vector2f pos) {_pos = pos;}
    void setRadius(float radius) {_radius = radius;}
    void setVel(sf::Vector2f vel) {_vel = vel;}
    void setMass(float _mass) {mass = _mass;}
    void setFileName(std::string fileName) {_fileName = fileName;}
    void setAcceleration(sf::Vector2f acceleration) { _acceleration = acceleration;}
    void setNetForce(sf::Vector2f netForce) {_netForce = netForce;}
    // Number of particles
    void setPlanets(int numParticles) {_numParticles = numParticles;}
    void setWindowSize(sf::Vector2f windowSize) {_windowSize = windowSize;}
    // Member functions
    void windowLocation(float radius, CelestialBody &c1);
    void calculate(const CelestialBody& _c2);
    // Operator overloading
    friend std::istream& operator>>(std::istream& in, CelestialBody& obj);
    friend std::ostream& operator<<(std::ostream& out, const CelestialBody& obj);
    CelestialBody& operator=(const CelestialBody& obj);
    void newVelPos(double seconds);

 protected:
    void draw(sf::RenderTarget&, sf::RenderStates) const override;

 private:
  int _numParticles;
  sf::Vector2f _pos;
  sf::Vector2f _vel;
  sf::Vector2f _newPos;
  float mass;
  std::string _fileName;
  sf::Vector2f _windowSize;
  float _radius;
  sf::Vector2f _netForce;
  sf::Vector2f _acceleration;
};
