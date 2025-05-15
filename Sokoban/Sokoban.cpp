
// Copyright Ayham Alkhatib 2023
#include "Sokoban.hpp"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <SFML/Graphics.hpp>
std::istream& operator>>(std::istream& in, Sokoban& obj) {
    in  >> obj._height >> obj._width;
    obj.matrix.setRows(obj._height);
    obj.matrix.setColumns(obj._width);
    obj.matrix.setData();
    obj.setWindowSize({obj._width * TILE_SIZE, obj._height * TILE_SIZE});
    in >> obj.matrix;
    obj.blockData();
    obj.matrix.setSize();
    obj._origMatrix = obj.matrix;
    return in;
}

void Sokoban::movePlayer(Direction dir) {
    
    if (isOutWindowParam(_dir) == false) {
        std::cout << _playerPos.x << ", " << _playerPos.y << std::endl;
    switch(dir) {
        case Up:
            
            // If there is no wall and no box and storage,
            if ((matrix(_playerPos.x - 1, _playerPos.y) != 'A'  && matrix(_playerPos.x - 1, _playerPos.y) != '1')) {
                // If player is at storage, then the storage gets redrawn and player moves up into free space
                // considering there are no walls or boxes
                if (isAtStorage({_playerPos.x, _playerPos.y})) {
                    if (matrix(_playerPos.x - 1, _playerPos.y) != '#') {
                        matrix(_playerPos.x, _playerPos.y) = 'a';
                        std::cout << _playerPos.x << ", " << _playerPos.y << std::endl << std::endl; 
                        matrix(_playerPos.x - 1, _playerPos.y) = '@';
                        std::cout << _playerPos.x - 1 << ", " << _playerPos.y << std::endl << std::endl; 
                        _playerPos.x -= 1;
                        }
                    } else {   
                // If the player isn't in the storage, then player jus moves freely
                checkWall("Up");
            }
            std::cout << matrix << std::endl;
            } else if (matrix(_playerPos.x - 2, _playerPos.y) == 'a' && matrix(_playerPos.x - 1, _playerPos.y) == 'A') {
                storageBox("Up");
            } else if (matrix(_playerPos.x - 1, _playerPos.y) == '1' && (matrix(_playerPos.x - 2, _playerPos.y) != 'A' && matrix(_playerPos.x - 2, _playerPos.y) != '#')) {
                storagePlayer("Up");
            } else if (matrix(_playerPos.x,_playerPos.y) == '@' && isAtStorage({_playerPos.x, _playerPos.y}) && playerBoxPar("Up") == false) {
                
                storageDraw("Up");
            } else {
                if (playerBoxPar("Up") == false)
                    pushBox("Up");
            }
             std::cout << _playerPos.x << ", " << _playerPos.y << std::endl << std::endl; 
            break;
        case Down:
            if (matrix(_playerPos.x + 1, _playerPos.y) != 'A' && matrix(_playerPos.x + 1, _playerPos.y) != '1') {
                if (isAtStorage({_playerPos.x, _playerPos.y})) {
                    if (matrix(_playerPos.x + 1, _playerPos.y) != '#') {
                        matrix(_playerPos.x, _playerPos.y) = 'a';
                        matrix(_playerPos.x + 1, _playerPos.y) = '@';
                        _playerPos.x += 1;
                        } 
                        }else {
                checkWall("Down"); 
                }
            } else if(matrix(_playerPos.x + 2, _playerPos.y) == 'a' && matrix(_playerPos.x + 1, _playerPos.y) == 'A') {
                storageBox("Down");
            } else if (matrix(_playerPos.x + 1, _playerPos.y) == '1' && (matrix(_playerPos.x + 2, _playerPos.y) != 'A' && matrix(_playerPos.x + 2, _playerPos.y) != '#')) {
                storagePlayer("Down");
            } else if(matrix(_playerPos.x,_playerPos.y) == '@' && isAtStorage({_playerPos.x, _playerPos.y})  && playerBoxPar("Down") == false) {
                    storageDraw("Down");
            } else {
                if (playerBoxPar("Down") == false)
                    pushBox("Down");
            } 
            std::cout << matrix << std::endl << _playerPos.x << ", " << _playerPos.y << std::endl << std::endl; 
            break;
        case Left:
            if (matrix(_playerPos.x, _playerPos.y - 1) != 'A' && matrix(_playerPos.x, _playerPos.y - 1) != '1') {
                if (isAtStorage({_playerPos.x, _playerPos.y})) {
                    if (matrix(_playerPos.x , _playerPos.y - 1) != '#') {
                        matrix(_playerPos.x, _playerPos.y) = 'a';
                        matrix(_playerPos.x , _playerPos.y - 1) = '@';
                        _playerPos.y -= 1;
                    }
                } else {
                checkWall("Left");
                }
                
                
            } else if (matrix(_playerPos.x, _playerPos.y - 2) == 'a' && matrix(_playerPos.x, _playerPos.y - 1) == 'A') {
                storageBox("Left");
            } else if (matrix(_playerPos.x, _playerPos.y - 1) == '1' && (matrix(_playerPos.x, _playerPos.y - 2) != 'A' && matrix(_playerPos.x, _playerPos.y - 2) != '#')) {
                storagePlayer("Left");
            } else if (matrix(_playerPos.x,_playerPos.y) == '@' && isAtStorage({_playerPos.x, _playerPos.y}) && playerBoxPar("Left") == false) {
                    storageDraw("Left");
            } else { 
                if (playerBoxPar("Left") == false)
                        pushBox("Left");
            }
            std::cout << matrix << std::endl << _playerPos.x << ", " << _playerPos.y << std::endl << std::endl; 
            break;
        case Right:
            if (matrix(_playerPos.x, _playerPos.y + 1) != 'A' && matrix(_playerPos.x , _playerPos.y + 1) != '1') {
                 if (isAtStorage({_playerPos.x, _playerPos.y})) {
                    if (matrix(_playerPos.x , _playerPos.y + 1) != '#') {
                        matrix(_playerPos.x, _playerPos.y) = 'a';
                        matrix(_playerPos.x , _playerPos.y + 1) = '@';
                        _playerPos.y += 1;
                    }
                }
                else {
                    checkWall("Right");
                }
            } else if (matrix(_playerPos.x, _playerPos.y + 2) == 'a' && matrix(_playerPos.x, _playerPos.y + 1) == 'A') {
                    storageBox("Right");
            } else if(matrix(_playerPos.x, _playerPos.y + 1) == '1' && (matrix(_playerPos.x, _playerPos.y + 2) != 'A' && matrix(_playerPos.x, _playerPos.y + 2) != '#')) {
                storagePlayer("Right");
            } else if(matrix(_playerPos.x,_playerPos.y) == '@' && isAtStorage({_playerPos.x, _playerPos.y})  && playerBoxPar("Right") == false) {
                    storageDraw("Right");
            } else {
                if (playerBoxPar("Right") == false)
                    pushBox("Right");
            }
            std::cout << matrix << std::endl << _playerPos.x << ", " << _playerPos.y << std::endl << std::endl; 
            break;
    }
}

}

