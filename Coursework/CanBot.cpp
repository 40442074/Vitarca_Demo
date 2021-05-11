#include "CanBot.h"
#include "components/cmp_player_physics.h"
#include "components/cmp_enemy_physics.h"
#include "game.h"

using namespace std;
using namespace sf;

//--------------------CanBot--------------------

void CanBot::load() {
    _sprite = addComponent<SpriteComponent>();
    _texture->loadFromFile("res/img/player_spritesheet.png");
    _sprite->setTexture(_texture);
    _sprite->getSprite().setTextureRect(IntRect(0, 0, 27, 48));
    _sprite->getSprite().setOrigin(13.5f * sceneTracker.GetMultiplier(), 24.f * sceneTracker.GetMultiplier());

    _legTexture->loadFromFile("res/img/crate.png");
    for (int i = 0; i < 2; i++)
    {
        _feet[i] = scene->makeEntity();
        _legSprites[i] = _feet[i]->addComponent<SpriteComponent>();
        _legSprites[i]->setTexture(_legTexture);
        _legSprites[i]->getSprite().setTextureRect(IntRect(0, 0, 60, 60));
        _legSprites[i]->getSprite().setOrigin(30.f * sceneTracker.GetMultiplier(), 30.f * sceneTracker.GetMultiplier());
        _legSprites[i]->getSprite().setScale(1.f/5.f, 1.f/5.f);
    }

    _feet[0]->setPosition(Vector2f(getPosition().x - 13.5f, getPosition().y + 34.f));
    _ftUp[0] = true;
    _feet[1]->setPosition(Vector2f(getPosition().x + 13.5f - 30.f, getPosition().y + 44.f));
    _ftUp[1] = false;
}

void CanBot::update(double dt, b2Body * b) {

    //Set sprite "rolling" effect speed
    if (_physCmp->getState() == Rolling)
    {
        //Spin based on box2d angular velocity
        _sRotVel = b->GetAngularVelocity() * -100.0f;
    }
    else
    {
        //Spin based on a goal angle dictated by facing direction
        if (_physCmp->getFacingR())
            _sRotGoal = 0.0f;
        else
            _sRotGoal = 180.0f;

        _sRotVel = ((_sRotGoal - _sRotation) * 3.0f);     
    }
    _sRotation += _sRotVel * dt;

    //Keep rotation within 360 degrees
    if (_sRotation >= 360.0f)
        _sRotation -= 360.0f;
    if (_sRotation < 0.0f)
        _sRotation += 360.0f;

    //Work out which part of the sprite to use
    int spriteNo = ((int)trunc(_sRotation) - ((int)trunc(_sRotation) % 24)) / 24;
    if (spriteNo == 15)
        spriteNo = 0;
    int x = (spriteNo % _ssWidth);
    int y = (spriteNo - (spriteNo % _ssWidth)) / _ssWidth;
    _sprite->getSprite().setTextureRect(IntRect(x * 27, y * 48, 27, 48));

    if (_physCmp->getFacingR())
    {
        if (_feet[0]->getPosition().x - (getPosition().x/* - 13.5f*/) < -30.f && !_ftUp[0])
        {
            _feet[0]->setPosition(Vector2f(_feet[0]->getPosition().x, getPosition().y + 34.f));
            _ftUp[0] = true;
            _feet[1]->setPosition(Vector2f(getPosition().x/* + 13.5f*/ + 30.f, getPosition().y + 44.f));
            _ftUp[1] = false;
        }
        if (_feet[1]->getPosition().x - (getPosition().x/* + 13.5f*/) < -30.f && !_ftUp[1])
        {
            _feet[1]->setPosition(Vector2f(_feet[1]->getPosition().x, getPosition().y + 34.f));
            _ftUp[1] = true;
            _feet[0]->setPosition(Vector2f(getPosition().x/* - 13.5f*/ + 30.f, getPosition().y + 44.f));
            _ftUp[0] = false;
        }
    }
    else
    {
        if (_feet[0]->getPosition().x - (getPosition().x/* - 13.5f*/) > 30.f && !_ftUp[0])
        {
            _feet[0]->setPosition(Vector2f(_feet[0]->getPosition().x, getPosition().y + 34.f));
            _ftUp[0] = true;
            _feet[1]->setPosition(Vector2f(getPosition().x/* + 13.5f*/ - 30.f, getPosition().y + 44.f));
            _ftUp[1] = false;
        }
        if (_feet[1]->getPosition().x - (getPosition().x/* + 13.5f*/) > 30.f && !_ftUp[1])
        {
            _feet[1]->setPosition(Vector2f(_feet[1]->getPosition().x, getPosition().y + 34.f));
            _ftUp[1] = true;
            _feet[0]->setPosition(Vector2f(getPosition().x/*- 13.5f*/ - 30.f, getPosition().y + 44.f));
            _ftUp[0] = false;
        }
    }

    if (_ftUp[0])
        _feet[0]->setPosition(Vector2f(_feet[0]->getPosition().x + b->GetLinearVelocity().x, getPosition().y + 34.f));
    if (_ftUp[1])
        _feet[1]->setPosition(Vector2f(_feet[1]->getPosition().x + b->GetLinearVelocity().x, getPosition().y + 34.f));

    Entity::update(dt);
}

CanBot::CanBot(Scene* s) : Entity(s) {
    _texture = make_shared<Texture>(Texture());
    _legTexture = make_shared<Texture>(Texture());
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