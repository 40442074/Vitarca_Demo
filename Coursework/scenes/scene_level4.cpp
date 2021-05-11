#include "scene_level4.h"
#include "../game.h"
#include "../CanBot.h"
#include "../components/cmp_camera.h"
#include "../components/cmp_bullet.h"
#include <LevelSystem.h>
#include <iostream>
using namespace std;
using namespace sf;

static shared_ptr<Player> player;
static shared_ptr<Entity> camera, camTopE;
static shared_ptr<Texture> playertex, coneTex, cameraTex;
static shared_ptr<CameraComponent> cam;
static shared_ptr<SpriteComponent> camSprite, camTopSprite;

void Level4Scene::Load() {
  cout << "Scene 4 Load" << endl;
  ls::loadLevelFile("res/level4.txt", 40.0f);
  auto ho = Engine::getWindowSize().y - (ls::getHeight() * 40.f);
  ls::setOffset(Vector2f(0, ho));

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

  ////create camera vision cone and top of camera, apply textures and give camComponents and spritecomponents
  {
      camera = makeEntity();
      camera.get()->addTag("camera");
      //get position of cam from spritesheet               
      auto camTiles = ls::findTiles(ls::CAMERA3);

      for (auto c : camTiles) {
          auto camPos = ls::getTilePosition(c);
          camPos += Vector2f(60.f, 60.f); //offset to center
          camera->setPosition(camPos);
      }

      camSprite = camera->addComponent<SpriteComponent>();
      coneTex = make_shared<Texture>(Texture());
      coneTex.get()->loadFromFile("res/img/enemy/camera_vision.png");

      camSprite->setTexture(coneTex);
      camSprite->getSprite().setScale(Vector2f(sceneTracker.GetMultiplier(), sceneTracker.GetMultiplier()));
      camSprite->getSprite().setTextureRect(IntRect(0, 0, 317, 324));
      camSprite->getSprite().setOrigin(165.f * sceneTracker.GetMultiplier(), 0.f * sceneTracker.GetMultiplier());
      camSprite->getSprite().setColor(Color::Blue);
      cam = camera->addComponent<CameraComponent>(player.get()->getFixture(), "Vision");

      auto tempPos = camera->getPosition();
      camTopE = makeEntity();
      camTopE.get()->addTag("camtop");
      camTopSprite = camTopE->addComponent<SpriteComponent>();
      camTopE->setPosition(Vector2f(tempPos.x, tempPos.y - 15));
      cameraTex = make_shared<Texture>(Texture());
      cameraTex.get()->loadFromFile("res/img/enemy/camera_top.png");
      camTopSprite->setTexture(cameraTex);
      camTopSprite->getSprite().setScale(Vector2f(sceneTracker.GetMultiplier(), sceneTracker.GetMultiplier()));
      camTopSprite->getSprite().setTextureRect(IntRect(0, 0, 39, 27));
      camTopSprite->getSprite().setOrigin(17.5f * sceneTracker.GetMultiplier(), 0.5f * sceneTracker.GetMultiplier());
      camTopE->addComponent<CameraComponent>(player.get()->getFixture(), "Top");
  }


  cout << " Scene 4 Load Done" << endl;
  setLoaded(true);
}

void Level4Scene::UnLoad() {
  cout << "Scene 4 UnLoad" << endl;
  player.reset();
  ls::unload();
  camera.reset();
  camTopE.reset();
  camSprite.reset();
  cam.reset();
  camTopSprite.reset();
  Scene::UnLoad();
}



void Level4Scene::Update(const double& dt) {
  Scene::Update(dt);
  const auto pp = player->getPosition();
  if (ls::getTileAt(pp) == ls::END) {
    Engine::ChangeScene((Scene*)&level5);
  } /*else if (!player->isAlive()) {
    Engine::ChangeScene((Scene*)&level4);
  }*/
  
}

void Level4Scene::Render() {
  ls::render(Engine::GetWindow());
  Scene::Render();
}
