#include "cmp_crate_physics.h"
#include "system_physics.h"
#include <SFML/Window/Mouse.hpp>

using namespace sf;
using namespace std;

void CratePhysicsComponent::update(double dt)
{
	auto mousepos = Physics::sv2_to_bv2(Physics::invert_height((Vector2f)Mouse::getPosition() - Vector2f(0, 30)));

	cout << to_string(length(Physics::bv2_to_sv2(_playerBody->GetPosition() - mousepos))) + "\n";

	if (_fixture->TestPoint(mousepos) //Mouse is over crate
		&& Mouse::isButtonPressed(Mouse::Button::Left) //Left mouse is held
		&& length(Physics::bv2_to_sv2(_playerBody->GetPosition() - mousepos)) < 200.0f) //Mouse is less than 200 pixels from player
	{
		_body->SetTransform(mousepos, _body->GetAngle());
	}

	PhysicsComponent::update(dt);
}

CratePhysicsComponent::CratePhysicsComponent(Entity* p, const sf::Vector2f& size, b2Body *pb) : PhysicsComponent(p, true, size, 1.0f)
{
	_size = Physics::sv2_to_bv2(size, true);

	_body->SetTransform(_body->GetPosition(), 1);
	_playerBody = pb;
}