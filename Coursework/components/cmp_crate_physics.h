#pragma once
#include "cmp_physics.h"

class CratePhysicsComponent : public PhysicsComponent {
protected:
	b2Vec2 _size;

public:
	void update(double dt) override;

	explicit CratePhysicsComponent(Entity* p, const sf::Vector2f& size);

	CratePhysicsComponent() = delete;
};