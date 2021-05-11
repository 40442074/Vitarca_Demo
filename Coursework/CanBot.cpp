#include "CanBot.h"
#include "components/cmp_player_physics.h"
#include "components/cmp_enemy_physics.h"
#include "game.h"
#include "system_physics.h"

using namespace std;
using namespace sf;

//--------------------CanBot--------------------

void CanBot::load() {
    _sprite = addComponent<SpriteComponent>();
    _texture->loadFromFile("res/img/player_spritesheet.png");
    _sprite->setTexture(_texture);
    _sprite->getSprite().setTextureRect(IntRect(0, 0, 27, 48));
    _sprite->getSprite().setOrigin(13.5f * sceneTracker.GetMultiplier(), 24.f * sceneTracker.GetMultiplier());

    _limbTexture->loadFromFile("res/img/leg.png");
    for (int i = 0; i < 2; i++)
    {
        _legs[i] = scene->makeEntity();
        _legSprites[i] = _legs[i]->addComponent<SpriteComponent>();
        _legSprites[i]->setTexture(_limbTexture);
        _legSprites[i]->getSprite().setTextureRect(IntRect(0, 0, 7, 20));
        _legSprites[i]->getSprite().setOrigin(3.5f * sceneTracker.GetMultiplier(), 0);
        _legSprites[i]->getSprite().setScale(1.f, 1.f);

        _arms[i] = scene->makeEntity();
        _armSprites[i] = _arms[i]->addComponent<SpriteComponent>();
        _armSprites[i]->setTexture(_limbTexture);
        _armSprites[i]->getSprite().setTextureRect(IntRect(0, 0, 7, 20));
        _armSprites[i]->getSprite().setOrigin(3.5f * sceneTracker.GetMultiplier(), 0);
        _armSprites[i]->getSprite().setScale(1.f, 1.f);

        _arms[i]->setPosition(_physCmp->getCornerPos(i));
        _legs[i]->setPosition(_physCmp->getCornerPos(i + 2));
    }
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

    //Foot placement logic - if either foot is too far away while placed on the ground, they swap places
    //and the other foot is grounded, with the original being lifted
    if (_physCmp->getFacingR())
    {
        if (_feet[0].x - (getPosition().x) < -30.f && !_ftUp[0])
        {
            _feet[0] = Vector2f(_feet[0].x, getPosition().y + 34.f);
            _ftUp[0] = true;
            _feet[1] = Vector2f(getPosition().x + 30.f, getPosition().y + 44.f);
            _ftUp[1] = false;
        }
        if (_feet[1].x - getPosition().x < -30.f && !_ftUp[1])
        {
            _feet[1] = Vector2f(_feet[1].x, getPosition().y + 34.f);
            _ftUp[1] = true;
            _feet[0] = Vector2f(getPosition().x + 30.f, getPosition().y + 44.f);
            _ftUp[0] = false;
        }
    }
    else
    {
        if (_feet[0].x - getPosition().x > 30.f && !_ftUp[0])
        {
            _feet[0] = Vector2f(_feet[0].x, getPosition().y + 34.f);
            _ftUp[0] = true;
            _feet[1] = Vector2f(getPosition().x - 30.f, getPosition().y + 44.f);
            _ftUp[1] = false;
        }
        if (_feet[1].x - (getPosition().x) > 30.f && !_ftUp[1])
        {
            _feet[1] = Vector2f(_feet[1].x, getPosition().y + 34.f);
            _ftUp[1] = true;
            _feet[0] = Vector2f(getPosition().x - 30.f, getPosition().y + 44.f);
            _ftUp[0] = false;
        }
    }

    //Maintain correct foot y position
    if (_ftUp[0])
        _feet[0] = Vector2f(_feet[0].x + b->GetLinearVelocity().x, getPosition().y + 34.f);
    if (_ftUp[1])
        _feet[1] = Vector2f(_feet[1].x + b->GetLinearVelocity().x, getPosition().y + 34.f);

    //Decide whether legs should be retracted or not
    Vector2f footTarget[2];
    if (_physCmp->getState() == Rolling || !_physCmp->getGrounded())
    {
        footTarget[0] = Vector2f(_physCmp->getCornerPos(2).x, _physCmp->getCornerPos(2).y + 5.0f);
        footTarget[1] = Vector2f(_physCmp->getCornerPos(3).x, _physCmp->getCornerPos(3).y + 5.0f);
    }
    else
    {
        footTarget[0] = _feet[0];
        footTarget[1] = _feet[1];
    }

    //Calculate leg scale and angle with respect to feet location
    for (int i = 0; i < 2; i++)
    {
        _legs[i]->setPosition(_physCmp->getCornerPos(i + 2));

        _legSprites[i]->getSprite().setScale(1, length(_legs[i]->getPosition() - footTarget[i]) / 20.0f);

        auto slope = (footTarget[i].y - _legs[i]->getPosition().y) / (footTarget[i].x - _legs[i]->getPosition().x);
        if (slope >= 0)
            _legs[i]->setRotation((atan(slope) * (180.0 / M_PI)) - 90.0);
        else
            _legs[i]->setRotation((atan(slope) * (180.0 / M_PI)) - 270.0);
    }

    Vector2f handTarget[2];
    if (_grabbing)
    {
        handTarget[0] = _grabbingPos;
        handTarget[1] = _grabbingPos;
    }
    else
    {
        handTarget[0] = Vector2f(_physCmp->getCornerPos(0).x, _physCmp->getCornerPos(0).y - 5.0f);
        handTarget[1] = Vector2f(_physCmp->getCornerPos(1).x, _physCmp->getCornerPos(1).y - 5.0f);
    }

    //Calculate arm scale and angle with respect to hand location
    for (int i = 0; i < 2; i++)
    {
        _arms[i]->setPosition(_physCmp->getCornerPos(i));

        _armSprites[i]->getSprite().setScale(1, length(_arms[i]->getPosition() - handTarget[i]) / 20.0f);

        auto slope = (handTarget[i].y - _arms[i]->getPosition().y) / (handTarget[i].x - _arms[i]->getPosition().x);
        double rot;
        if (slope >= 0)
            rot = (atan(slope) * (180.0 / M_PI)) - 90.0;
        else
            rot = (atan(slope) * (180.0 / M_PI)) - 270.0;

        if (handTarget[i].y < _arms[i]->getPosition().y)
            rot -= 180.0;

        _arms[i]->setRotation(rot);
    }

    Entity::update(dt);
}

CanBot::CanBot(Scene* s) : Entity(s) {
    _texture = make_shared<Texture>(Texture());
    _limbTexture = make_shared<Texture>(Texture());
    _sRotation = 0;
    _sRotVel = 0;

    _feet[0] = Vector2f(getPosition().x, getPosition().y + 34.f);
    _ftUp[0] = true;
    _feet[1] = Vector2f(getPosition().x, getPosition().y + 44.f);
    _ftUp[1] = false;
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