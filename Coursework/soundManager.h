#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include "engine.h"

class SoundManager {
public:
	SoundManager() = default;

	void Load();

	//void Update(const double& dt);
protected:
	sf::SoundBuffer _buffer;
	sf::Sound _sound;
};
