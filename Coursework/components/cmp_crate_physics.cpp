#include "cmp_crate_physics.h"
#include "system_physics.h"
#include <SFML/Window/Mouse.hpp>

using namespace sf;
using namespace std;

void CratePhysicsComponent::update(double dt)
{
	if (_fixture->TestPoint(Physics::sv2_to_bv2((Vector2f)Mouse::getPosition())))
	{
		cout << "mouse is over crate :)";
	}

	PhysicsComponent::update(dt);
}

CratePhysicsComponent::CratePhysicsComponent(Entity* p, const sf::Vector2f& size) : PhysicsComponent(p, true, size)
{
	_size = Physics::sv2_to_bv2(size, true);
}