#pragma once
#include "cmp_physics.h"

enum CanBotState
{
	Walking,
	Rolling
};

class CanBotPhysicsComponent : public PhysicsComponent {
protected:
	b2Vec2 _size;
	sf::Vector2f _maxVelocity;
	bool _grounded;
	float _groundspeed;
	b2Fixture* _legFixture;
	CanBotState _state;
	bool _movingX;
	bool _facingR;

	bool isGrounded() const;
	void horizontalMove(bool right, double dt);
	void jump(double dt, sf::Vector2f pos);
	void setState(CanBotState s);

public:
	void virtual update(double dt) override = 0;

	explicit CanBotPhysicsComponent(Entity* p, const sf::Vector2f& size);

	CanBotPhysicsComponent() = delete;

	CanBotState getState() {
		return _state;
	}

	bool getFacingR() {
		return _facingR;
	}
};