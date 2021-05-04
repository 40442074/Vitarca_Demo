#pragma once
#include <SFML/Graphics.hpp>
#include "MyLevelSystem.h"
#include <memory>
#include <string>
#include <vector>
#include <maths.h>

class BGSpriteLoader {
public:
	static void ReadSpriteSheet();
	static void Load();
	static void Render(sf::RenderWindow& window);

protected:
	
};