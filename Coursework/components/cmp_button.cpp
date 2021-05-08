#include "cmp_button.h"
#include <system_renderer.h>
#include <system_resources.h>
#include <engine.cpp>
#include "../game.h"
#include <SFML/Audio/Sound.hpp>
#include <sstream>
#include <iostream>
#include <string>

void ButtonComponent::update(double dt) {
	string tag = _text.getString();
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		mousethis = true;
	}
	else
	{
		mousethis = false;
	}

	//if string contains numbers for volume ui
	if (_buttonType == "SoundNumber")
	{
		int vol = sounds.GetSoundVolume();
		_text.setString(to_string(vol));
	}
	else if (_buttonType == "MusicNumber")
	{
		int vol = sounds.GetMusicVolume();
		_text.setString(to_string(vol));
	}

	if (mousethis && !mouselast && _rect.contains(static_cast<sf::Vector2i>(sf::Mouse::getPosition(Engine::GetWindow()))))
	{
		sounds.PlayButtonSound();

		if (tag == "Start Game" || tag == "Level-1" || tag == "Restart Level")
		{
			Engine::ChangeScene(&level1);
		}
		else if (tag == "Level Select")
		{
			Engine::ChangeScene(&levelSelect);
		}
		else if (tag == "Options" || tag == "Back to Options")
		{
			Engine::ChangeScene(&optionsScene);
		}
		else if (tag == "Back to Main Menu")
		{
			Engine::ChangeScene(&menu);
		}
		else if (tag == "Restart Game")
		{
			//delete progress
		}
		else if (tag == "Exit Game")
		{
			//exit game
			Engine::GetWindow().close();
		}
		else if (tag == "Volume")
		{
			Engine::ChangeScene(&volScene);
		}
		else if (tag == "+" && _buttonType == "Sound")
		{
			if (sounds.GetSoundVolume() < 100) {//limits on volume
				sounds.SetSoundVolume(sounds.GetSoundVolume() + 10);
			}
			else if (sounds.GetSoundVolume() > 100) //limits on volume
			{
				sounds.SetSoundVolume(100);
			}		
		}
		else if (tag == "-" && _buttonType == "Sound")
		{
			if (sounds.GetSoundVolume() > 0) { //limits on volume
				sounds.SetSoundVolume(sounds.GetSoundVolume() - 10);
			}
			else if (sounds.GetSoundVolume() < 0) //limits on volume
			{
				sounds.SetSoundVolume(0);
			}	
		}
		else if (tag == "+" && _buttonType == "Music")
		{
			if (sounds.GetMusicVolume() < 100) {//limits on volume
				sounds.SetMusicVolume(sounds.GetMusicVolume() + 10);
			}
			else if (sounds.GetMusicVolume() > 100) //limits on volume
			{
				sounds.SetMusicVolume(100);
			}		
		}
		else if (tag == "-" && _buttonType == "Music")
		{
			if (sounds.GetMusicVolume() > 0) { //limits on volume
				sounds.SetMusicVolume(sounds.GetMusicVolume() - 10);
			}
			else if (sounds.GetMusicVolume() < 0) //limits on volume
			{
				sounds.SetMusicVolume(0);
			}	
		}
		else if (tag == "Resolution")
		{
			Engine::ChangeScene(&resScene);
		}
		else if (tag == "Level-2")
		{
			Engine::ChangeScene(&level2);
		}
		else if (tag == "Level-3")
		{
			//Engine::ChangeScene(&level3);
		}
		else if (tag == "Resume")
		{
		/*	if (sceneTracker.GetPreviousScene() == "level1")
			{
				Engine::ChangeScene(&level1);
			}*/
			_buttonType = "NotPaused";
			
		}
	}
	mouselast = mousethis;
}


void ButtonComponent::render() { Renderer::queue(&_text); }
 
ButtonComponent::ButtonComponent(Entity* const p, const std::string f, const int charSize, const sf::Color c, const sf::Vector2f pos, std::string tag, const std::string& str) : Component(p), _string(str) {
    _text.setString(_string);
    _font = Resources::get<sf::Font>(f);
    _text.setFont(*_font);
	_charSize = charSize;
	_colour = c;
	_pos = pos;
	_text.setPosition(_pos);
	_text.setColor(c);
	auto xLength = _string.size() * _charSize;
	_rect = IntRect(_pos.x, _pos.y, xLength, _charSize);
	_buttonType = tag;
	//sounds.Load();
}

void ButtonComponent::SetText(const std::string& str) {
    _string = str;
    _text.setString(_string);
}

std::string ButtonComponent::GetButtonType()
{
	return _buttonType;
}

void ButtonComponent::SetButtonType(std::string s)
{
	_buttonType = s;
}