void Sokoban::pushBox(std::string dir) {
    int x = 0;
    if (dir == "Up") {
        if (matrix(_playerPos.x - 2, _playerPos.y ) != '#' && matrix(_playerPos.x - 2, _playerPos.y ) != 'A') {
                if (matrix(_playerPos.x - 1, _playerPos.y) == 'A') {
                    for (long unsigned int i = 0; i < _boxPos.size(); i++) {
                        if (_playerPos.x - 1 == _boxPos.at(i).x && _playerPos.y == _boxPos.at(i).y) {
                            x = i;
                        }
                    }
                    matrix(_playerPos.x , _playerPos.y) = '.';
                    std::cout << _playerPos.x << ", " << _playerPos.y << std::endl << std::endl; 
                    matrix(_playerPos.x - 2, _playerPos.y) = 'A';
                    std::cout << _playerPos.x - 2 << ", " << _playerPos.y << std::endl << std::endl; 
                    _boxPos.at(x) = {_playerPos.x - 2, _playerPos.y};
                    matrix(_playerPos.x - 1, _playerPos.y) = '@';
                    _playerPos.x -= 1;
                }
            }
    }
    x = 0;
    if (dir == "Down") {
        if (matrix(_playerPos.x + 2, _playerPos.y ) != '#' && matrix(_playerPos.x + 2, _playerPos.y ) != 'A') {
                if (matrix(_playerPos.x + 1, _playerPos.y) == 'A') {
                    for (long unsigned int i = 0; i < _boxPos.size(); i++) {
                        if (_playerPos.x + 1 == _boxPos.at(i).x && _playerPos.y == _boxPos.at(i).y) {
                            x = i;
                        }
                    }
                    matrix(_playerPos.x , _playerPos.y) = '.';
                    matrix(_playerPos.x + 2, _playerPos.y) = 'A';
                    _boxPos.at(x) = {_playerPos.x + 2, _playerPos.y};
                    matrix(_playerPos.x + 1, _playerPos.y) = '@';
                    _playerPos.x += 1;
                }
                
            }
    }
    x = 0;
    if (dir == "Left") {
        if (matrix(_playerPos.x, _playerPos.y - 2) != '#' && matrix(_playerPos.x, _playerPos.y - 2) != 'A' ) {
                if (matrix(_playerPos.x , _playerPos.y - 1) == 'A') {
                    for (long unsigned int i = 0; i < _boxPos.size(); i++) {
                        if (_playerPos.x == _boxPos.at(i).x && _playerPos.y - 1 == _boxPos.at(i).y) {
                            x = i;
                        }
                    }
                    matrix(_playerPos.x , _playerPos.y) = '.';
                    matrix(_playerPos.x , _playerPos.y - 2) = 'A';
                    _boxPos.at(x) = {_playerPos.x, _playerPos.y - 2};
                    matrix(_playerPos.x , _playerPos.y - 1) = '@';
                    _playerPos.y -= 1;
                }
            }
    }
    x = 0;
    if (dir == "Right") {
         if (matrix(_playerPos.x, _playerPos.y + 2) != '#' && matrix(_playerPos.x, _playerPos.y +2 ) != 'A') {
                if (matrix(_playerPos.x , _playerPos.y + 1) == 'A') {
                    for (long unsigned int i = 0; i < _boxPos.size(); i++) {
                        if (_playerPos.x == _boxPos.at(i).x && _playerPos.y + 1 == _boxPos.at(i).y) {
                            x = i;
                        }
                    }
                    matrix(_playerPos.x , _playerPos.y) = '.';
                    matrix(_playerPos.x , _playerPos.y + 2) = 'A';
                    _boxPos.at(x) = {_playerPos.x, _playerPos.y + 2};
                    matrix(_playerPos.x , _playerPos.y + 1) = '@';
                    _playerPos.y += 1;
                }
            }
    }
}
void Sokoban::checkWall(std::string dir) {
    if (matrix(_playerPos.x - 1, _playerPos.y) != 'A') {
        if (dir == "Up") {
            if (matrix(_playerPos.x  - 1, _playerPos.y)  != '#') {
                    matrix(_playerPos.x, _playerPos.y) = '.';
                    std::cout << _playerPos.x << ", " << _playerPos.y << std::endl << std::endl; 
                    matrix(_playerPos.x  - 1, _playerPos.y) = '@';
                    std::cout << _playerPos.x - 1 << ", " << _playerPos.y << std::endl << std::endl; 
                    _playerPos.x -= 1;
                }
        }
    }
    if (matrix(_playerPos.x + 1, _playerPos.y) != 'A') {
        if (dir == "Down") {
            if (matrix(_playerPos.x  + 1, _playerPos.y)  != '#') {
                    matrix(_playerPos.x, _playerPos.y) = '.';
                    matrix(_playerPos.x  + 1, _playerPos.y) = '@';
                    _playerPos.x += 1;
                }
        }
    }
    if (matrix(_playerPos.x, _playerPos.y - 1) != 'A') {
        if (dir == "Left") {
            if (matrix(_playerPos.x , _playerPos.y - 1)  != '#') {
                    matrix(_playerPos.x, _playerPos.y) = '.';
                    matrix(_playerPos.x , _playerPos.y - 1) = '@';
                    _playerPos.y -= 1;
                }
        }
    }
    if (matrix(_playerPos.x , _playerPos.y + 1) != 'A') {
        if (dir == "Right") {
            if (matrix(_playerPos.x, _playerPos.y + 1)  != '#') {
                    matrix(_playerPos.x, _playerPos.y) = '.';
                    matrix(_playerPos.x , _playerPos.y + 1) = '@';
                    _playerPos.y += 1;
                }
        }
}
}

