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
	std::string GetPath();
	void createDir(const char* path);
	void ReadFromFile();
	void UpdateSaveData();
	inline bool DoesFileExist();
	void SetOverwrite(bool b);
protected:
	float xWidth = 1920;
	float yHeight = 1080;
	float multiplier = 1.0f;
	std::vector<bool> levelsComplete;
	bool overwriteSaveData = false;
	float _physicsScale;
	std::string AppDataPath;
};