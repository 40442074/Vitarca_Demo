#include "Windows.h"
#include "GameManager.h"
#include "ecm.h"
#include "MyLevelSystem.h"
#include "SystemRenderer.h"
#include "BGSpriteLoader.h"
#include "button.h"

#include <string>

//have a menu that allows you to use the mouse and click on a level to then load that level and play it.
//menu with mouse support, buttons to click on, then a system to load a specific text file as the level.

using namespace sf;
using namespace std;

std::shared_ptr<Scene> gameScene;
std::shared_ptr<Scene> menuScene;
std::shared_ptr<Scene> activeScene;

std::shared_ptr<Entity> player;
std::vector<std::shared_ptr<Entity>> enemy_list;
std::vector<std::shared_ptr<Entity>> camera_list;

BGSpriteLoader bgSpriteLoader;
std::vector<Button> buttons;
int buttonCount = 3;

sf::Font font;
sf::Color white = Color(255, 255, 255, 255);

sf::RenderWindow window;
void Scene::render() { _ents.render(/*window*/); }

void Scene::update(double dt) {
	for (int i = 0; i < _ents.list.size(); i++) {
		_ents.list[i]->update(dt);
	}
}

void MenuScene::update(double dt) {
	if (Keyboard::isKeyPressed(Keyboard::Space)) {
		activeScene = gameScene;
	}
	Scene::update(dt);
	_text.setString("MainMenu");

	for (int i = 0; i < buttonCount; i++)
	{
		buttons[i].update(dt, Renderer::getWindow());
	}
}

sf::Font MenuScene::GetFont()
{
	return font;
}

void MenuScene::render() {
	for (int i = 0; i < buttonCount; i++)
	{
		buttons[i].render();
	}
	Scene::render();
}

void MenuScene::load() {
	char c[MAX_PATH];
	GetModuleFileName(NULL, c, MAX_PATH);
	string s = string(c);
	s = s.substr(0, s.find_last_of("\\/"));

	font.loadFromFile(s + "\\res\\fonts\\PressStart2P-Regular.ttf");
	////text.setPosition(Vector2f(window.getSize().x / 2, window.getSize().y / 2));

	for (int i = 0; i < buttonCount; i++)
	{
		buttons.push_back(Button());
		int val = (i + 1);
		buttons[i].load(Color(255, 0, 255, 255), 24, "Level " + to_string(val), Vector2f(200, 200 * i + 100), font);

	}
}

void GameScene::update(double dt) {
	if (Keyboard::isKeyPressed(Keyboard::Tab)) {
		activeScene = menuScene;
	}
	Scene::update(dt);

}

void GameScene::render() {
	bgSpriteLoader.Render(Renderer::getWindow());
}

//void GameScene::load() {
//	Player* player = new Player();
//	shared_ptr<Player> play = shared_ptr<Player>(player);
//	_ents.list.push_back(play);
//
//	for (int i = 0; i < 4; i++)
//	{
//		Ghost* gho = new Ghost();
//		shared_ptr<Ghost> lul = shared_ptr<Ghost>(gho);
//
//		_ents.list.push_back(lul);
//	}
//}

void GameScene::load() {
	char c[MAX_PATH];
	GetModuleFileName(NULL, c, MAX_PATH);
	string s = string(c);
	s = s.substr(0, s.find_last_of("\\/"));

	//load level
	lvlSys::loadLevelFile(s + "\\res\\test_level.txt", 60.0f);
	bgSpriteLoader.ReadSpriteSheet();
	bgSpriteLoader.Load();

	//respawn();
}