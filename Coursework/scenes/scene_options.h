#pragma once
#include "engine.h"

class OptionsMenuScene : public Scene {
public:
	OptionsMenuScene() = default;
	~OptionsMenuScene() override = default;

	void Load() override;

	void Update(const double& dt) override;
};