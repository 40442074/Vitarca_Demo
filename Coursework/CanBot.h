#pragma once

#include "SFML/Graphics/Texture.hpp"
#include "Box2D/Dynamics/b2Fixture.h"
#include <ecm.h>
#include "components/cmp_sprite.h"
#include "components/cmp_canbot_physics.h"

class CanBot : public Entity {
protected:
	std::shared_ptr<sf::Texture> _texture;
	std::shared_ptr<SpriteComponent> _sprite;
	std::shared_ptr<CanBotPhysicsComponent> _physCmp;

	const int _ssHeight = 3;
	const int _ssWidth = 5;
	float _sRotation, _sRotVel, _sRotGoal;
	const float _sInterval = 0;

public:
	CanBot(Scene* s);

	void update(double dt, b2Body* b);

	void load();
};

class Player : public CanBot {
protected:
	b2Body *_body;
	b2Fixture *_canFixture;

public:
	Player(Scene* s);

	void load();

	void update(double dt);

	b2Body *getBody() {
		return _body;
	}

	b2Fixture *getFixture() {
		return _canFixture;
	}
};

class Enemy : public CanBot {
protected:
	b2Body *_body;

public:
	Enemy(Scene* s);

	void load();

	void update(double dt);
};