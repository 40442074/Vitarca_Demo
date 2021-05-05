#include "scene_volume.h"
#include "../components/cmp_text.h"
#include "../components/cmp_button.h"
#include "../game.h"
#include <SFML/Window/Keyboard.hpp>
#include <iostream>

using namespace std;
using namespace sf;

std::shared_ptr<Entity> volumeControl[3];
std::string volumeText[3] = { "+", "0", "-" };

void VolumeMenuScene::Load() {

	for(int i = 0; i < 3; i++)
	{
		volumeControl[i] = makeEntity();
		volumeControl[i]->addComponent<ButtonComponent>("PressStart2P-Regular.ttf", 48, Color::Blue, Vector2f(((Engine::getWindowSize().x / 2) - (i * 200)), (Engine::getWindowSize().y / 2)), volumeText[i]);
	}
}

void VolumeMenuScene::Update(const double& dt) {

	gManager.Render();
	Scene::Update(dt);
}