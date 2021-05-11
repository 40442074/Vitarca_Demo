//#include "scene_level_select.h"
#include "../components/cmp_text.h"
#include "../components/cmp_button.h"
#include "../game.h"
#include <SFML/Window/Keyboard.hpp>
#include <iostream>


using namespace std;
using namespace sf;

std::shared_ptr<Entity> levelButtons[8];
std::string levelText[8] = { "Level-1", "Level-2", "Level-3", "Level-4", "Level-5", "Level-6", "Level-7", "Back to Main Menu" };

void LevelMenuScene::Load() {
	sceneTracker.ReadFromFile(); //calls a read to check which levels have been unlocked via savedata

	for (int i = 0; i < 8; i++) {

		levelButtons[i] = makeEntity();
		levelButtons[i]->addComponent<ButtonComponent>("PressStart2P-Regular.ttf", 48, Color::Blue, 
			Vector2f(Engine::getWindowSize().x / 6, Engine::getWindowSize().y / 3 + Engine::getWindowSize().y / 10 * i), "LevelSelect", levelText[i]);
		levelButtons[i]->setPosition(Vector2f(200, 200 * i));

		if (i == 7)
		{
			levelButtons[i] = makeEntity();
			levelButtons[i]->addComponent<ButtonComponent>("PressStart2P-Regular.ttf", 48, Color::Blue,
				Vector2f(Engine::getWindowSize().x / 2 + 100, Engine::getWindowSize().y / 3), "LevelSelect", levelText[i]);
			levelButtons[i]->setPosition(Vector2f(200, 200 * i));
		}
		else
		{
			levelButtons[i] = makeEntity();
			levelButtons[i]->addComponent<ButtonComponent>("PressStart2P-Regular.ttf", 48, Color::Blue,
				Vector2f(Engine::getWindowSize().x / 6, Engine::getWindowSize().y / 3 + Engine::getWindowSize().y / 10 * i), "LevelSelect", levelText[i]);
			levelButtons[i]->setPosition(Vector2f(200, 200 * i));
		}
	}
	setLoaded(true);
}

void LevelMenuScene::Update(const double& dt) {
	if (sf::Keyboard::isKeyPressed(Keyboard::Space)) {
		Engine::ChangeScene(&level1);
	}

	gManager.Render();
	Scene::Update(dt);
}