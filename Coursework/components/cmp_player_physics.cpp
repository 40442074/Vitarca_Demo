#include "cmp_player_physics.h"
#include "system_physics.h"
#include <LevelSystem.h>
#include <SFML/Window/Keyboard.hpp>
#include "../game.h"
#include "../Keys.h"


using namespace std;
using namespace sf;

sf::Event eventT;

void PlayerPhysicsComponent::update(double dt) {
    const auto pos = _parent->getPosition();
    _movingX = false;

    //Teleport to start if we fall off map.
    if (pos.y > ls::getHeight() * ls::getTileSize()) {
        teleport(ls::getTilePosition(ls::findTiles(ls::START)[0]));
    }

    if (_state == Walking && (Keyboard::isKeyPressed(Keyboard::Key::S)))
    {
        setState(Rolling);
    }
    else if (!(Keyboard::isKeyPressed(Keyboard::Down) || Keyboard::isKeyPressed(Keyboard::S)))
    {
        sounds.PlayPwalkSound();
        setState(Walking);
    }

    if (Keyboard::isKeyPressed(Keyboard::Right) || Keyboard::isKeyPressed(Keyboard::D))
        horizontalMove(true, dt);
    else if (Keyboard::isKeyPressed(Keyboard::Left) || Keyboard::isKeyPressed(Keyboard::A))
        horizontalMove(false, dt);

    if (Keyboard::isKeyPressed(Keyboard::Up) || Keyboard::isKeyPressed(Keyboard::W)) 
        jump(dt, pos);

    CanBotPhysicsComponent::update(dt);
}

PlayerPhysicsComponent::PlayerPhysicsComponent(Entity* p, const Vector2f& size) : CanBotPhysicsComponent(p, size) {}