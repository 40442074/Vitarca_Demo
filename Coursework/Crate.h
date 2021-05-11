#pragma once
#include "SFML/Graphics/Texture.hpp"
#include "Box2D/Dynamics/b2Body.h"
#include "CanBot.h"
#include <ecm.h>

class Crate : public Entity {
private:
	std::shared_ptr<sf::Texture> _texture;

public:
	Crate(Scene* s);

	void load(Player *p);
};