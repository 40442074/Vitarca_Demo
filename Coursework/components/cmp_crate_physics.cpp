#include "cmp_crate_physics.h"
#include "system_physics.h"
#include <SFML/Window/Mouse.hpp>
#include "engine.h"
//#include "../scenes/scene_tracker.h"
#include "../game.h"

using namespace sf;
using namespace std;

void CratePhysicsComponent::update(double dt)
{
	auto mousepos = Physics::sv2_to_bv2(Physics::invert_height((Vector2f)Mouse::getPosition(Engine::GetWindow())));

	if (_fixture->TestPoint(mousepos) //Mouse is over crate
		&& Mouse::isButtonPressed(Mouse::Button::Left) //Left mouse is held
		&& !_beingHeld
		&& length(Physics::bv2_to_sv2(_playerBody->GetPosition() - mousepos)) < 200.0f * sceneTracker.GetMultiplier()) //Mouse is less than 200 pixels from player
	{
		_beingHeld = true;
		_player->setGrabbing(true);
	}

	if (_beingHeld)
	{
		_player->setGrabbingPos(Physics::invert_height(Physics::bv2_to_sv2(_body->GetPosition())));

		sounds.PlayCDragSound();
		if (!Mouse::isButtonPressed(Mouse::Button::Left) || length(Physics::bv2_to_sv2(_body->GetPosition() - _playerBody->GetPosition())) > 500.0 * sceneTracker.GetMultiplier())
		{
			_beingHeld = false;
			_player->setGrabbing(false);
		}

		auto normtomouse = normalize(Physics::bv2_to_sv2(mousepos - _body->GetPosition())); //Direction (normal) from box to mouse
		auto lengthtobody = (float)length(Physics::bv2_to_sv2(mousepos - _playerBody->GetPosition())); //Length from box to mouse

		if (lengthtobody < 200.0f * sceneTracker.GetMultiplier())
			_body->ApplyLinearImpulseToCenter(Physics::sv2_to_bv2(normtomouse * 5000.0f * (float)dt), true);
		else
		{
			auto playertomouse = normalize(Physics::bv2_to_sv2(mousepos - _playerBody->GetPosition())); //Direction from player to mouse
			auto goalpoint = _playerBody->GetPosition() + Physics::sv2_to_bv2(playertomouse * (200.0f * sceneTracker.GetMultiplier()));
			auto normtopoint = normalize(Physics::bv2_to_sv2(goalpoint - _body->GetPosition()));

			_body->ApplyLinearImpulseToCenter(Physics::sv2_to_bv2(normtopoint * 5000.0f * (float)dt), true);
		}
	}
	else
	{
		sounds.PauseCDragSound();
	}

	PhysicsComponent::update(dt);
}

CratePhysicsComponent::CratePhysicsComponent(Entity* p, const sf::Vector2f& size, b2Body *pb, Player *pl) : PhysicsComponent(p, true, size, 1.0f)
{
	_size = Physics::sv2_to_bv2(size, true);

	_body->SetTransform(_body->GetPosition(), 1);
	_playerBody = pb;
	_player = pl;

	_beingHeld = false;
}