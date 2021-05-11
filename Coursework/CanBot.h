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

	//Limbs
	sf::Vector2f _feet[2];
	bool _ftUp[2];
	std::shared_ptr<Entity> _legs[2];
	std::shared_ptr<Entity> _arms[2];
	std::shared_ptr<SpriteComponent> _legSprites[2];
	std::shared_ptr<SpriteComponent> _armSprites[2];
	std::shared_ptr<sf::Texture> _limbTexture;

	//Sprite rotations
	const int _ssWidth = 5;
	float _sRotation, _sRotVel, _sRotGoal;

	bool _grabbing = false;
	sf::Vector2f _grabbingPos;

	sf::Vector2f _legPositions[2];

public:
	CanBot(Scene* s);

	void update(double dt, b2Body* b);

	void load();

	void setGrabbing(bool g) {
		_grabbing = g;
	}
	void setGrabbingPos(sf::Vector2f p) {
		_grabbingPos = p;
	}
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