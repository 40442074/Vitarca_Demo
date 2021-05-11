#include "soundManager.h"

using namespace std;
using namespace sf;


void SoundManager::Load() {		//creates sound buffers to load sound effects for use
	for (int i = 0; i < 4; i++)
	{
		_buffers[0].loadFromFile("res/sounds/button_click.wav");
		_buffers[1].loadFromFile("res/sounds/playerwalk.wav");
		_buffers[2].loadFromFile("res/sounds/enemywalk.wav");
		_buffers[3].loadFromFile("res/sounds/cratedrag.wav");
		
		//_buffers[1].loadFromFile("res/sounds/soundtrack_01.wav");
		
		_sounds[i].setBuffer(_buffers[i]);
	}
	
	_music.openFromFile("res/sounds/soundtrack.ogg"); //loads music to be played
}

void SoundManager::PlayButtonSound()
{
	_sounds[0].play(); //causes the sound effect to be played
}
void SoundManager::PlayPwalkSound()
{
	if (_sounds[1].Playing == false)
	{
		_sounds[1].play(); //causes the sound effect to be played
	}
}
void SoundManager::PlayEWalkSound()
{
	if (_sounds[2].Playing == false)
	{
		_sounds[2].play(); //causes the sound effect to be played
	}
}
void SoundManager::PlayCDragSound()
{
	if (_sounds[3].Playing == false)
	{
		_sounds[3].play(); //causes the sound effect to be played
	}
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
