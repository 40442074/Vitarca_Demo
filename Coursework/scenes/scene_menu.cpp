#include "scene_menu.h"
#include "../components/cmp_text.h"
#include "../components/cmp_button.h"
#include "../game.h"
#include <SFML/Window/Keyboard.hpp>
#include <iostream>

using namespace std;
using namespace sf;

int buttonCount = 5;
std::shared_ptr<Entity> buttons[3];
string buttonText[5] = { "Start Game", "Level Select", "Options", "Restart Game", "Exit Game" };

void MenuScene::Load() {
    cout << "Menu Load \n";

    for (int i = 0; i < buttonCount; i++){
        buttons[i] = makeEntity();
        buttons[i]->addComponent<ButtonComponent>("PressStart2P-Regular.ttf", 48, Color::Blue, Vector2f((Engine::getWindowSize().x / 2) - 250, (100 * i) + 250), buttonText[i]);
    }
  setLoaded(true);
}

void MenuScene::Update(const double& dt) {
  // cout << "Menu Update "<<dt<<"\n";

  if (sf::Keyboard::isKeyPressed(Keyboard::Space)) {
    Engine::ChangeScene(&level1);
  }
  if (sf::Keyboard::isKeyPressed(Keyboard::P)) {
      //sounds.PlayButtonSound();
  }

  //renders menu sprite
  gManager.Render();
  Scene::Update(dt);
}