#pragma once
#include "engine.h"

class ResMenuScene : public Scene {
public:
	ResMenuScene() = default;
	~ResMenuScene() override = default;

	void Load() override;

	void Update(const double& dt) override;
};