void Sokoban::storageBox(std::string dir) {
    int x = 0;
    if (dir == "Up") {
        for (long unsigned int i = 0; i < _boxPos.size(); i++) {
            if (_playerPos.x - 1 == _boxPos.at(i).x && _playerPos.y == _boxPos.at(i).y) {
                x = i;
                }
                }
        _boxPos.at(x) = {_playerPos.x - 2, _playerPos.y};
        matrix(_playerPos.x, _playerPos.y) = '.'; 
        matrix(_playerPos.x - 1, _playerPos.y) = '@';
        std::cout << _playerPos.x - 1 << ", " << _playerPos.y << std::endl << std::endl; 
        matrix(_playerPos.x - 2, _playerPos.y) = '1';
        std::cout << _playerPos.x - 2 << ", " << _playerPos.y << std::endl << std::endl; 
        _playerPos.x -= 1;
    } else if (dir == "Down") {
        x = 0;
        for (long unsigned int i = 0; i < _boxPos.size(); i++) {
            if (_playerPos.x + 1 == _boxPos.at(i).x && _playerPos.y == _boxPos.at(i).y) {
                x = i;
                }
            }
        _boxPos.at(x) = {_playerPos.x + 2, _playerPos.y};    
        matrix(_playerPos.x, _playerPos.y) = '.'; 
        matrix(_playerPos.x + 1, _playerPos.y) = '@';
        matrix(_playerPos.x + 2, _playerPos.y) = '1';
        _playerPos.x += 1;
    } else if (dir == "Left") {
        x = 0;
        for (long unsigned int i = 0; i < _boxPos.size(); i++) {
            if (_playerPos.x == _boxPos.at(i).x && _playerPos.y - 1 == _boxPos.at(i).y) {
                x = i;
                }
            }
        _boxPos.at(x) = {_playerPos.x, _playerPos.y - 2};
        matrix(_playerPos.x, _playerPos.y) = '.'; 
        matrix(_playerPos.x, _playerPos.y - 1) = '@';
        matrix(_playerPos.x, _playerPos.y - 2) = '1';
        _playerPos.y -= 1;

    } else if (dir == "Right") {
        x = 0;
        for (long unsigned int i = 0; i < _boxPos.size(); i++) {
            if (_playerPos.x == _boxPos.at(i).x && _playerPos.y +1 == _boxPos.at(i).y) {
                x = i;
                }
            }
        _boxPos.at(x) = {_playerPos.x, _playerPos.y + 2};
        matrix(_playerPos.x, _playerPos.y) = '.'; 
        matrix(_playerPos.x, _playerPos.y + 1) = '@';
        matrix(_playerPos.x, _playerPos.y + 2) = '1';
        _playerPos.y += 1;
    }
}

