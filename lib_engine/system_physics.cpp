
#include "system_physics.h"
#include "Box2D/Box2D.h"

using namespace std;
using namespace sf;

namespace Physics {
static shared_ptr<b2World> world;
const int32 velocityIterations = 6;
const int32 positionIterations = 2;

void initialise() {
  b2Vec2 gravity(0.0f, -10.0f);
  // Construct a world object, which will hold and simulate the rigid
  // bodies.
  world.reset(new b2World(gravity));
}

void shutdown() { world.reset(); }

void update(const double& dt) {
    world->Step((float)dt, velocityIterations, positionIterations);
}

std::shared_ptr<b2World> GetWorld() { return world; }

const Vector2f bv2_to_sv2(const b2Vec2& in, bool scale) {
  if (scale) {
    return Vector2f((in.x * sceneTracker.GetPhysics()), (in.y * sceneTracker.GetPhysics()));
  } else {
    return Vector2f(in.x, in.y);
  }
}

const b2Vec2 sv2_to_bv2(const Vector2f& in, bool scale) {
  if (scale) {
    return b2Vec2((in.x * (1.0f/ sceneTracker.GetPhysics())), (in.y * (1.0f / sceneTracker.GetPhysics())));
  } else {
    return b2Vec2(in.x, in.y);
  }
}

const float sf_to_bf(const float in, bool scale) {
    if (scale) {
        return in * (1.0f / sceneTracker.GetPhysics());
    }
    else {
        return in;
    }
}

const Vector2f invert_height(const Vector2f& in) {
  return Vector2f(in.x, 720 - in.y);
}

const bool checkFixtureCollision(b2Fixture* f1, b2Fixture* f2) {
    //auto f = f1->GetAABB(f1->GetBody().);
    return false;
}
} // namespace Physics