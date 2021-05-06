#pragma once
#include "ecm.h"

class CameraComponent : public Component {
public:
	void update(double dt) override;
	void render() override {}
	explicit CameraComponent(Entity* p);
	CameraComponent() = delete;
};