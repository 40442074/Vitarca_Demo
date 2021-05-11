#include "scene_level2.h"
#include "../components/cmp_sprite.h"
#include "../components/cmp_camera.h"
#include "../components/cmp_crate_physics.h"
#include "../game.h"
#include "../Player.h"
#include "../Enemy.h"
#include "../Crate.h"
#include <LevelSystem.h>
#include <iostream>
#include <thread>
#include "../BGSpriteLoader.h"
//
//#include "../components/cmp_text.h"
//#include "../components/cmp_button.h"

using namespace std;
using namespace sf;

static shared_ptr<Player> player;
static shared_ptr<Crate> crate;
static shared_ptr<Texture> playertex, cratetex;


//Pause menu
//shared_ptr<Entity> testButtons[3];
//std::string pauseText[3] = { "Resume", "Restart Level", "Back to Main Menu" };
//bool pthis, plast, isPaused;
//
//static shared_ptr<Texture> pauseTex;
//static shared_ptr<Entity> pauseTexE;
//static shared_ptr<SpriteComponent> pauseTexS;

void Level2Scene::Load() {
  cout << "Scene 2 Load" << endl;
  ls::loadLevelFile("res/level2.txt", 60.0f * sceneTracker.GetMultiplier());
  spriteLoader.ReadSpriteSheet();
  spriteLoader.Load();
  auto ho = Engine::getWindowSize().y - (ls::getHeight() * 40.f);
  ls::setOffset(Vector2f(0, ho));

  //pause code
 /* isPaused = false;
  plast = false;
  pthis = false;*/
  hasUnloaded = false;

  // Create player
  {
      player = makeEntityChild<Player>();
      player->setPosition(ls::getTilePosition(ls::findTiles(ls::START)[0]) + Vector2f(50.0f, 20.0f));
      player->load();
  }


  // Add physics colliders to level tiles.
  {
      auto walls = ls::findTiles(ls::WALL);
      for (auto w : walls) {
          auto pos = ls::getTilePosition(w);
          pos += Vector2f(30.f, 30.f); //offset to center
          auto e = makeEntity();
          e->setPosition(pos);
          e.get()->addTag("wall");
          e->addComponent<PhysicsComponent>(false, Vector2f(60.f, 60.f));
      }
  }

  //Create test crate
  {
      crate = makeEntityChild<Crate>();
      crate->setPosition(Vector2f(1000.0f * sceneTracker.GetMultiplier(), 100.0f * sceneTracker.GetMultiplier()));
      crate->load(player->getBody());
  }

  cout << " Scene 2 Load Done" << endl;
  setLoaded(true);
}

void Level2Scene::UnLoad() {
  cout << "Scene 2 UnLoad" << endl;
  player.reset();
  crate.reset();
  ls::unload();
  //pauseTexS.reset();
  //pauseTexE.reset();
  Scene::UnLoad();

  hasUnloaded = true;
}

void Level2Scene::Update(const double& dt) {
  Scene::Update(dt);
  const auto pp = player->getPosition();
  //if (ls::getTileAt(pp) == ls::END) {
  //  Engine::ChangeScene((Scene*)&level3);
  //} else if (!player->isAlive()) {
  //  Engine::ChangeScene((Scene*)&level2);
  //}
}

void Level2Scene::Render() {
  ls::render(Engine::GetWindow());
  spriteLoader.Render(Engine::GetWindow());
  Scene::Render();
}
