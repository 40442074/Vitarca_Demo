#include <memory>	//used code from PACMAN, whole thing
#include "scene.h"


extern std::shared_ptr<Scene> gameScene;
extern std::shared_ptr<Scene> menuScene;
extern std::shared_ptr<Scene> activeScene;

extern std::shared_ptr<Entity> player;
extern std::vector<std::shared_ptr<Entity>>enemy_list;
extern std::vector<std::shared_ptr<Entity>>camera_list;

extern sf::Font font;


class MenuScene : public Scene {
private:
	sf::Text text;

public:
	MenuScene() = default;
	void update(double dt) override;
	void render() override;
	void load()override;
	static sf::Font GetFont();
};

class GameScene : public Scene {
private:
	sf::Text text;
	sf::Clock scoreClock;
	//void respawn();

public:
	GameScene() = default;
	void update(double dt) override;
	void render() override;
	void load() override;
};