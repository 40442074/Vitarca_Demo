#include "cmp_enemy_physics.h"
#include "system_physics.h"
#include <LevelSystem.h>
#include <SFML/Window/Keyboard.hpp>

using namespace std;
using namespace sf;

void EnemyPhysicsComponent::update(double dt) {
    const auto pos = _parent->getPosition();
    _movingX = false;

    setState(Walking);

    if (_movingLeft)
    {
        horizontalMove(false, dt);
        auto currTile = ls::getTileIndex(pos);
        auto left = ls::getTile(Vector2ul(currTile.x - 1, currTile.y));
        auto leftanddown = ls::getTile(Vector2ul(currTile.x - 1, currTile.y - 1));

        if (ls::getTile(Vector2ul(currTile.x - 1, currTile.y)) == ls::WALL || ls::getTile(Vector2ul(currTile.x - 1, currTile.y + 1)) == ls::EMPTY)
        {
            _movingLeft = false;
        }
    }
    else
    {
        horizontalMove(true, dt);
        auto currTile = ls::getTileIndex(pos);

        if (ls::getTile(Vector2ul(currTile.x + 1, currTile.y)) == ls::WALL || ls::getTile(Vector2ul(currTile.x + 1, currTile.y + 1)) == ls::EMPTY)
        {
            _movingLeft = true;
        }
    }

    CanBotPhysicsComponent::update(dt);
}

EnemyPhysicsComponent::EnemyPhysicsComponent(Entity* p, const Vector2f& size) : CanBotPhysicsComponent(p, size) {}