#include "cmp_camera.h"
#include <iostream>

using namespace sf;
using namespace std;

void CameraComponent::update(double dt) {	//needs to sentry back and forth and then detect if comes into contact with player
	static float angle = 0.f;
	angle += 0.5f * dt;

	//_parent->setRotation(0.f + sin(angle) * 45.f);
	if (_tag == "Vision")
	{
		_body->SetTransform(_body->GetPosition(), 0.f + sin(angle) /** 45.f*/);
		_parent->setPosition(Physics::invert_height(Physics::bv2_to_sv2(_body->GetPosition())));
		_parent->setRotation(-(180 / b2_pi) * _body->GetAngle());

		if (b2TestOverlap(_playerBodyFixture->GetShape(), 0, _fixture->GetShape(), 0, _playerBodyFixture->GetBody()->GetTransform(), _body->GetTransform()))
		{
			//cout << "player and camera overlap!!";
			_colour.r = 255;
			_colour.g = 0;
		}
		else
		{
			_colour.r = 0;
			_colour.g = 255;
		}
	}
	else if(_tag == "Top")
	{
		_parent->setRotation(0.f + sin(angle) * -45.f);
	}

}

void CameraComponent::SetColour(sf::Color c) {
	c.r = _colour.r;
	c.g = _colour.g;
	c.b = _colour.b;
	
};

sf::Color CameraComponent::GetColour() {
	return _colour;
}

b2Fixture* CameraComponent::getFixture() {
	return _fixture;
}

CameraComponent::CameraComponent(Entity* p, b2Fixture *pb, std::string tag) : Component(p) {

	_tag = tag;

	_playerBodyFixture = pb;

	b2BodyDef BodyDef;
	BodyDef.type = b2_dynamicBody;
	BodyDef.position = Physics::sv2_to_bv2(Physics::invert_height(p->getPosition()));
	// Create the body
	_body = Physics::GetWorld()->CreateBody(&BodyDef);
	_body->SetActive(true);

	//Create collision cone fixture
	b2PolygonShape cone;
	b2Vec2 points[4] = { Physics::sv2_to_bv2(Vector2f(22, 0), true), Physics::sv2_to_bv2(Vector2f(-22, 0), true), Physics::sv2_to_bv2(Vector2f(-100, -332), true),  Physics::sv2_to_bv2(Vector2f(100, -332), true) };
	cone.Set(points, 4);
	b2FixtureDef coneFixture;
	coneFixture.friction = 0.0f;
	coneFixture.restitution = .0;
	coneFixture.shape = &cone;
	coneFixture.isSensor = true;
	_fixture = _body->CreateFixture(&coneFixture);

	_body->SetGravityScale(0.f);
}