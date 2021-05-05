#include "soundManager.h"

using namespace std;
using namespace sf;


void SoundManager::Load() {
	for (int i = 0; i < 1; i++)
	{
		_buffers[0].loadFromFile("res/sounds/button_click.wav");
		//_buffers[1].loadFromFile("res/sounds/soundtrack_01.wav");
		
		_sounds[i].setBuffer(_buffers[i]);
	}
	
	_music.openFromFile("res/sounds/soundtrack.ogg");
}

void SoundManager::PlayButtonSound()
{
	_sounds[0].play();
}

void SoundManager::PlaySoundtrack() {
	_music.play();
}