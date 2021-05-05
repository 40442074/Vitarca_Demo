#pragma once
#include "engine.h"

class VolumeMenuScene : public Scene {
public:
	VolumeMenuScene() = default;
	~VolumeMenuScene() override = default;

	void Load() override;

	void Update(const double& dt) override;
};