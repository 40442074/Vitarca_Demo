#include "MyLevelSystem.h"
#include <fstream>
#include <iostream>
                               
using namespace std;
using namespace sf;
//used code from PACMAN
std::unique_ptr<LevelSystem::TILE[]> LevelSystem::_tiles;
size_t LevelSystem::_width;
size_t LevelSystem::_height;
Vector2f LevelSystem::_offset(0.0f, 0.0f);

int tileSizeArray = 0;
std::vector<LevelSystem::TILE> tileCopy;

float LevelSystem::_tileSize(100.f);
vector<std::unique_ptr<sf::RectangleShape>> LevelSystem::_sprites;

std::map<LevelSystem::TILE, sf::Color> LevelSystem::_colours{ {WALL, Color::White}, {FINISH, Color::Red}, {CAMERA1, Color::Blue},  {CAMERA2, Color::Black}, {CAMERA3, Color::Green}, {CAMERA4, Color::Yellow},{EMPTY, Color::Cyan} };

//sf::Color LevelSystem::getColor(LevelSystem::TILE t) {
//    auto it = _colours.find(t);
//    if (it == _colours.end()) {
//        _colours[t] = Color::Transparent;
//    }
//    return _colours[t];
//}
//
//void LevelSystem::setColor(LevelSystem::TILE t, sf::Color c) {
//    _colours[t] = c;
//}
//used code from PACMAN

//used code from PACMAN
void LevelSystem::loadLevelFile(const std::string& path, float tileSize) {
    _tileSize = tileSize;
    size_t w = 0, h = 0;
    string buffer;

    // Load in file to buffer
    ifstream f(path);
    std::cout << path;
    if (f.good()) {

        f.seekg(0, std::ios::end);
        buffer.resize(f.tellg());
        f.seekg(0);
        f.read(&buffer[0], buffer.size());
        f.close();
    }
    else {

        std::cout << path;
        throw string("Couldn't open level file: ") + path;
    }

    std::vector<TILE> temp_tiles;
    for (int i = 0; i < buffer.size(); ++i) {
        const char c = buffer[i];
        switch (c) {
        case 'w':
            temp_tiles.push_back(WALL);
            break;
        case 'c':
            //temp_tiles.push_back(CAMERA);

            if (h < 1) //if top row
            {
                if (buffer[i - 1] != 'c') //if no C to the left, then pick top left cam
                {
                    temp_tiles.push_back(CAMERA1);
                }
                else //else pick top right cam
                {
                    temp_tiles.push_back(CAMERA2);
                }
            }
            else if (h > 0) //if not top row
            {
                if (buffer[i - 1] != 'c') //if no cam to left
                {
                    temp_tiles.push_back(CAMERA3); //pick bottom left cam
                }
                else //else pick bottom right cam
                {
                    temp_tiles.push_back(CAMERA4); 
                }
            }
            break;
        case 'e':
            temp_tiles.push_back(ENEMY);
            break;
        case 'f':
            temp_tiles.push_back(FINISH);
            break;
        case 's':
            temp_tiles.push_back(START);
            break;
        case ' ':
            temp_tiles.push_back(EMPTY);
            break;
        case 'p':
            temp_tiles.push_back(PUZZLE);
            break;
        case '\n':      // end of line
            if (w == 0) { // if we haven't written width yet
                w = i;      // set width
            }
            h++; // increment height
            std::cout<<"";
            break;
        case '\t':
            throw string("File includes tabs") + path;;
            break;
        default:
            cout << c << endl; // Don't know what this tile type is
        }
    }
    if (temp_tiles.size() != (w * h)) {
        throw string("Can't parse level file") + path;
    }
    _tiles = std::make_unique<TILE[]>(w * h);
    tileSizeArray = temp_tiles.size();
    tileCopy = temp_tiles;
    _width = w; //set static class vars
    _height = h;
    std::copy(temp_tiles.begin(), temp_tiles.end(), &_tiles[0]);
    cout << "Level " << path << " Loaded. " << w << "x" << h << std::endl;
    //buildSprites();
}
//used code from PACMAN

//used code from PACMAN
//void LevelSystem::buildSprites() {
//    _sprites.clear();
//    for (size_t y = 0; y < _height; ++y) {
//        for (size_t x = 0; x < _width; ++x) {
//            auto s = make_unique<RectangleShape>();
//            s->setPosition(getTilePosition({ x, y }));
//            s->setSize(Vector2f(_tileSize, _tileSize));
//            s->setFillColor(getColor(getTile({ x, y })));
//            _sprites.push_back(move(s));
//        }
//    }
//}
//used code from PACMAN

//used code from PACMAN
Vector2f LevelSystem::getTilePosition(Vector2ul p) {
    return (Vector2f(p.x, p.y) * _tileSize);
}
//used code from PACMAN

//used code from PACMAN
//LevelSystem::TILE LevelSystem::getTile(Vector2ul p) {
//    if (p.x > _width || p.y > _height) {
//        throw string("Tile out of range: ") + to_string(p.x) + "," + to_string(p.y) + ")";
//    }
//    return _tiles[(p.y * _width) + p.x];
//}
//used code from PACMAN

////used code from PACMAN
//LevelSystem::TILE LevelSystem::getTileAt(Vector2f v) {
//    auto a = v - _offset;
//    if (a.x < 0 || a.y < 0) {
//        throw string("Tile out of range ");
//    }
//    return getTile(Vector2ul((v - _offset) / (_tileSize)));
//}
////used code from PACMAN

//used code from PACMAN
size_t LevelSystem::getWidth()
{
    return _width; //broken
}
//used code from PACMAN

//used code from PACMAN
//size_t LevelSystem::getHeight(size_t height)
//{
//    height = _height;
//    return height; //broken
//}
//used code from PACMAN

int LevelSystem::GetTileSize()
{
    return tileSizeArray;
}

std::vector<LevelSystem::TILE> LevelSystem::getTileNames()
{
    return tileCopy;
}

//used code from PACMAN
//vector<Vector2ul> LevelSystem::findTiles(lvlSys::TILE t)
//{
//    vector<Vector2ul> returnvar;
//    for (int i = 0; i < (_width * _height); i++)
//    {
//        if (_tiles[i] == t)
//        {
//            returnvar.push_back(Vector2ul(i % _width, (i - (i % _width)) / _width));
//        }
//    }
//
//    return returnvar;
//}
//used code from PACMAN

//used code from PACMAN
//void LevelSystem::Render(RenderWindow& window) {
//    for (size_t i = 0; i < _width * _height; ++i) {
//        //window.draw(*_sprites[i]);
//    }
//}
//used code from PACMAN