#include "scene_level1.h"
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
static shared_ptr<Enemy> enemy;
static shared_ptr<Crate> crate;
static shared_ptr<Entity> camera, camTopE;
static shared_ptr<Texture> playertex, coneTex, cameraTex, cratetex;

static shared_ptr<CameraComponent> cam;
static shared_ptr<SpriteComponent> camSprite, camTopSprite;

//Pause menu
static shared_ptr<PauseMenu> pauseMenu;

void Level1Scene::Load() {
    sceneTracker.SetPhysics(30.0f / sceneTracker.GetMultiplier());

    cout << " Scene 1 Load" << endl;
    ls::loadLevelFile("res/level1.txt", 60.0f * sceneTracker.GetMultiplier());
    spriteLoader.ReadSpriteSheet();
    spriteLoader.Load();

    auto ho = Engine::getWindowSize().y - (ls::getHeight() * 60.f);
    ls::setOffset(Vector2f(0, 0));

    hasUnloaded = false;

    // Create player
    {
        player = makeEntityChild<Player>();
        player->setPosition(ls::getTilePosition(ls::findTiles(ls::START)[0]) + Vector2f(120.0f, 20.0f));
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

    //Simulate long loading times
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    cout << " Scene 1 Load Done" << endl;

    setLoaded(true);
}

void Level1Scene::UnLoad() {
    cout << "Scene 1 Unload" << endl;

    player.reset();
    ls::unload();
    Scene::UnLoad();

    hasUnloaded = true;
}

void Level1Scene::Update(const double& dt) {
    pauseMenu->Update(dt);

    if (!pauseMenu->GetPaused())  //if the game isnt paused
    {
        pauseMenu->setVisible(false);    //set the pause menu invisible     
        pauseMenu->SetPaused("NotPaused"); //lock buttons from being activated
        //do update
        if (ls::getTileAt(player->getPosition()) == ls::END) {
            sceneTracker.SetLevelComplete(0, true);
            Engine::ChangeScene((Scene*)&level2);            
        }
        Scene::Update(dt);
    }
    else//if the game is paused
    {
        pauseMenu->setVisible(true); //set pause menu visible
        pauseMenu->SetPaused("Paused"); //allow buttons to be clicked
    }
}

void Level1Scene::Render() {
    ls::render(Engine::GetWindow());
    spriteLoader.Render(Engine::GetWindow());
    Scene::Render();
}
