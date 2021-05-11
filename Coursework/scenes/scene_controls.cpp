#include "scene_controls.h"
#include "../components/cmp_text.h"
#include "../components/cmp_button.h"
#include "../game.h"
#include <SFML/Window/Keyboard.hpp>
#include <iostream>

using namespace std;
using namespace sf;

std::shared_ptr<Entity> titleButton; //creating entity components for the buttons
std::shared_ptr<Entity> controlButtons[4];
std::string controlText[4] = { "Right", "Left", "Down", "Jump" }; //the visual text for the buttons
std::shared_ptr<Entity> mapButtons[4];
std::string mapText[4] = {"d", "a", "s", "Space" };

void ControlScene::Load() {
	titleButton = makeEntity(); //positions are calculated using screen space instead of pixels for resolution scaling
	titleButton->addComponent<ButtonComponent>("PressStart2P-Regular.ttf", 48, Color::Blue,
		Vector2f(Engine::getWindowSize().x / 2 - Engine::getWindowSize().x / 10, Engine::getWindowSize().y / 3 - Engine::getWindowSize().y / 6), "controls", "Remap");

	for (int i = 0; i < 4; i++)
	{
		controlButtons[i] = makeEntity();
		controlButtons[i]->addComponent<ButtonComponent>("PressStart2P-Regular.ttf", 48, Color::Blue,
			Vector2f(Engine::getWindowSize().x / 4, Engine::getWindowSize().y / 3 + Engine::getWindowSize().y / 10 * i), "controls", controlText[i]);
	}

	for (int i = 0; i < 4; i++)
	{
		mapButtons[i] = makeEntity();
		mapButtons[i]->addComponent<ButtonComponent>("PressStart2P-Regular.ttf", 48, Color::Blue,
			Vector2f(Engine::getWindowSize().x / 2, Engine::getWindowSize().y / 3 + Engine::getWindowSize().y / 10 * i), "remappable", mapText[i]);
		mapButtons[i]->GetCompatibleComponent<ButtonComponent>()[0]->SetParentKeys();
	}
}

void ControlScene::Update(const double& dt) {
	gManager.Render();	//render the buttons on screen
	Scene::Update(dt);
}