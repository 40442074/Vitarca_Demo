#pragma once

#include "Box2D/Box2D.h"
#include <SFML/System/Vector2.hpp>
//#include "../Coursework/scenes/scene_tracker.h"
#include "../Coursework/game.h"

namespace Physics {
void initialise();
void shutdown();
void update(const double&);

std::shared_ptr<b2World> GetWorld();

const float physics_scale = 30.0f / sceneTracker.GetMultiplier();
const float physics_scale_inv = 1.0f / physics_scale;

const float scale = 1.0f;

//void setPhysicsScale(float f) {
//    //physics_scale = 30.0f / sceneTracker.GetMultiplier();
//    //physics_scale_inv = 1.0f / physics_scale;
//};

const sf::Vector2f bv2_to_sv2(const b2Vec2& in, bool scale = true);
const b2Vec2 sv2_to_bv2(const sf::Vector2f& in, bool scale = true);
const float sf_to_bf(const float in, bool scale = true);
const sf::Vector2f invert_height(const sf::Vector2f& in);
const bool checkFixtureCollision(b2Fixture* f1, b2Fixture* f2);
} // namespace Physics
