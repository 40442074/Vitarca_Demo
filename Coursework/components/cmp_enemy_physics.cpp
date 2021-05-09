#include "cmp_enemy_physics.h"
#include "system_physics.h"
#include <LevelSystem.h>
#include <SFML/Window/Keyboard.hpp>

using namespace std;
using namespace sf;

void EnemyPhysicsComponent::update(double dt) {
    const auto pos = _parent->getPosition();
    _movingx = false;

    setState(Walking);
    horizontalMove(false, dt);

    CanBotPhysicsComponent::update(dt);
}

EnemyPhysicsComponent::EnemyPhysicsComponent(Entity* p, const Vector2f& size) : CanBotPhysicsComponent(p, size) {}