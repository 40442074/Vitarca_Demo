#pragma once
#include "../../lib_engine/engine.h"

class SceneTracker{
public:
	SceneTracker() = default;

	void Load();

	void Update(const double& dt);

	void SetWidthHeight(int width, int height);
	float GetWidth();
	float GetHeight();
	void SetWindowView();
	float GetMultiplier();
	float GetPhysics();
	void SetPhysics(float f);
protected:
	float xWidth = 1920;
	float yHeight = 1080;
	float multiplier = 1.0f;
	float _physicsScale;
};