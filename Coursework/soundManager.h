#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Audio/Music.hpp>
#include "engine.h"

class SoundManager {
public:
	SoundManager() = default;

	void Load();

	void PlayButtonSound();
	void PlaySoundtrack();
	float GetSoundVolume();
	float GetMusicVolume();
	void SetMusicVolume(float vol);
	void SetSoundVolume(float vol);

	//void Update(const double& dt);
protected:
	sf::SoundBuffer _buffers[1];
	sf::Sound _sounds[1];
	sf::Music _music;
};
