//#pragma once
//
//#include <SFML/Graphics.hpp>
//#include <memory>
//#include <string>
//#include <vector>
//#include <maths.h>
//
//#define lvlSys LevelSystem
//
//class LevelSystem {
//public:
//	enum TILE { WALL, CAMERA1, CAMERA2, CAMERA3, CAMERA4, ENEMY, FINISH, START, EMPTY, PUZZLE };
//
////used code from PACMAN
//	static void loadLevelFile(const std::string&, float tileSize = 100.f);
//	//static void Render(sf::RenderWindow& window);
//	//static sf::Color getColor(TILE t);
//	//static void setColor(TILE t, sf::Color c);
//	//Get Tile at grid coordinate
//	//static TILE getTile(sf::Vector2ul);
//	//Get Screenspace coordinate of tile
//	static sf::Vector2f getTilePosition(sf::Vector2ul);
//	//get the tile at screenspace pos
//	//static TILE getTileAt(sf::Vector2f);
//	static int GetTileSize();
//	static std::vector<TILE> getTileNames();
//
//	static size_t getWidth();
//	//static size_t getHeight(size_t _height);
//	//static std::vector<sf::Vector2ul> findTiles(TILE);
////used code from PACMAN
//
//protected:
//
////used code from PACMAN
//	static std::unique_ptr<TILE[]> _tiles; //Internal array of tiles
//	static size_t _width; //how many tiles wide is level
//	static size_t _height; //how many tile high is level
//	static sf::Vector2f _offset; //Screenspace offset of level, when rendered.
//	static float _tileSize; //Screenspace size of each tile, when rendered.
//	static std::map<TILE, sf::Color> _colours; //color to render each tile type
//
//	//array of sfml sprites of each tile
//	static std::vector<std::unique_ptr<sf::RectangleShape>> _sprites;
//	//generate the _sprites array
//	//static void buildSprites();
////used code from PACMAN
//
//private:
//	LevelSystem() = delete;
//	~LevelSystem() = delete;
//};