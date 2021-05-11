#pragma once
//#include "engine.h"
#include <ecm.h>
#include "../components/cmp_button.h"

class PauseMenu : public Entity {
public:
	PauseMenu(Scene* s);

	void Load();

	void Update(const double& dt);
	bool GetPaused();
	void SetPaused(std::string s);

protected:
	std::shared_ptr<ButtonComponent> _pauseComponents[3];
	std::string _pauseText[3] = { "Resume", "Restart Level", "Back to Main Menu" };
	bool _pthis = false, _plast = false, _isPaused = false;
};