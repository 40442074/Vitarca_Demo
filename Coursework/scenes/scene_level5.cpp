#include "scene_level5.h"
#include "../components/cmp_player_physics.h"
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

//#include "../components/cmp_text.h"
//#include "../components/cmp_button.h"

using namespace std;
using namespace sf;

static shared_ptr<Player> player;
static shared_ptr<Enemy> enemy;
static shared_ptr<Crate> crate;
static shared_ptr<Texture> playertex;

//Pause menu
static shared_ptr<PauseMenu> pauseMenu;

void Level5Scene::Load() {
    sceneTracker.SetPhysics(30.0f / sceneTracker.GetMultiplier());

    cout << " Scene 5 Load" << endl;
    ls::loadLevelFile("res/level5.txt", 60.0f * sceneTracker.GetMultiplier());
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
    cout << " Scene 5 Load Done" << endl;

   

    //Create test crate
    {
        crate = makeEntityChild<Crate>();
        crate->setPosition(Vector2f(1000.0f * sceneTracker.GetMultiplier(), 100.0f * sceneTracker.GetMultiplier()));
        crate->load(player.get());
    }
    setLoaded(true);
}

void Level5Scene::UnLoad() {
    cout << "Scene 5 Unload" << endl;

    player.reset();
    enemy.reset();
    crate.reset();
    ls::unload();
    Scene::UnLoad();

    hasUnloaded = true;
}

void Level5Scene::Update(const double& dt) {
    pauseMenu->Update(dt);

    if (!pauseMenu->GetPaused())  //if the game isnt paused
    {
        pauseMenu->setVisible(false);    //set the pause menu invisible     
        pauseMenu->SetPaused("NotPaused"); //lock buttons from being activated
        //do update
        if (ls::getTileAt(player->getPosition()) == ls::END) {
            sceneTracker.SetLevelComplete(4, true);
            Engine::ChangeScene((Scene*)&level6);
        }
        Scene::Update(dt);
    }
    else//if the game is paused
    {
        pauseMenu->setVisible(true); //set pause menu visible
        pauseMenu->SetPaused("Paused"); //allow buttons to be clicked
    }
  
}

void Level5Scene::Render() {
    ls::render(Engine::GetWindow());
    spriteLoader.Render(Engine::GetWindow());
    Scene::Render();
}
