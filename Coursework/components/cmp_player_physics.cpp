#include "cmp_player_physics.h"
#include "system_physics.h"
#include <LevelSystem.h>
#include <SFML/Window/Keyboard.hpp>

using namespace std;
using namespace sf;
using namespace Physics;

bool PlayerPhysicsComponent::isGrounded() const {
  auto touch = getTouching();
  const auto& pos = _body->GetPosition();
  const float halfPlrHeigt = _size.y * .5f;
  const float halfPlrWidth = _size.x * .52f;
  b2WorldManifold manifold;
  for (const auto& contact : touch) {
    contact->GetWorldManifold(&manifold);
    const int numPoints = contact->GetManifold()->pointCount;
    bool onTop = numPoints > 0;
    // If all contacts are below the player.
    for (int j = 0; j < numPoints; j++) {
      onTop &= (manifold.points[j].y < pos.y - halfPlrHeigt);
    }
    if (onTop) {
      return true;
    }
  }

  return false;
}

void PlayerPhysicsComponent::update(double dt) {

  const auto pos = _parent->getPosition();

  //Teleport to start if we fall off map.
  if (pos.y > ls::getHeight() * ls::getTileSize()) {
    teleport(ls::getTilePosition(ls::findTiles(ls::START)[0]));
  }

  if (Keyboard::isKeyPressed(Keyboard::Down))
  {
      _legFixture->SetSensor(true);
      // Moving Either Left or Right
      if (Keyboard::isKeyPressed(Keyboard::Right)) {
          if (getAngVelocity() < 10)
              _body->SetAngularVelocity(_body->GetAngularVelocity() + 10.0f * dt);
          if (getVelocity().x < _maxVelocity.x)
              impulse({ (float)(dt * _groundspeed * 0.3f), 0 });
      }
      else if (Keyboard::isKeyPressed(Keyboard::Left)) {
          if (getAngVelocity() > -10)
              _body->SetAngularVelocity(_body->GetAngularVelocity() - 10.0f * dt);
          if (getVelocity().x > -_maxVelocity.x)
              impulse({ -(float)(dt * _groundspeed * 0.3f), 0 });
      }
  }
  else
  {
      _legFixture->SetSensor(false);
      _body->SetTransform(_body->GetPosition(), 0);
      _body->SetAngularVelocity(0);
      if (Keyboard::isKeyPressed(Keyboard::Left) ||
          Keyboard::isKeyPressed(Keyboard::Right)) {
          // Moving Either Left or Right
          if (Keyboard::isKeyPressed(Keyboard::Right)) {
              if (getVelocity().x < _maxVelocity.x)
                  impulse({ (float)(dt * _groundspeed), 0 });
          }
          else {
              if (getVelocity().x > -_maxVelocity.x)
                  impulse({ -(float)(dt * _groundspeed), 0 });
          }
      }
      else {
          // Dampen X axis movement
          dampen({ 0.9f, 1.0f });
      }
  }

  // Handle Jump
  if (Keyboard::isKeyPressed(Keyboard::Up)) {
    _grounded = isGrounded();
    if (_grounded) {
      setVelocity(Vector2f(getVelocity().x, 0.f));
      teleport(Vector2f(pos.x, pos.y - 2.0f));
      impulse(Vector2f(0, -10.f));
    }
  }

  if (Keyboard::isKeyPressed(Keyboard::Down))
  {
      setFriction(0.0f);
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
      else {
          setFriction(0.1f);
      }
  }

  // Clamp velocity.
  auto v = getVelocity();
  v.x = copysign(min(abs(v.x), _maxVelocity.x), v.x);
  v.y = copysign(min(abs(v.y), _maxVelocity.y), v.y);
  setVelocity(v);

  PhysicsComponent::update(dt);
}

PlayerPhysicsComponent::PlayerPhysicsComponent(Entity* p,
    const Vector2f& size)
    : PhysicsComponent(p, true, size) {
    _size = sv2_to_bv2(size, true);
    _maxVelocity = Vector2f(200.f, 400.f);
    _groundspeed = 30.f;
    _grounded = false;
    _body->SetSleepingAllowed(false);
    //Bullet items have higher-res collision detection
    _body->SetBullet(true);

    //Create leg space
    b2PolygonShape legBottom;
    legBottom.SetAsBox(_size.x * 0.5f, sf_to_bf(20.0f, true) * 0.5f, b2Vec2(0, -(_size.y / 2.0f) - sf_to_bf(10.0f, true)), 0);
    b2FixtureDef legFixture;
    legFixture.shape = &legBottom;
    legFixture.isSensor = false;
    _legFixture = _body->CreateFixture(&legFixture);
}