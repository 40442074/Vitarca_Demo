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
ControlScene controlScene;


Level1Scene level1;
Level2Scene level2;
Level3Scene level3;
Level4Scene level4;
Level5Scene level5;
Level6Scene level6;
Level7Scene level7;

SceneTracker sceneTracker; //for resolution

int main() {
	Engine::Start(sceneTracker.GetWidth(), sceneTracker.GetHeight(), "Vitarca", &splash);
}