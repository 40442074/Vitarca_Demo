#include "engine.h"
#include "game.h"

using namespace std;

//extern int gameX = 1920;
//extern int gameY = 1080;

MenuScene menu;
SoundManager sounds;
GameManager gManager;

SplashScene splash;
LevelMenuScene levelSelect;
OptionsMenuScene optionsScene;
VolumeMenuScene volScene;
ResMenuScene resScene;
//PauseMenu pauseScene;


Level1Scene level1;
Level2Scene level2;
Level3Scene level3;

SceneTracker sceneTracker; //for resolution

int main() {
	Engine::Start(sceneTracker.GetWidth(), sceneTracker.GetHeight(), "Vitarca", &splash);
}