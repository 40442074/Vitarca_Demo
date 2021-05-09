#include "pause.h"
#include "../components/cmp_text.h"
#include "../components/cmp_button.h"
#include "../game.h"
#include <SFML/Window/Keyboard.hpp>
#include <iostream>
#include <vector>

using namespace std;
using namespace sf;


void PauseMenu::Load() {

	for (int i = 0; i < 3; i++) {
		_pauseButtons[i] = makeEntity();
		_pauseButtons[i]->addComponent<ButtonComponent>("PressStart2P-Regular.ttf", 48, Color::Blue, 
			Vector2f(Engine::getWindowSize().x / 6, Engine::getWindowSize().y / 3 + Engine::getWindowSize().y / 10 * i), "Pause", _pauseText[i]);
	}
	setLoaded(true);
}

void PauseMenu::Update(const double& dt) {

	gManager.Render();

	Scene::Update(dt);
}

void PauseMenu::GetPositions(sf::Vector2f positions[], int size) {
	if (size > 0)
	{
		for (int i = 0; i < size; i++)
		{
			//_positions.push_back(positions[i]);
		}
	}
	
}

void PauseMenu::ClearPositions() {
	_positions.clear();
}

std::vector<sf::Vector2f> PauseMenu::SetPositions() {
	if (_positions.size() > 0)
	{
		return _positions;
	}
	else
	{
		throw string("empty array: ");
	}
	
}

