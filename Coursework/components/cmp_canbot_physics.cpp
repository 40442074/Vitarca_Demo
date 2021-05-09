#include "cmp_canbot_physics.h"
#include "system_physics.h"
#include <LevelSystem.h>
#include <SFML/Window/Keyboard.hpp>

using namespace std;
using namespace sf;
using namespace Physics;

bool CanBotPhysicsComponent::isGrounded() const {
    auto touch = getTouching();
    const auto& pos = _body->GetPosition();
    const float halfHeigt = _size.y * .5f;
    const float halfWidth = _size.x * .52f;
    b2WorldManifold manifold;
    for (const auto& contact : touch) {
        contact->GetWorldManifold(&manifold);
        const int numPoints = contact->GetManifold()->pointCount;
        bool onTop = numPoints > 0;
        // If all contacts are below the canbot.
        for (int j = 0; j < numPoints; j++) {
            onTop &= (manifold.points[j].y < pos.y - halfHeigt);
        }
        if (onTop) {
            return true;
        }
    }

    return false;
}

void CanBotPhysicsComponent::horizontalMove(bool right, double dt) {
    _movingx = true;

    if (_state = Walking)
    {
        if (right && getVelocity().x < _maxVelocity.x)
            impulse({ (float)(dt * _groundspeed), 0 });
        else if (getVelocity().x > -_maxVelocity.x)
            impulse({ (float)(dt * -_groundspeed), 0 });
    }
    else
    {
        if (right)
        {
            if (getAngVelocity() > -10)
                _body->ApplyAngularImpulse(-10.0f * dt, true);
            if (getVelocity().x < _maxVelocity.x)
                impulse({ (float)(dt * _groundspeed * 0.3f), 0 });
        }
        else
        {
            if (getAngVelocity() < 10)
                _body->ApplyAngularImpulse(10.0f * dt, true);
            if (getVelocity().x > -_maxVelocity.x)
                impulse({ (float)(dt * -_groundspeed * 0.3f), 0 });
        }
    }
}

void CanBotPhysicsComponent::jump(double dt, Vector2f pos) {
    _grounded = isGrounded();
    if (_grounded) {
        setVelocity(Vector2f(getVelocity().x, 0.f));
        teleport(Vector2f(pos.x, pos.y - 2.0f));
        impulse(Vector2f(0, -6.f));
    }
}

void CanBotPhysicsComponent::setState(CanBotState s) {
    _state = s;

    if (s == Walking)
    {
        _legFixture->SetSensor(false);
        _body->SetTransform(_body->GetPosition(), 0);
        _body->SetAngularVelocity(0);
    }
    else
    {
        _legFixture->SetSensor(true);
    }
}

void CanBotPhysicsComponent::update(double dt) {

    //Dampen movement
    if (!_movingx)
    {
        if (_state == Walking)
            dampenLin({ 0.99f, 1.0f });
        else
        {
            dampenAng(0.999f);
            dampenLin({ 0.999f, 1.0f });
        }
    }

    if (_state == Rolling)
    {
        setFriction(1.0f);
    }
    else
    {
        //Are we in air?
        if (!_grounded) {
            // Check to see if we have landed yet
            _grounded = isGrounded();
            // disable friction while jumping
            setFriction(0.0f);
        }
        else
            setFriction(0.1f);
    }

    // Clamp velocity.
    auto v = getVelocity();
    v.x = copysign(min(abs(v.x), _maxVelocity.x), v.x);
    v.y = copysign(min(abs(v.y), _maxVelocity.y), v.y);
    setVelocity(v);

    PhysicsComponent::update(dt);
}

CanBotPhysicsComponent::CanBotPhysicsComponent(Entity* p, const Vector2f& size)
    : PhysicsComponent(p, true, size, 0.5f, 0.5f) {

    _size = sv2_to_bv2(size, true);
    _maxVelocity = Vector2f(200.f, 400.f);
    _groundspeed = 30.f;
    _grounded = false;
    _body->SetSleepingAllowed(false);
    //Bullet items have higher-res collision detection
    _body->SetBullet(true);
    _state = Walking;
    _movingx = false;

    //Create leg space
    b2PolygonShape legBottom;
    legBottom.SetAsBox(_size.x * 0.5f, sf_to_bf(20.0f , true) * 0.5f, b2Vec2(0, -((_size.y / 2.0f)) - sf_to_bf(10.0f, true)), 0);
    b2FixtureDef legFixture;
    legFixture.shape = &legBottom;
    legFixture.isSensor = false;
    _legFixture = _body->CreateFixture(&legFixture);
}