#pragma once
#include "engine.h"

class SceneTracker : public Scene {
public:
	SceneTracker() = default;
	~SceneTracker() override = default;

	void Load() override;

	void Update(const double& dt) override;
};