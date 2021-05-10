#include "BGSpriteLoader.h"
#include <iostream>
#include "LevelSystem.h"
#include "game.h"
//#include "scenes/scene_tracker.h"


using namespace std;
using namespace sf;

Texture BGspriteSheet;
std::vector<Sprite> totalSprites;
std::vector<Sprite> spriteTypes;

void BGSpriteLoader::ReadSpriteSheet()
{ 
    if (!BGspriteSheet.loadFromFile("res/img/TileSet-360x60.png")) {
        cerr << "Failed to load spritesheet!" << std::endl;
    }
    
    spriteTypes.clear();
    totalSprites.clear();
    for (int i = 0; i < 6; i++)
    {
        spriteTypes.push_back(Sprite());
        spriteTypes[i].setTexture(BGspriteSheet);
        spriteTypes[i].setScale(Vector2f(sceneTracker.GetMultiplier(), sceneTracker.GetMultiplier()));
        spriteTypes[i].setTextureRect(sf::IntRect(i * 60, 0, 60, 60));
    }
}

void BGSpriteLoader::Load()
{
    ReadSpriteSheet();
    auto tiles = ls::getTileNames();
    //for each tile in the list, how many are of wall or empty etc.
    //want to set the position of all of the sprites
    auto width = ls::getWidth();
    for (int i = 0; i < tiles.size(); i++)
    {
        if (tiles[i] == ls::WALL)
        {
            totalSprites.push_back(spriteTypes[1]);
        }
        else if (tiles[i] == ls::CAMERA1)
        {
            totalSprites.push_back(spriteTypes[2]);
        }
        else if (tiles[i] == ls::CAMERA2)
        {
            totalSprites.push_back(spriteTypes[3]);
        }
        else if (tiles[i] == ls::CAMERA3)
        {
            totalSprites.push_back(spriteTypes[4]);
        }
        else if (tiles[i] == ls::CAMERA4)
        {
            totalSprites.push_back(spriteTypes[5]);
        }
        else if (tiles[i] == ls::ENEMY)
        {
            totalSprites.push_back(spriteTypes[2]);
        }
        else if (tiles[i] == ls::END)
        {
            totalSprites.push_back(spriteTypes[2]);
        }
        else if (tiles[i] == ls::START)
        {
            totalSprites.push_back(spriteTypes[2]);
        }
        else if (tiles[i] == ls::EMPTY)
        {
            totalSprites.push_back(spriteTypes[0]);
        }
        totalSprites[i].setPosition(ls::getTilePosition(Vector2ul(i % width, (i - (i % width)) / width)));
    }


    //have 7 textures in the sprite list, need to duplicate these sprites at the positions
    //of the tiles where WALL or EMPTY are and place the sprite on that position.

    //give each tile a sprite and set that sprite to the corresponding texture sheet one. so set a WALL sprite to the 2nd sprite
    //in the sheet.
    
}

void BGSpriteLoader::Render(RenderWindow& window)
{
    for (int i = 0; i < totalSprites.size(); i++)
    {
        window.draw(totalSprites[i]);
    }
}