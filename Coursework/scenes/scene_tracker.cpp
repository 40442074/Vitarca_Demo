#include "scene_tracker.h"
#include "../game.h"
#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>

using namespace std;
using namespace sf;

void SceneTracker::Load() {

}

void SceneTracker::Update(const double& dt) {
}

float SceneTracker::GetWidth()
{
	return xWidth;
}

float SceneTracker::GetHeight()
{
	return yHeight;
}

void SceneTracker::SetWidthHeight(int width, int height)
{
	xWidth = width;
	yHeight = height;

	multiplier = (float)height / 1080.0f;

	SetWindowView();
}

void SceneTracker::SetWindowView() {
	auto width = GetWidth();
	auto height = GetHeight();
	sf::View view(sf::FloatRect(0, 0, width, height));
	Engine::SetWindow(view, width, height);
}

float SceneTracker::GetMultiplier() {
	return multiplier;
}

void SceneTracker::InitialiseLevelComplete() {
	for (int i = 0; i < 5; i++)
	{
		levelsComplete.push_back(false);
	}
}

std::vector<bool> SceneTracker::GetLevelComplete()
{
	return levelsComplete;
}

void SceneTracker::SetLevelComplete(int position, bool f)
{
	levelsComplete[position] = f;
}

void SceneTracker::ClearLevelComplete() {
	for (int i = 0; i < 5; i++)
	{
		levelsComplete[i] = false;
	}
}

float SceneTracker::GetPhysics() {
	return _physicsScale;
}

void SceneTracker::SetPhysics(float f)
{
	_physicsScale = f;
}

std::string SceneTracker::GetPath()
{
	char* path;
	size_t len;
	_dupenv_s(&path, &len, "APPDATA");
	AppDataPath = path;
	AppDataPath += "\\Vitarca";
	return AppDataPath;
}

void SceneTracker::WriteToFile() {
	auto path = GetPath();
	createDir(path.c_str());

	std::string newPath = AppDataPath.c_str();
	ofstream MyFile(newPath + "\\Testfile.txt");
	cout << newPath << "\\Testfile.txt" << "\n";
	MyFile << "Works";
	MyFile.flush();
	MyFile.close();
}

void SceneTracker::createDir(const char* path)
{
	CreateDirectoryA(path, NULL);
}

void SceneTracker::ReadFromFile()
{
	string textRead;
	auto path = GetPath();
	ifstream ReadFile(path + "\\Testfile.txt");

	while (getline(ReadFile, textRead)) {
		cout << textRead << "\n";
	}
}