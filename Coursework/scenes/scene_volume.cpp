#include "scene_volume.h"
#include "../components/cmp_text.h"
#include "../components/cmp_button.h"
#include "../game.h"
#include <SFML/Window/Keyboard.hpp>
#include <iostream>

using namespace std;
using namespace sf;

std::shared_ptr<Entity> soundVol[5];
std::shared_ptr<Entity> musicVol[5];
std::string soundText[5] = { "Sound Effects", "-", "0", "+", "Back to Options" };

void VolumeMenuScene::Load() {
	
	for(int i = 0; i < 4; i++)
	{
		soundVol[i] = makeEntity();
		if (i < 1) //if button is the title
		{
			soundVol[i]->addComponent<ButtonComponent>("PressStart2P-Regular.ttf", 48, Color::Blue,
				Vector2f(((Engine::getWindowSize().x / 2) - 600), Engine::getWindowSize().y / 2 - 100), "Sound", soundText[i]);
		}
		else
		{
			if (i == 2) //if button is the number
			{
				soundVol[i]->addComponent<ButtonComponent>("PressStart2P-Regular.ttf", 48, Color::Blue,
					Vector2f(((Engine::getWindowSize().x / 2) - 200) + i * 150, Engine::getWindowSize().y / 2 - 100), "SoundNumber", soundText[i]);
			}
			else
			{
				soundVol[i]->addComponent<ButtonComponent>("PressStart2P-Regular.ttf", 48, Color::Blue,
					Vector2f(((Engine::getWindowSize().x / 2) - 200) + i * 150, Engine::getWindowSize().y / 2 - 100), "Sound", soundText[i]);
			}
			
		}
	}

	for (int i = 0; i < 5; i++)
	{
		musicVol[i] = makeEntity();
		if (i < 1) //if button is the title
		{
			musicVol[i]->addComponent<ButtonComponent>("PressStart2P-Regular.ttf", 48, Color::Blue,
				Vector2f(((Engine::getWindowSize().x / 2) - 600), Engine::getWindowSize().y / 2), "Music", "Music");
		}
		else if (i == 5) //back to options button
		{
			musicVol[i]->addComponent<ButtonComponent>("PressStart2P-Regular.ttf", 48, Color::Blue,
				Vector2f(((Engine::getWindowSize().x / 2) - 400), Engine::getWindowSize().y / 2 + 350), "Music", soundText[i]);
		}
		else
		{
			if (i == 2) //if button is the number
			{
				musicVol[i]->addComponent<ButtonComponent>("PressStart2P-Regular.ttf", 48, Color::Blue,
					Vector2f(((Engine::getWindowSize().x / 2) - 200) + i * 150, Engine::getWindowSize().y / 2), "MusicNumber", soundText[i]);
			}
			else
			{
				musicVol[i]->addComponent<ButtonComponent>("PressStart2P-Regular.ttf", 48, Color::Blue,
					Vector2f(((Engine::getWindowSize().x / 2) - 200) + i * 150, Engine::getWindowSize().y / 2), "Music", soundText[i]);
			}

		}
	}
}

void VolumeMenuScene::Update(const double& dt) {

	gManager.Render();
	Scene::Update(dt);
}