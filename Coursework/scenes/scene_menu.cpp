#include "scene_menu.h"
#include "../components/cmp_text.h"
#include "../components/cmp_button.h"
#include "../game.h"
#include <SFML/Window/Keyboard.hpp>
#include <iostream>

using namespace std;
using namespace sf;

int buttonCount = 3;
std::shared_ptr<Entity> buttons[3];

void MenuScene::Load() {
    cout << "Menu Load \n";
    {
        auto txt = makeEntity();
        auto t = txt->addComponent<TextComponent>(
            "Vitarca\nPress Space to Start");
        txt->setPosition(Vector2f(200, 200));
    }
    for (int i = 0; i < buttonCount; i++){

        buttons[i] = makeEntity();

        buttons[i]->addComponent<ButtonComponent>("PressStart2P-Regular.ttf", 48, Color::Blue, Vector2f(200, 200 * i), "Level-");
        buttons[i]->setPosition(Vector2f(200, 200 * i));
     
    }
  ////auto a = makeEntity();
  ////a->setPosition(Vector2f(a->getPosition().x + 200, a->getPosition().y + 200));
  ////auto as = a->addComponent<ButtonComponent>("PressStart2P-Regular.ttf", 24, Color::Blue, "Level-1");
  //a->setPosition(Vector2f(400, 400));

  setLoaded(true);
}

void MenuScene::Update(const double& dt) {
  // cout << "Menu Update "<<dt<<"\n";

  if (sf::Keyboard::isKeyPressed(Keyboard::Space)) {
    Engine::ChangeScene(&level1);
  }

  Scene::Update(dt);
}