#include "cmp_button.h"
#include <system_renderer.h>
#include <system_resources.h>
#include <engine.cpp>
#include "../game.h"

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
		else if (tag == "Level-2")
		{
			Engine::ChangeScene(&level2);
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
}

void ButtonComponent::SetText(const std::string& str) {
    _string = str;
    _text.setString(_string);
}