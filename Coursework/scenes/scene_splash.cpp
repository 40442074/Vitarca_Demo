#include "scene_splash.h"
#include "../components/cmp_text.h"
#include "../components/cmp_button.h"
#include "../game.h"
#include <SFML/Window/Keyboard.hpp>
#include <iostream>


using namespace std;
using namespace sf;

void SplashScene::Load() {
	sounds.Load();
	sounds.PlaySoundtrack();
	gManager.Load();
	setLoaded(true);
}

void SplashScene::Update(const double& dt) {
	//Simulate long loading times
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	cout << " Splash Load Done" << endl;
	Engine::ChangeScene(&menu);
	Scene::Update(dt);
}