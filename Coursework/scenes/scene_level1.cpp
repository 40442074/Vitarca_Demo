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

static shared_ptr<Entity> player, camera, camTopE;
static shared_ptr<Texture> playertex, coneTex, cameraTex;

b2Fixture *playerBody, *cameraCone;
shared_ptr<CameraComponent> cam, camTop;
shared_ptr<SpriteComponent> camSprite, camTopSprite;
sf::Color camColour;

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

  //create camera vision cone and top of camera, apply textures and give camComponents and spritecomponents
  {
      camera = makeEntity();                                
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
      camSprite->getSprite().setTextureRect(IntRect(0, 0, 317, 324));
      camSprite->getSprite().setOrigin(165.f, 0.f);
      camSprite->getSprite().setColor(Color::Blue);
      cam = camera->addComponent<CameraComponent>(playerBody, "Vision");
      cameraCone = cam->getFixture();

      auto tempPos = camera->getPosition();
      camTopE = makeEntity();
      camTopSprite = camTopE->addComponent<SpriteComponent>();
      camTopE->setPosition(Vector2f(tempPos.x, tempPos.y - 15));
      cameraTex = make_shared<Texture>(Texture());
      cameraTex.get()->loadFromFile("res/img/enemy/camera_top.png");
      camTopSprite->setTexture(cameraTex);
      camTopSprite->getSprite().setScale(Vector2f(1.9f, 1.9f));
      camTopSprite->getSprite().setTextureRect(IntRect(0, 0, 39, 27));
      camTopSprite->getSprite().setOrigin(17.5f, 0.5f);
      camTop = camTopE->addComponent<CameraComponent>(playerBody, "Top");
    
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

  camColour = cam->GetColour();
  camSprite->getSprite().setColor(camColour);
  Scene::Update(dt);
}

void Level1Scene::Render() {
  ls::render(Engine::GetWindow());
  spriteLoader.Render(Engine::GetWindow());
  Scene::Render();
}
