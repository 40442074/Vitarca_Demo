#include "scene_res.h"
#include "../components/cmp_text.h"
#include "../components/cmp_button.h"
#include "../game.h"
#include <SFML/Window/Keyboard.hpp>
#include <iostream>
#include "../scenes/scene_tracker.h"

using namespace std;
using namespace sf;

std::shared_ptr<Entity> resButtons[1];
std::string resText[5] = { "Resolution", "1920 x 1080", "1280 x 720", "640 x 480", "Back to Options" };

void ResMenuScene::Load() {
	for (int i = 0; i < 5; i++)
	{
		resButtons[i] = makeEntity();
		resButtons[i]->addComponent<ButtonComponent>("PressStart2P-Regular.ttf", 48, Color::Blue,
			Vector2f(Engine::getWindowSize().x / 6, Engine::getWindowSize().y / 3 + Engine::getWindowSize().y / 10 * i), "res", resText[i]);	
	}
}

void ResMenuScene::Update(const double& dt) {
	gManager.Render();
	Scene::Update(dt);
}