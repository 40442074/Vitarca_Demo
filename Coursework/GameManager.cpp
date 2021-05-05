#include "GameManager.h"
#include "engine.h"

using namespace sf;
using namespace std;

Texture menuArt;
Sprite menuSprites;

void GameManager::Load() {
	if (!menuArt.loadFromFile("res/img/menu/smoke_splash.png")) {
		cerr << "Failed to load menuArt!" << std::endl;
	}
	menuSprites.setTexture(menuArt);
}

void GameManager::Render() {
	Engine::GetWindow().draw(menuSprites);
}