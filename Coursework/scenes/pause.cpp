#include "pause.h"
#include "../components/cmp_text.h"
#include "../components/cmp_button.h"
#include "../game.h"
#include <SFML/Window/Keyboard.hpp>
#include <iostream>
#include <vector>

using namespace std;
using namespace sf;

PauseMenu::PauseMenu(Scene* s) : Entity(s) { //default constructor for pause menu as it derives from entity

}

void PauseMenu::Load() {    //initialises bools and creates pause menu buttons same as scene_Options.cpp
	_isPaused = false;
	_plast = false;
	_pthis = false;

	for (int i = 0; i < 3; i++) {
		_pauseComponents[i] = addComponent<ButtonComponent>("PressStart2P-Regular.ttf", 48, Color::Blue,
			Vector2f(Engine::getWindowSize().x / 6, Engine::getWindowSize().y / 3 + Engine::getWindowSize().y / 10 * i), "Pause", _pauseText[i]);
		_pauseComponents[i].get()->SetButtonType("NotPaused");
	}
}

void PauseMenu::SetPaused(std::string s) //sets the buttonType to check whether game is paused,
{                                       //this enables or disables int rects via cmp_button.cpp
    for (int i = 0; i < 3; i++) {
        _pauseComponents[i].get()->SetButtonType(s);
    }
}

void PauseMenu::Update(const double& dt) {

    if (Keyboard::isKeyPressed(Keyboard::P)) //pause menu
        _pthis = true;
    else
        _plast = false; //ensuring one click

    if (_pthis && !_plast)
    {
        _isPaused = true;
    }
    
    _pthis = _plast;

    if (_pauseComponents[0]->GetIsClicked() == true) //check if resume is clicked
    {
        _isPaused = false;
        _pauseComponents[0]->SetIsClicked(false);
    }

    Entity::update(dt); 
}

bool PauseMenu::GetPaused() {
    return _isPaused;
}




