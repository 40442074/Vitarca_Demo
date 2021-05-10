#include "scene_level1.h"
#include "../components/cmp_player_physics.h"
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

#include "../components/cmp_text.h"
#include "../components/cmp_button.h"

using namespace std;
using namespace sf;

static shared_ptr<Player> player;
static shared_ptr<Enemy> enemy;
static shared_ptr<Crate> crate;
static shared_ptr<Entity> camera, camTopE;
static shared_ptr<Texture> playertex, coneTex, cameraTex, cratetex;

static shared_ptr<CameraComponent> cam;
static shared_ptr<SpriteComponent> camSprite, camTopSprite;
sf::Color camColour;

bool hasUnloaded;

//Pause menu
shared_ptr<Entity> testButtons[3];
std::string pauseText[3] = { "Resume", "Restart Level", "Back to Main Menu" };
bool pthis, plast, isPaused;

static shared_ptr<Texture> pauseTex;
static shared_ptr<Entity> pauseTexE;
static shared_ptr<SpriteComponent> pauseTexS;

void Level1Scene::Load() {
    sceneTracker.SetPhysics(30.0f / sceneTracker.GetMultiplier());

    cout << " Scene 1 Load" << endl;
    ls::loadLevelFile("res/level1.txt", 60.0f * sceneTracker.GetMultiplier());
    spriteLoader.ReadSpriteSheet();
    spriteLoader.Load();

    auto ho = Engine::getWindowSize().y - (ls::getHeight() * 60.f);
    ls::setOffset(Vector2f(0, 0));

    //pause code
    isPaused = false;
    plast = false;
    pthis = false;
    hasUnloaded = false;

    // Create player
    {
        player = makeEntityChild<Player>();
        player->setPosition(ls::getTilePosition(ls::findTiles(ls::START)[0]) + Vector2f(50.0f, 20.0f));
        player->load();
    }

    //Create test enemy
    {
        enemy = makeEntityChild<Enemy>();
        enemy->setPosition(Vector2f(1020.0f, 360.0f));
        enemy->load();
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

    //Simulate long loading times
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    cout << " Scene 1 Load Done" << endl;

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

    //Create test crate
    {
        crate = makeEntityChild<Crate>();
        crate->setPosition(Vector2f(1000.0f * sceneTracker.GetMultiplier(), 100.0f * sceneTracker.GetMultiplier()));
        crate->load(player->getBody());
    }

    //Pause Menu load
    for (int i = 0; i < 3; i++)
    {
        testButtons[i] = makeEntity();
        testButtons[i]->addComponent<ButtonComponent>("PressStart2P-Regular.ttf", 48, Color::Blue, Vector2f(Engine::getWindowSize().x / 6, Engine::getWindowSize().y / 3 + Engine::getWindowSize().y / 10 * i), "Pause", pauseText[i]);
        testButtons[i]->GetCompatibleComponent<ButtonComponent>()[0]->SetButtonType("NotPaused");
    }
  
    for (int i = 0; i < 3; i++)
    {
        testButtons[i]->setVisible(false);
    }

    pauseTexE = makeEntity();
    pauseTexS = pauseTexE->addComponent<SpriteComponent>();
    pauseTex = make_shared<Texture>(Texture());
    pauseTex.get()->loadFromFile("res/img/menu/pause_BG.png");
    pauseTexS->setTexture(pauseTex);
    pauseTexE->setVisible(false);
    setLoaded(true);
}

void Level1Scene::UnLoad() {
    cout << "Scene 1 Unload" << endl;

    player.reset();
    enemy.reset();
    crate.reset();
    ls::unload();
    camera.reset();
    camTopE.reset();
    camSprite.reset();
    cam.reset();
    camTopSprite.reset();
    pauseTexS.reset();
    pauseTexE.reset();
    for (int i = 0; i < 3; i++)
    {
        //testButtons[i].reset();
    }
    Scene::UnLoad();

    hasUnloaded = true;
}

void Level1Scene::Update(const double& dt) {

    if (ls::getTileAt(player->getPosition()) == ls::END) {
        Engine::ChangeScene((Scene*)&level2);
        sceneTracker.SetLevelComplete(0, true);
    }

    if (Keyboard::isKeyPressed(Keyboard::P)) //pause menu
        pthis = true;
    else
        plast = false;

    if (pthis && !plast) 
    {  
        isPaused = true;
    }

    if (!isPaused)
    {
        Scene::Update(dt);  
    }
    else
    {
        for (int i = 0; i < 3; i++)
        {
            if(!testButtons[i]->isVisible())
                testButtons[i]->setVisible(true);
            if(!hasUnloaded)
                pauseTexE->setVisible(true);

            testButtons[i]->GetCompatibleComponent<ButtonComponent>()[0]->SetButtonType("Paused");
            testButtons[i]->update(dt);
        } 
        //RESUME BELOW
        auto t = testButtons[0].get()->get_components<ButtonComponent>();
        auto b = t[0]->GetButtonType();

        if (b == "NotPaused")
        {
            isPaused = false;
            testButtons[0]->GetCompatibleComponent<ButtonComponent>()[0]->SetButtonType("Paused");
            for (int i = 0; i < 3; i++)
            {
                testButtons[i]->setVisible(false);
                if(i > 0)
                    testButtons[i]->GetCompatibleComponent<ButtonComponent>()[0]->SetButtonType("NotPaused");
            }
            pauseTexE->setVisible(false);       
        }
    }
  
    if (!hasUnloaded)
    {
        camColour = cam->GetColour();
        camSprite->getSprite().setColor(camColour);
    }

    pthis = plast;

}

void Level1Scene::Render() {
    ls::render(Engine::GetWindow());
    spriteLoader.Render(Engine::GetWindow());
    Scene::Render();
}
