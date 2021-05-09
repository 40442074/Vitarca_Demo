#pragma once
#include "ecm.h"
#include "SFML/Graphics/Texture.hpp"
#include "Box2D/Dynamics/b2Body.h"

class Crate : public Entity {
private:
	std::shared_ptr<sf::Texture> _texture;

public:
	Crate(Scene* s);

	void load(b2Body* pb);
};