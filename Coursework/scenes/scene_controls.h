#pragma once
#include "engine.h"

class ControlScene : public Scene {
public:
	ControlScene() = default;
	~ControlScene() override = default;

	void Load() override;

	void Update(const double& dt) override;
};