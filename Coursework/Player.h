#pragma once
#include "ecm.h"
#include "SFML/Graphics/Texture.hpp"
#include "Box2D/Dynamics/b2Fixture.h"

class Player : public Entity {
private:
	std::shared_ptr<sf::Texture> _texture;
	b2Body *_body;
	b2Fixture *_canFixture;

public:
	Player(Scene* s);

	void load();

	b2Body *getBody() {
		return _body;
	}

	b2Fixture *getFixture() {
		return _canFixture;
	}
};