#include "CanBot.h"
#include "components/cmp_player_physics.h"
#include "components/cmp_enemy_physics.h"
#include "game.h"

using namespace std;
using namespace sf;

//--------------------CanBot--------------------

void CanBot::load() {
    _sprite = addComponent<SpriteComponent>();
    _texture.get()->loadFromFile("res/img/player_spritesheet.png");
    _sprite->setTexture(_texture);
    _sprite->getSprite().setTextureRect(IntRect(0, 0, 27, 48));
    _sprite->getSprite().setOrigin(13.5f * sceneTracker.GetMultiplier(), 24.f * sceneTracker.GetMultiplier());
}

void CanBot::update(double dt, b2Body * b) {

    if (_physCmp->getState() == Rolling)
    {
        _sRotVel = b->GetAngularVelocity() * -100.0f;
    }
    else
    {
        _sRotVel = 0.0f;
    }

    _sRotation += _sRotVel * dt;

    //Keep rotation within 360 degrees
    if (_sRotation >= 360.0f)
        _sRotation -= 360.0f;
    if (_sRotation < 0.0f)
        _sRotation += 360.0f;

    int spriteNo = ((int)trunc(_sRotation) - ((int)trunc(_sRotation) % 24)) / 24;
    if (spriteNo == 15)
        spriteNo = 0;
    int x = (spriteNo % _ssWidth);
    int y = (spriteNo - (spriteNo % _ssWidth)) / _ssWidth;

    _sprite->getSprite().setTextureRect(IntRect(x * 27, y * 48, 27, 48));

    Entity::update(dt);
}

CanBot::CanBot(Scene* s) : Entity(s) {
    _texture = make_shared<Texture>(Texture());
    _sRotation = 0;
    _sRotVel = 0;
}

//--------------------Player--------------------

void Player::load() {
    addTag("player");

    _physCmp = addComponent<PlayerPhysicsComponent>(Vector2f(27.f, 48.f));
    _canFixture = _physCmp.get()->getFixture();
    _body = _canFixture->GetBody();

    CanBot::load();
}

void Player::update(double dt) {
    CanBot::update(dt, _body);
}

Player::Player(Scene* s) : CanBot(s) {}

//--------------------Enemy--------------------

void Enemy::load() {
    addTag("enemy");

    _physCmp = addComponent<EnemyPhysicsComponent>(Vector2f(27.f, 48.f));
    _body = _physCmp.get()->getFixture()->GetBody();

    CanBot::load();
}

void Enemy::update(double dt) {
    CanBot::update(dt, _body);
}

Enemy::Enemy(Scene* s) : CanBot(s) {}