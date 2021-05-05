#include "scene_res.h"
#include "../components/cmp_text.h"
#include "../components/cmp_button.h"
#include "../game.h"
#include <SFML/Window/Keyboard.hpp>
#include <iostream>

using namespace std;
using namespace sf;

void ResMenuScene::Load() {


}

void ResMenuScene::Update(const double& dt) {

	gManager.Render();
	Scene::Update(dt);
}