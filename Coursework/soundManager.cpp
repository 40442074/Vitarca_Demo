#include "soundManager.h"

using namespace std;
using namespace sf;


void SoundManager::Load() {		//creates sound buffers to load sound effects for use
	for (int i = 0; i < 1; i++)
	{
		_buffers[0].loadFromFile("res/sounds/button_click.wav");
		//_buffers[1].loadFromFile("res/sounds/soundtrack_01.wav");
		
		_sounds[i].setBuffer(_buffers[i]);
	}
	
	_music.openFromFile("res/sounds/soundtrack.ogg"); //loads music to be played
}

void SoundManager::PlayButtonSound()
{
	_sounds[0].play(); //causes the sound effect to be played
}

void SoundManager::PlaySoundtrack() {
	_music.play();
}

float SoundManager::GetSoundVolume() {
	return _sounds->getVolume();			//gets and sets volume, for use within options and volume menus
}

float SoundManager::GetMusicVolume() {
	return _music.getVolume();
}

void SoundManager::SetMusicVolume(float vol) {
	_music.setVolume(vol);
}

void SoundManager::SetSoundVolume(float vol) {
	_sounds->setVolume(vol);
}
