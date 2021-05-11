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
	xWidth = width; // used with scaling of the level for resoltion
	yHeight = height;

	multiplier = (float)height / 1080.0f; //divides height by max res getting a < 1 scale factor

	SetWindowView();
}

void SceneTracker::SetWindowView() {
	auto width = GetWidth();
	auto height = GetHeight();
	sf::View view(sf::FloatRect(0, 0, width, height));	//sets the view to a specific width, height and offset
	Engine::SetWindow(view, width, height);
}

float SceneTracker::GetMultiplier() {
	return multiplier;
} //returns the multiplier for use in other scripts

void SceneTracker::InitialiseLevelComplete() {
	for (int i = 0; i < 7; i++)
	{
		levelsComplete.push_back(false);
	}
} //initialising save data vector as all false.

std::vector<bool> SceneTracker::GetLevelComplete()
{
	return levelsComplete;
}

void SceneTracker::SetLevelComplete(int position, bool f)
{
	levelsComplete[position] = f; //when completing a level, the level number and true is set to the appropriate position int eh vector
	UpdateSaveData(); //calls various methods as appropriate	
	WriteToFile();
}

void SceneTracker::UpdateSaveData()
{
	overwriteSaveData = true; //lets the write to file method know that it is safe to overwrite the save file
}

void SceneTracker::SetOverwrite(bool b)
{
	overwriteSaveData = b;				//resets the bool for overwriiting
}

void SceneTracker::ClearLevelComplete() {
	for (int i = 0; i < 7; i++)
	{
		levelsComplete[i] = false;		//clears the current progress whilst running
	}
}

float SceneTracker::GetPhysics() {
	return _physicsScale;
}

void SceneTracker::SetPhysics(float f)
{
	_physicsScale = f;
} //unused methods for adjusitng physcis scale

std::string SceneTracker::GetPath()
{
	char* path;			//gets the path to AppData
	size_t len;
	_dupenv_s(&path, &len, "APPDATA");
	AppDataPath = path;
	AppDataPath += "\\Vitarca"; //adds game name to end of folder name
	return AppDataPath;
}

void SceneTracker::WriteToFile() {
	
	if (DoesFileExist() < 1 || overwriteSaveData)     //if file doesnt exist or overwrite is permitted      
	{
		auto path = GetPath();
		createDir(path.c_str()); //calls a method to create a directory inside appdata\\roaming
		std::string newPath = AppDataPath.c_str();
		ofstream MyFile(newPath + "\\VitarcaSAVEDATA.txt"); //creates a file for savedata
		cout << newPath << "\\VitarcaSAVEDATA.txt" << "\n";
		for (const auto& e : levelsComplete) MyFile << e << "\n"; //writes the vector into the text file for level progress
		//MyFile << "Works";
		//.flush();
		MyFile.close();
		SetOverwrite(false);
	}
	else
	{
		cout << "File Already Exists!" << "\n";
	}
}

void SceneTracker::createDir(const char* path)
{
	CreateDirectoryA(path, NULL); //creates the directory using the provided path
}

void SceneTracker::ReadFromFile()
{
	if(DoesFileExist() > 0) //if file exists
	{
		levelsComplete.clear(); //clear vector
		string textRead;
		auto path = GetPath();
		ifstream ReadFile(path + "\\VitarcaSAVEDATA.txt");

		//read the text file and push into vector

		while (getline(ReadFile, textRead)) {
			//cout << "Read Lines: " << num << "\n";
			stringstream ss;
			ss << textRead;
			int num;
			ss >> num;
			levelsComplete.push_back(num);	
		}
	}

}

inline bool SceneTracker::DoesFileExist()
{
	struct stat buffer;
	auto path = GetPath() + "\\VitarcaSAVEDATA.txt"; //efficiently checks if the file exists.
	return (stat(path.c_str(), &buffer) == 0);
}