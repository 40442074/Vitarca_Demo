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
	soundTime = _buffers[1].getDuration();
	crateDuration = _buffers[3].getDuration();
	_sounds[1].setLoop(true);
	_sounds[3].setLoop(true);
}

void SoundManager::PlayButtonSound()
{
	_sounds[0].play(); //causes the sound effect to be played
}
void SoundManager::PlayPwalkSound()
{
	float dt = 1 / 60;	
	timeSeconds -= dt;
	if (timeSeconds <= 0.0f)
	{
		_sounds[1].play();
		timeSeconds = soundTime.asSeconds();
	}
}
void SoundManager::PlayEWalkSound()
{
	_sounds[2].setLoop(true);
	_sounds[2].play();
}
void SoundManager::PlayCDragSound()
{
	float dt = 1 / 60;
	crateTiming -= dt;
	if (crateTiming <= 0.0f)
	{
		_sounds[3].play();
		crateTiming = crateDuration.asSeconds();
	}
}

void SoundManager::PausePwalkSound()
{
	_sounds[1].pause();
}
void SoundManager::PauseEWalkSound()
{
	_sounds[2].pause();
}
void SoundManager::PauseCDragSound()
{
	_sounds[3].pause();
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
