#pragma once
#include "engine.h"

class LevelMenuScene : public Scene {
public:
	LevelMenuScene() = default;
	~LevelMenuScene() override = default;

	void Load() override;

	void Update(const double& dt) override;
};