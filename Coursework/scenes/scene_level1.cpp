#include "scene_level1.h"
#include "../components/cmp_player_physics.h"
#include "../components/cmp_sprite.h"
#include "../components/cmp_camera.h"
#include "../game.h"
#include <LevelSystem.h>
#include <iostream>
#include <thread>
#include "../BGSpriteLoader.h"


using namespace std;
using namespace sf;

static shared_ptr<Entity> player, camera;
static shared_ptr<Texture> playertex, cameraTex;

b2Fixture *playerBody, *cameraCone;
//PhysicsComponent* playerBody, *cameraCone;

void Level1Scene::Load() {
  cout << " Scene 1 Load" << endl;
  ls::loadLevelFile("res/level1.txt", 60.0f);
  spriteLoader.ReadSpriteSheet();
  spriteLoader.Load();

  auto ho = Engine::getWindowSize().y - (ls::getHeight() * 40.f);
  ls::setOffset(Vector2f(0, 0));

  // Create player
  {
    player = makeEntity();
    player->setPosition(ls::getTilePosition(ls::findTiles(ls::START)[0]) + Vector2f(0, 20.0f));
    auto s = player->addComponent<SpriteComponent>();
    playertex = make_shared<Texture>(Texture());
    playertex.get()->loadFromFile("res/img/player_spritesheet.png");
    s->setTexture(playertex);
    s->getSprite().setTextureRect(IntRect(0, 0, 27, 48));
    s->getSprite().setOrigin(13.5f, 24.f);

    auto p = player->addComponent<PlayerPhysicsComponent>(Vector2f(27.f, 48.f));
    playerBody = p.get()->getFixture();
  }

  // Add physics colliders to level tiles.
  {
    auto walls = ls::findTiles(ls::WALL);
    for (auto w : walls) {
      auto pos = ls::getTilePosition(w);
      pos += Vector2f(30.f, 30.f); //offset to center
      auto e = makeEntity();
      e->setPosition(pos);
      e->addComponent<PhysicsComponent>(false, Vector2f(60.f, 60.f));
    }
  }

  //Simulate long loading times
  std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  cout << " Scene 1 Load Done" << endl;

  //create camera
  {
      camera = makeEntity();                                
      //get position of cam from spritesheet               
      auto camTiles = ls::findTiles(ls::CAMERA3);

      for (auto c : camTiles) {
          auto camPos = ls::getTilePosition(c);
          camPos += Vector2f(60.f, 60.f); //offset to center
          camera->setPosition(camPos);
      }

      auto s = camera->addComponent<SpriteComponent>();
      cameraTex = make_shared<Texture>(Texture());
      cameraTex.get()->loadFromFile("res/img/enemy/camera_vision.png");

      s->setTexture(cameraTex);
      s->getSprite().setTextureRect(IntRect(0, 0, 317, 324));
      
      s->getSprite().setOrigin(165.f, 0.f);
      auto c = camera->addComponent<CameraComponent>();
      cameraCone = c.get()->getFixture();
  }

  setLoaded(true);
}

void Level1Scene::UnLoad() {
  cout << "Scene 1 Unload" << endl;
  player.reset();
  ls::unload();
  Scene::UnLoad();
}

void Level1Scene::Update(const double& dt) {

  if (ls::getTileAt(player->getPosition()) == ls::END) {
    Engine::ChangeScene((Scene*)&level2);
  }
  Scene::Update(dt);
}

void Level1Scene::Render() {
  ls::render(Engine::GetWindow());
  spriteLoader.Render(Engine::GetWindow());
  Scene::Render();
}
