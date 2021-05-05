#include "soundManager.h"
#include "game.h"

using namespace std;
using namespace sf;

void SoundManager::Load() {

	_buffer.loadFromFile("button_click.wav");
	//_sound.setBuffer(_buffer);
}