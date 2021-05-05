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
	void SetVolume(float vol);
	float GetVolume();
	//void Update(const double& dt);
protected:
	sf::SoundBuffer _buffers[1];
	sf::Sound _sounds[1];
	sf::Music _music;
};
