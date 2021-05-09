#pragma once
#include "engine.h"

class SceneTracker{
public:
	SceneTracker() = default;

	void Load();

	void Update(const double& dt);

	void SetWidthHeight(int width, int height);
	float GetWidth();
	float GetHeight();
	void SetWindowView();
protected:
	float xWidth = 1920;
	float yHeight = 1080;
};