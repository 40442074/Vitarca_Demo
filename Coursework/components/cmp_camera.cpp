#include "cmp_camera.h"

void CameraComponent::update(double dt) {	//needs to sentry back and forth and then detect if comes into contact with player
	static float angle = 0.f;
	angle += 1.f * dt;

	_parent->setRotation(0.f + sin(angle) * 45.f);
}

CameraComponent::CameraComponent(Entity* p) : Component(p) {
	//_direction = Vector2f(1.0f, 0);
	//_speed = 100.0f;
}