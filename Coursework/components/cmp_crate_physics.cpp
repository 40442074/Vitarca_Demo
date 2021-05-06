#include "cmp_crate_physics.h"
#include "system_physics.h"
#include <SFML/Window/Mouse.hpp>

using namespace sf;
using namespace std;

void CratePhysicsComponent::update(double dt)
{
	if (_fixture->TestPoint(Physics::sv2_to_bv2(Physics::invert_height((Vector2f)Mouse::getPosition() - Vector2f(0, 30))))
		&& Mouse::isButtonPressed(Mouse::Button::Left))
	{
		_body->SetTransform(Physics::sv2_to_bv2(Physics::invert_height((Vector2f)Mouse::getPosition() - Vector2f(0, 30))), _body->GetAngle());
	}

	PhysicsComponent::update(dt);
}

CratePhysicsComponent::CratePhysicsComponent(Entity* p, const sf::Vector2f& size) : PhysicsComponent(p, true, size, 1.0f)
{
	_size = Physics::sv2_to_bv2(size, true);

	_body->SetTransform(_body->GetPosition(), 1);
}