void Sokoban::storagePlayer(std::string dir) {
    int x = 0;
    if (dir == "Up") {
        for (long unsigned int i = 0; i < _boxPos.size(); i++) {
            if (_playerPos.x - 1 == _boxPos.at(i).x && _playerPos.y == _boxPos.at(i).y) {
                x = i;
                }
            }
        _boxPos.at(x) = {_playerPos.x - 2, _playerPos.y};
        matrix(_playerPos.x, _playerPos.y) = '.';
        matrix(_playerPos.x - 1, _playerPos.y) = '@';
        std::cout << _playerPos.x - 1<< ", " << _playerPos.y << std::endl << std::endl; 
        matrix(_playerPos.x - 2, _playerPos.y) = 'A';
        std::cout << _playerPos.x - 2 << ", " << _playerPos.y << std::endl << std::endl; 
        _playerPos.x -= 1;
    } else if (dir == "Down") {
        x = 0;
        for (long unsigned int i = 0; i < _boxPos.size(); i++) {
            if (_playerPos.x + 1 == _boxPos.at(i).x && _playerPos.y == _boxPos.at(i).y) {
                            x = i;
                        }
        }
        _boxPos.at(x) = {_playerPos.x + 2, _playerPos.y};  
        matrix(_playerPos.x, _playerPos.y) = '.';
        matrix(_playerPos.x + 1, _playerPos.y) = '@';
        matrix(_playerPos.x + 2, _playerPos.y) = 'A';
        _playerPos.x += 1;
    } else if (dir == "Right") {
        x = 0;

        for (long unsigned int i = 0; i < _boxPos.size(); i++) {
            if (_playerPos.x == _boxPos.at(i).x && _playerPos.y +1 == _boxPos.at(i).y) {
                x = i;
                }
        }
        _boxPos.at(x) = {_playerPos.x, _playerPos.y + 2};
        matrix(_playerPos.x, _playerPos.y) = '.';
        matrix(_playerPos.x , _playerPos.y + 1) = '@';
        matrix(_playerPos.x, _playerPos.y + 2) = 'A';
        _playerPos.y += 1;
    } else if (dir == "Left") {
        x = 0;
 
        for (long unsigned int i = 0; i < _boxPos.size(); i++) {
         if (_playerPos.x == _boxPos.at(i).x && _playerPos.y - 1 == _boxPos.at(i).y) {
            x = i;
        }
        }
        _boxPos.at(x) = {_playerPos.x, _playerPos.y - 2};
        matrix(_playerPos.x, _playerPos.y) = '.';
        matrix(_playerPos.x , _playerPos.y - 1) = '@';
        matrix(_playerPos.x, _playerPos.y - 2) = 'A';
        _playerPos.y -= 1;
    }
}

