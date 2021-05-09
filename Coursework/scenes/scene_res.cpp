#include "scene_res.h"
#include "../components/cmp_text.h"
#include "../components/cmp_button.h"
#include "../game.h"
#include <SFML/Window/Keyboard.hpp>
#include <iostream>

using namespace std;
using namespace sf;

std::shared_ptr<Entity> resButtons[1];
std::string resText[5] = { "Resolution", "1920 x 1080", "1280 x 720", "640 x 480", "Back to Options" };

void ResMenuScene::Load() {
	for (int i = 0; i < 5; i++)
	{
		resButtons[i] = makeEntity();
		resButtons[i]->addComponent<ButtonComponent>("PressStart2P-Regular.ttf", 48, Color::Blue,
			Vector2f(((Engine::getWindowSize().x / 2) - 600), (Engine::getWindowSize().y / 2 - 300) + 100 * i), "res", resText[i]);		
		//resButtons[i]->addComponent<ButtonComponent>("PressStart2P-Regular.ttf", 48, Color::Blue,
		//	Vector2f(((1920 / 2) - 600), 1080 / 2 - 100), "res", resText[i]);
	}
}

void ResMenuScene::Update(const double& dt) {
	gManager.Render();
	Scene::Update(dt);
}