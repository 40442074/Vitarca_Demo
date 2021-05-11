#include "scene_level3.h"
#include "../components/cmp_sprite.h"
#include "../components/cmp_camera.h"
#include "../components/cmp_crate_physics.h"
#include "../game.h"
#include "../CanBot.h"
#include "../Crate.h"
#include <LevelSystem.h>
#include <iostream>
#include <thread>
#include "../BGSpriteLoader.h"
#include "pause.h"

using namespace std;
using namespace sf;

static shared_ptr<Player> player;
static shared_ptr<Crate> crate;
static shared_ptr<Texture> playertex, cratetex;

//Pause menu
static shared_ptr<PauseMenu> pauseMenu;

void Level3Scene::Load() {
  sceneTracker.SetPhysics(30.0f / sceneTracker.GetMultiplier());
  cout << "Scene 3 Load" << endl;
  ls::loadLevelFile("res/level3.txt", 60.0f * sceneTracker.GetMultiplier());
  spriteLoader.ReadSpriteSheet();
  spriteLoader.Load();
  auto ho = Engine::getWindowSize().y - (ls::getHeight() * 60.f);
  ls::setOffset(Vector2f(0, 0));

  hasUnloaded = false;

  // Create player
  {
      player = makeEntityChild<Player>();
      player->setPosition(ls::getTilePosition(ls::findTiles(ls::START)[0]) + Vector2f(50.0f, 20.0f));
      player->load();
  }


  pauseMenu = makeEntityChild<PauseMenu>();
  pauseMenu->Load();
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
      crate->load(player.get());
  }

  cout << " Scene 3 Load Done" << endl;
  setLoaded(true);
}

void Level3Scene::UnLoad() {
  cout << "Scene 3 UnLoad" << endl;
  player.reset();
  crate.reset();
  ls::unload();
  Scene::UnLoad();

  hasUnloaded = true;
}

void Level3Scene::Update(const double& dt) {
    pauseMenu->Update(dt);

  const auto pp = player->getPosition();

  if (!pauseMenu->GetPaused())  //if the game isnt paused
  {
      pauseMenu->setVisible(false);    //set the pause menu invisible     
      pauseMenu->SetPaused("NotPaused"); //lock buttons from being activated
      //do update
      if (ls::getTileAt(pp) == ls::END) {
          sceneTracker.SetLevelComplete(2, true);
          Engine::ChangeScene((Scene*)&level4);
      } //else if (!player->isAlive()) {
      //  Engine::ChangeScene((Scene*)&level3);
      //}
      Scene::Update(dt);
  }
  else//if the game is paused
  {
      pauseMenu->setVisible(true); //set pause menu visible
      pauseMenu->SetPaused("Paused"); //allow buttons to be clicked
  }

}

void Level3Scene::Render() {
  ls::render(Engine::GetWindow());
  spriteLoader.Render(Engine::GetWindow());
  Scene::Render();
}
