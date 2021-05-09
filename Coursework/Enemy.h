#pragma once
#include "ecm.h"
#include "SFML/Graphics/Texture.hpp"
#include "Box2D/Dynamics/b2Fixture.h"

class Enemy : public Entity {
private:
	std::shared_ptr<sf::Texture> _texture;

public:
	Enemy(Scene* s);

	void load();
};