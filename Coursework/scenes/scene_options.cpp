#include "scene_options.h"
#include "../components/cmp_text.h"
#include "../components/cmp_button.h"
#include "../game.h"
#include <SFML/Window/Keyboard.hpp>
#include <iostream>

using namespace std;
using namespace sf;

std::shared_ptr<Entity> OptionsButtons[4];
std::string optionText[4] = {"Volume", "Resolution", "Controls", "Back to Main Menu"};

void OptionsMenuScene::Load() {

	for (int i = 0; i < 4; i++) {

		OptionsButtons[i] = makeEntity();
		OptionsButtons[i]->addComponent<ButtonComponent>("PressStart2P-Regular.ttf", 48, Color::Blue, 
			Vector2f(Engine::getWindowSize().x / 6, Engine::getWindowSize().y / 3 + Engine::getWindowSize().y / 10 * i), "Options", optionText[i]);
	}
	setLoaded(true);
}

void OptionsMenuScene::Update(const double& dt) {
	if (sf::Keyboard::isKeyPressed(Keyboard::Space)) {
		Engine::ChangeScene(&level1);
	}
	gManager.Render();
	Scene::Update(dt);
}