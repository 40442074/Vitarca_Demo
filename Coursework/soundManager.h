#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include "engine.h"

class SoundManager {
public:
	SoundManager() = default;

	void Load();

	void PlayButtonSound();
	void PlaySountrack();
	//void Update(const double& dt);
protected:
	sf::SoundBuffer _buffers[2];
	sf::Sound _sounds[2];
};
