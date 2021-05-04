#include "engine.h"
//#include "game.h"
#include "scenes/scene_menu.h"

using namespace std;

MenuScene menu;
//Level1Scene level1;
//Level2Scene level2;
//Level3Scene level3;

int main() {
	Engine::Start(1280, 720, "Platformer", &menu);
}

//void Load() {
//    /*   for (int i = 0; i < 4; i++)               moved to pacman.cpp
//       {
//           Ghost* gho = new Ghost();
//           shared_ptr<Ghost> lul = shared_ptr<Ghost>(gho);
//
//           em.list.push_back(lul);
//       }
//       Player* player = new Player();
//
//       shared_ptr<Player> play = shared_ptr<Player>(player);
//       em.list.push_back(play);*/
//
//       //instantiating the scenes
//    gameScene.reset(new GameScene());
//    menuScene.reset(new MenuScene());
//    gameScene->load();
//    menuScene->load();
//
//    //levelScenes.reset(new LvlScenes());
//    //levelScenes->load();
//    ////lvl1Scene.reset(new Level1());
//    ////lvl2Scene.reset(new Level2());
//    ////lvl1Scene->load();
//    ////lvl2Scene->load();
//    //start at main menu
//    activeScene = menuScene;
//}
//
//void Update() {
//    static Clock clock;
//    float dt = clock.restart().asSeconds();
//    activeScene->update(dt);
//}
//
//void Render(RenderWindow& window) {
//    activeScene->render();
//    //flush to screen
//    Renderer::render();
//}
//
//int main(){
//  sf::RenderWindow window(sf::VideoMode(1280, 720), "Vitarca", sf::Style::Titlebar | sf::Style::Close);
//  static Clock clock;
//  float dt = clock.restart().asSeconds();
//  Load();
//  Renderer::initialise(window);
//  while (window.isOpen()){
//      sf::Event event;
//      while (window.pollEvent(event)){
//      if (event.type == sf::Event::Closed){
//        window.close();
//      }
//    }
//    Update();
//    window.clear();
//    Render(window);
//    window.display();
//  }
//  return 0;
//}
//
