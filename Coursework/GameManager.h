#include <memory>	//used code from PACMAN, whole thing
#include "scenes/scene.h"
#include <SFML/Graphics.hpp>

class GameManager{
public:
	GameManager() = default;

	void Load();

	void Render();
};