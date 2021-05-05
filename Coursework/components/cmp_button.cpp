#include "cmp_button.h"
#include <system_renderer.h>
#include <system_resources.h>
#include <engine.cpp>
#include "../game.h"
#include <SFML/Audio/Sound.hpp>

void ButtonComponent::update(double dt) {
	auto tag = _text.getString();
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		mousethis = true;
	}
	else
	{
		mousethis = false;
	}

	if (mousethis && !mouselast && _rect.contains(static_cast<sf::Vector2i>(sf::Mouse::getPosition(Engine::GetWindow()))))
	{
		sounds.PlayButtonSound();
		float currVolume = sounds.GetVolume();
		if (tag == "Start Game" || tag == "Level-1")
		{
			Engine::ChangeScene(&level1);
		}
		else if (tag == "Level Select")
		{
			Engine::ChangeScene(&levelSelect);
		}
		else if (tag == "Options")
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
		else if (tag == "+")
		{
			sounds.SetVolume(sounds.GetVolume() + 1.0f);
		}
		else if (tag == "-")
		{
			sounds.SetVolume(sounds.GetVolume() - 1.0f);
		}
		else if (tag < to_string(currVolume) || tag > to_string(currVolume))
		{
			tag == to_string(currVolume);
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
	}
	mouselast = mousethis;
}


void ButtonComponent::render() { Renderer::queue(&_text); }
 
ButtonComponent::ButtonComponent(Entity* const p, const std::string f, const int charSize, const sf::Color c, const sf::Vector2f pos, const std::string& str) : Component(p), _string(str) {
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

	//sounds.Load();
}

void ButtonComponent::SetText(const std::string& str) {
    _string = str;
    _text.setString(_string);
}