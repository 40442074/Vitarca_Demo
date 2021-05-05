#include "scene_options.h"
#include "../components/cmp_text.h"
#include "../components/cmp_button.h"
#include "../game.h"
#include <SFML/Window/Keyboard.hpp>
#include <iostream>

using namespace std;
using namespace sf;

std::shared_ptr<Entity> OptionsButtons[4];
std::string optionText[4] = {"Volume", "Resolution", "Credits", "Back to Main Menu"};

void OptionsMenuScene::Load() {
	{
		auto txt = makeEntity();
		auto t = txt->addComponent<TextComponent>(
			"Vitarca Level Select\nPress Space to Start");
		txt->setPosition(Vector2f(200, 200));
	}

	for (int i = 0; i < 4; i++) {

		OptionsButtons[i] = makeEntity();
		OptionsButtons[i]->addComponent<ButtonComponent>("PressStart2P-Regular.ttf", 48, Color::Blue, Vector2f((Engine::getWindowSize().x / 2) - 250, (100 * i) + 250), optionText[i]);
		OptionsButtons[i]->setPosition(Vector2f(200, 200 * i));
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