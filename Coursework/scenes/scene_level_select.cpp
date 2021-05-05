#include "scene_level_select.h"
#include "../components/cmp_text.h"
#include "../components/cmp_button.h"
#include "../game.h"
#include <SFML/Window/Keyboard.hpp>
#include <iostream>


using namespace std;
using namespace sf;

std::shared_ptr<Entity> levelButtons[4];
std::string levelText[4] = { "Level-1", "Level-2", "Level-3", "Back to Main Menu" };

void LevelMenuScene::Load() {
	{
		auto txt = makeEntity();
		auto t = txt->addComponent<TextComponent>(
			"Vitarca Level Select\nPress Space to Start");
		txt->setPosition(Vector2f(200, 200));
	}

	for (int i = 0; i < 4; i++) {

		levelButtons[i] = makeEntity();
		levelButtons[i]->addComponent<ButtonComponent>("PressStart2P-Regular.ttf", 48, Color::Blue, Vector2f(200, 200 * i), levelText[i]);
		levelButtons[i]->setPosition(Vector2f(200, 200 * i));
	}
	setLoaded(true);
}

void LevelMenuScene::Update(const double& dt) {
	if (sf::Keyboard::isKeyPressed(Keyboard::Space)) {
		Engine::ChangeScene(&level1);
	}

	Scene::Update(dt);
}