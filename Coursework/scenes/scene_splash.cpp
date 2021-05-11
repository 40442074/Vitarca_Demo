#include "scene_splash.h"
#include "../components/cmp_text.h"
#include "../components/cmp_button.h"
#include "../game.h"
#include <SFML/Window/Keyboard.hpp>
#include <iostream>


using namespace std;
using namespace sf;

void SplashScene::Load() {
	sounds.Load();	//loads sounds for use in game
	sounds.PlaySoundtrack();
	gManager.Load();
	setLoaded(true);
}

void SplashScene::Update(const double& dt) {
	//Simulate long loading times
	std::this_thread::sleep_for(std::chrono::milliseconds(1000)); //default loading time
	cout << " Splash Load Done" << endl;
	Engine::setVsync(true); //enables vsync
	sceneTracker.InitialiseLevelComplete(); //initilaising savedata
	sceneTracker.WriteToFile(); //calls write to file mthod to create save data if it does not previously exist
	Engine::ChangeScene(&menu); //changes the current scene to the main menu
	Scene::Update(dt);
}