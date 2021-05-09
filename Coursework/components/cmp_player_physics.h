#pragma once

#include "cmp_canbot_physics.h"

class PlayerPhysicsComponent : public CanBotPhysicsComponent {
protected:

public:
  void update(double dt) override;

  explicit PlayerPhysicsComponent(Entity* p, const sf::Vector2f& size);

  PlayerPhysicsComponent() = delete;
};