// Copyright Ayham Alkhatib 2023
#pragma once
#include <string>
#include "Matrix.hpp"
#include <SFML/Graphics.hpp>
const unsigned int TILE_SIZE = 64;
typedef enum {Up, Down, Left, Right} Direction;
typedef enum {Reset} Restart;
class Sokoban:public sf::Drawable {
 public:
    // Accessors
    int height() const {return _height;}
    int width() const {return _width;}
    sf::Vector2u getWindowSize() const {return _windowSize;}
    std::string getDir() const {return _dir;}
    // Mutators
    void setWindowSize(sf::Vector2u windowSize) {_windowSize = windowSize;}
    int isWon() const;
    void blockData();
    // Move player data
    void movePlayer(Direction dir);
    void restartGame(Restart res);
    void checkWall(std::string dir);
    void pushBox(std::string dir);
    void storageBox(std::string dir);
    void storagePlayer(std::string dir);
    void storageDraw(std::string dir);
    bool isAtStorage(sf::Vector2i playerPos);
    bool isOutWindowParam(std::string dir);
    bool playerBoxPar(std::string dir);
    void setDir(std::string dir) {_dir = dir;}
    // Friend ()'s
    friend std::istream& operator>>(std::istream& in, Sokoban&);
    //void freeMemory();

 protected:
void draw(sf::RenderTarget&, sf::RenderStates) const override;

 private:
    int _height;
    int _width;
    Matrix matrix;
    std::vector<sf::Vector2i> _storagePos;
    std::vector<sf::Vector2i> _boxPos;
    sf::Vector2i _playerPos;
    sf::Vector2i _blockLength;
    sf::Vector2u _windowSize;
    Matrix _origMatrix;
    std::string _dir;
    sf::Texture _wall;
    sf::Texture _box;
    sf::Texture _empty;
    sf::Texture _storage;
    sf::Texture _playerFront;
    sf::Texture _playerBack;
    sf::Texture _playerRight;
    sf::Texture _playerLeft;
};