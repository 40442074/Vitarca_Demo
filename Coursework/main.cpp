#include "engine.h"
#include "game.h"

using namespace std;

extern int gameX = 1920;
extern int gameY = 1080;

MenuScene menu;
Level1Scene level1;
Level2Scene level2;
Level3Scene level3;

int main() {
	Engine::Start(gameX, gameY, "Vitarca", &menu);
}