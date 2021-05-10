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
	void InitialiseLevelComplete();
	std::vector<bool> GetLevelComplete();
	void SetLevelComplete(int position, bool f);
	void ClearLevelComplete();
	float GetPhysics();
	void SetPhysics(float f);
	void WriteToFile();
	void createDir(const char* path);
protected:
	float xWidth = 1920;
	float yHeight = 1080;
	float multiplier = 1.0f;
	std::vector<bool> levelsComplete;
	float _physicsScale;
	std::string AppDataPath;
};