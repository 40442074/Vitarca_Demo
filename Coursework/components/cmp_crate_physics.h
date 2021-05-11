#pragma once
#include "cmp_physics.h"
#include "../CanBot.h"

class CratePhysicsComponent : public PhysicsComponent {
protected:
	b2Vec2 _size;
	b2Body* _playerBody;
	Player* _player;
	bool _beingHeld;

public:
	void update(double dt) override;

	explicit CratePhysicsComponent(Entity* p, const sf::Vector2f& size, b2Body *pb, Player *pl);

	CratePhysicsComponent() = delete;
};