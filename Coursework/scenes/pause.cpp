#include "pause.h"
#include "../components/cmp_text.h"
#include "../components/cmp_button.h"
#include "../game.h"
#include <SFML/Window/Keyboard.hpp>
#include <iostream>
#include <vector>

using namespace std;
using namespace sf;

PauseMenu::PauseMenu(Scene* s) : Entity(s) {

}

void PauseMenu::Load() {

	//pause code
	_isPaused = false;
	_plast = false;
	_pthis = false;

	for (int i = 0; i < 3; i++) {
		_pauseComponents[i] = addComponent<ButtonComponent>("PressStart2P-Regular.ttf", 48, Color::Blue,
			Vector2f(Engine::getWindowSize().x / 6, Engine::getWindowSize().y / 3 + Engine::getWindowSize().y / 10 * i), "Pause", _pauseText[i]);
		_pauseComponents[i].get()->SetButtonType("NotPaused");
	}

	//for (int i = 0; i < 3; i++) {
	//	_pauseButtons[i] = makeEntity();
	//	_pauseButtons[i]->addComponent<ButtonComponent>("PressStart2P-Regular.ttf", 48, Color::Blue, 
	//		Vector2f(Engine::getWindowSize().x / 6, Engine::getWindowSize().y / 3 + Engine::getWindowSize().y / 10 * i), "Pause", _pauseText[i]);
	//}
}

void PauseMenu::SetPaused(std::string s)
{
    for (int i = 0; i < 3; i++) {
        _pauseComponents[i].get()->SetButtonType(s);
    }
}

void PauseMenu::Update(const double& dt) {

    if (Keyboard::isKeyPressed(Keyboard::P)) //pause menu
        _pthis = true;
    else
        _plast = false;

    if (_pthis && !_plast)
    {
        _isPaused = true;
    }
    else
    {
        //if (_pauseComponents[0]->GetButtonType() == "Paused") //and resume button isclicked
        //{
        //    _isPaused = false;
        //}
    }
    
    _pthis = _plast;

    if (_pauseComponents[0]->GetResumeClick() == true)
    {
        _isPaused = false;
        _pauseComponents[0]->SetResumeClick(false);
    }
    
    

    Entity::update(dt);
}

bool PauseMenu::GetPaused() {
    return _isPaused;
}




