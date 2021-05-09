#pragma once

#include "cmp_canbot_physics.h"

class EnemyPhysicsComponent : public CanBotPhysicsComponent {
protected:

public:
	void update(double dt) override;

	explicit EnemyPhysicsComponent(Entity* p, const sf::Vector2f& size);

	EnemyPhysicsComponent() = delete;
};