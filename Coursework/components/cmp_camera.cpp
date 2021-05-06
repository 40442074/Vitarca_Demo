#include "cmp_camera.h"
#include <iostream>

using namespace sf;
using namespace std;

void CameraComponent::update(double dt) {	//needs to sentry back and forth and then detect if comes into contact with player
	static float angle = 0.f;
	angle += 1.f * dt;

	//_parent->setRotation(0.f + sin(angle) * 45.f);
	//_body->SetAngularVelocity(0.f + sin(angle) * 45.f);
	_body->SetTransform(_body->GetPosition(), 0.f + sin(angle) /** 45.f*/);
	_parent->setPosition(Physics::invert_height(Physics::bv2_to_sv2(_body->GetPosition())));
	_parent->setRotation(-(180 / b2_pi) * _body->GetAngle());


	//intersect code -- if player fixture intersects cone fixture. color::red
	//b2Fixture playerBody;

	if (b2TestOverlap(_playerBodyFixture->GetShape(), 0, _fixture->GetShape(), 0, _playerBodyFixture->GetBody()->GetTransform(), _body->GetTransform()))
	{
		cout << "player and camera overlap!!";
	}
}

b2Fixture* CameraComponent::getFixture() {
	return _fixture;
}

CameraComponent::CameraComponent(Entity* p, b2Fixture *pb) : Component(p) {

	_playerBodyFixture = pb;

	b2BodyDef BodyDef;
	// Is Dynamic(moving), or static(Stationary)
	BodyDef.type = b2_dynamicBody;
	BodyDef.position = Physics::sv2_to_bv2(Physics::invert_height(p->getPosition()));

	// Create the body
	_body = Physics::GetWorld()->CreateBody(&BodyDef);
	_body->SetActive(true);
	//_direction = Vector2f(1.0f, 0);
	//_speed = 100.0f;
	//_sprite = sprite;
	//Create leg space
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