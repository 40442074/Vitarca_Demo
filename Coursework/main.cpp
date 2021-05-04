#include <SFML/Graphics.hpp>
#include "SystemRenderer.h"
#include "GameManager.h"

using namespace sf;
using namespace std;

EntityManager em;

void Load() {
    /*   for (int i = 0; i < 4; i++)               moved to pacman.cpp
       {
           Ghost* gho = new Ghost();
           shared_ptr<Ghost> lul = shared_ptr<Ghost>(gho);

           em.list.push_back(lul);
       }
       Player* player = new Player();

       shared_ptr<Player> play = shared_ptr<Player>(player);
       em.list.push_back(play);*/

       //instantiating the scenes
    gameScene.reset(new GameScene());
    menuScene.reset(new MenuScene());
    gameScene->load();
    menuScene->load();

    //levelScenes.reset(new LvlScenes());
    //levelScenes->load();
    ////lvl1Scene.reset(new Level1());
    ////lvl2Scene.reset(new Level2());
    ////lvl1Scene->load();
    ////lvl2Scene->load();
    //start at main menu
    activeScene = menuScene;
}

void Update() {
    static Clock clock;
    float dt = clock.restart().asSeconds();
    activeScene->update(dt);
}

void Render(RenderWindow& window) {
    activeScene->render();
    //flush to screen
    Renderer::render();
}

int main(){
  sf::RenderWindow window(sf::VideoMode(1920, 1080), "Vitarca");
  static Clock clock;
  float dt = clock.restart().asSeconds();
  Load();
  Renderer::initialise(window);
  while (window.isOpen()){
      sf::Event event;
      while (window.pollEvent(event)){
      if (event.type == sf::Event::Closed){
        window.close();
      }
    }
    Update();
    window.clear();
    Render(window);
    window.display();
  }
  return 0;
}

