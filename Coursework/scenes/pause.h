#pragma once
#include "engine.h"


class PauseMenu : public Scene {
public:
	PauseMenu() = default;
	~PauseMenu() override = default;

	void Load() override;

	void Update(const double& dt) override;

	void GetPositions(sf::Vector2f positions[], int size);
	void ClearPositions();

	std::vector<sf::Vector2f> SetPositions();

protected:
	std::shared_ptr<Entity> _pauseButtons[3];
	std::string _pauseText[3] = { "Resume", "Restart Level", "Back to Main Menu" };
	std::vector<sf::Vector2f> _positions;
};