void Sokoban::storageDraw(std::string dir) {
    if (dir == "Up") {
        if (matrix(_playerPos.x - 2, _playerPos.y) != '#' && matrix(_playerPos.x - 2, _playerPos.y) != 'A') {
                matrix(_playerPos.x, _playerPos.y) = 'a';
                matrix(_playerPos.x - 1, _playerPos.y) = '@';
                std::cout << _playerPos.x - 1 << ", " << _playerPos.y << std::endl << std::endl; 
                matrix(_playerPos.x - 2, _playerPos.y) = 'A';
                std::cout << _playerPos.x - 2 << ", " << _playerPos.y << std::endl << std::endl; 
                _playerPos.x -= 1;
            }
    } else if (dir == "Down") {
        if (matrix(_playerPos.x + 2, _playerPos.y) != '#' && matrix(_playerPos.x + 2, _playerPos.y) != 'A') {
                matrix(_playerPos.x, _playerPos.y) = 'a';
                matrix(_playerPos.x + 1, _playerPos.y) = '@';
                matrix(_playerPos.x + 2, _playerPos.y) = 'A';
                _playerPos.x += 1;
            }
    } else if (dir == "Left") {
        if (matrix(_playerPos.x, _playerPos.y - 2) != '#' && matrix(_playerPos.x, _playerPos.y - 2) != 'A') {
                matrix(_playerPos.x, _playerPos.y) = 'a';
                matrix(_playerPos.x, _playerPos.y - 1) = '@';
                matrix(_playerPos.x , _playerPos.y - 2) = 'A';
                _playerPos.y -= 1;
            }
    } else if (dir == "Right") {
        if (matrix(_playerPos.x, _playerPos.y + 2) != '#' && matrix(_playerPos.x , _playerPos.y + 2) != 'A') {
                matrix(_playerPos.x, _playerPos.y) = 'a';
                matrix(_playerPos.x, _playerPos.y + 1) = '@';
                matrix(_playerPos.x, _playerPos.y + 2) = 'A';
                _playerPos.y += 1;
            }
    }
}

bool Sokoban::isAtStorage(sf::Vector2i playerPos) {
    for (long unsigned int i = 0; i < _storagePos.size(); i++) {
        if (playerPos.x == _storagePos.at(i).x && playerPos.y == _storagePos.at(i).y) {
            return true;
        }
    }
    return false;
}


void Sokoban::blockData() {
    sf::Vector2i blockPos(0,0);
    _blockLength.x = _windowSize.x / _width;
    _blockLength.y = _windowSize.y / _height;
    // Block imagep 
    _wall.loadFromFile("block_06.png");
    _box.loadFromFile("crate_03.png");
    _empty.loadFromFile("ground_01.png");
    _storage.loadFromFile("ground_04.png");
    _playerFront.loadFromFile("player_05.png");
    _playerBack.loadFromFile("player_08.png");
    _playerRight.loadFromFile("player_17.png");
    _playerLeft.loadFromFile("player_20.png");

    for (int i = 0; i < matrix.getRows(); i++) {
        for (int j = 0; j < matrix.getColumns(); j++) {
            if (matrix(i, j) == '@') {
                _playerPos.x = i;
                _playerPos.y = j;
            } else if (matrix(i,j) == 'A') {
                _boxPos.push_back({i, j});
            } else if (matrix(i, j) == 'a') {
                _storagePos.push_back({i,j});
            }
    }
    
}
        
}

