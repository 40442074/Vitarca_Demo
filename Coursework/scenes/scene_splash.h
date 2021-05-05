#pragma once
#include "engine.h"

class SplashScene : public Scene {
public:
	SplashScene() = default;
	//~SplashScene() override = default;

	void Load() override;

	void Update(const double& dt) override;
};