void Sokoban::draw(sf::RenderTarget& window, sf::RenderStates states) const {
    sf::Sprite sprite;
    sf::Sprite sprite2;
    sf::Vector2i blockPos(0, 0);
    for (int i = 0; i < (matrix.getColumns() * matrix.getRows()); i++) {
        if ((i % matrix.getColumns()) == 0 && i != 0) {
                blockPos.x = 0;
                blockPos.y += _blockLength.y;
        }
        switch (matrix.getData(i)) {
            case '@':
                sprite.setTexture(_playerFront);
                sprite2.setTexture(_empty);
                sprite2.setPosition(blockPos.x, blockPos.y);
                window.draw(sprite2, states);
                break;
            case '.':
                sprite.setTexture(_empty);
                break;
            case '#':
                sprite.setTexture(_wall);
                break;
            case 'A':
                sprite.setTexture(_box);
                break;
            case 'a':
                sprite.setTexture(_storage);
                break;
            case '1':
                sprite.setTexture(_box);
                sprite2.setTexture(_storage);
                sprite2.setPosition(blockPos.x, blockPos.y);
                window.draw(sprite2, states);
                break;
        }
        sprite.setPosition(blockPos.x, blockPos.y);
        window.draw(sprite, states);
        blockPos.x += _blockLength.x;
}
}

void Sokoban::restartGame(Restart res) {
    if (res == Reset) {
        matrix = _origMatrix;
    }
    _boxPos.erase(_boxPos.begin(), _boxPos.end());
    _storagePos.erase(_storagePos.begin(), _storagePos.end());
    for (int i = 0; i < matrix.getRows(); i++) {
        for (int j = 0; j < matrix.getColumns(); j++) {
            if (matrix(i, j) == '@') {
                _playerPos.x = i;
                _playerPos.y = j;
            } else if (matrix(i,j) == 'A') {
                _boxPos.push_back({i, j});
            } else if (matrix(i, j) == 'a') {
                _storagePos.push_back({i,j});
            }
    }
    
}

}


bool Sokoban::isOutWindowParam(std::string dir) {
    std::cout << "In bool func: " << _playerPos.x << ", " << _playerPos.y << std::endl;
    std::cout << "Rows: " << matrix.getRows() << ", " << "Columns: " <<  matrix.getColumns() << std::endl;
    return (((_playerPos.x - 1) < 0 && dir == "Up") || ((_playerPos.y - 1) < 0 && dir == "Left") || ((_playerPos.x + 1) >= (matrix.getRows() ) && dir == "Down" ) || ((_playerPos.y + 1) >= matrix.getColumns() && dir == "Right"));
}


bool Sokoban::playerBoxPar(std::string dir) {
   return (((_playerPos.x - 2) < 0 && dir == "Up") || ((_playerPos.y - 2) < 0 && dir == "Left") || ((_playerPos.x + 2) >= (matrix.getRows() ) && dir == "Down" ) || ((_playerPos.y + 2) >= matrix.getColumns() && dir == "Right"));
}


int Sokoban::isWon() const {
    int gameState = 0;
    if (_storagePos.size() > _boxPos.size()) {
        for (long unsigned int i = 0; i < _boxPos.size(); i++) {
        for (long unsigned int j = 0; j < _storagePos.size(); j++) {
            if (_boxPos.at(i) == _storagePos.at(j)){
                gameState = 1;
            }
        }
        if (gameState != 1) return 0;
        gameState = 0;
    }
    return 1;
    } else {
    for (long unsigned int i = 0; i < _storagePos.size(); i++) {
        for (long unsigned int j = 0; j < _boxPos.size(); j++) {
            if (_storagePos.at(i) == _boxPos.at(j)){
                gameState = 1;
            }
        }
        if (gameState != 1) return 0;
        gameState = 0;
    }
    return 1;
    }

}



/*
void Sokoban::freeMemory() {
    matrix.~Matrix();
    _origMatrix.~Matrix();
}
*/
