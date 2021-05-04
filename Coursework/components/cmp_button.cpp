#include "cmp_button.h"
#include <system_renderer.h>
#include <system_resources.h>
#include <engine.cpp>

void ButtonComponent::update(double dt) {
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		mousethis = true;
	}
	else
	{
		mousethis = false;
	}

	if (mousethis && !mouselast
		&& _rect.contains(static_cast<sf::Vector2i>(sf::Mouse::getPosition(Engine::GetWindow()))))
	{
		std::cout << "mouse click";
	}
	mouselast = mousethis;
}

void ButtonComponent::render() { Renderer::queue(&_text); }

ButtonComponent::ButtonComponent(Entity* const p, const std::string f, const int charSize, const sf::Color c, const std::string& str)
    : Component(p), _string(str) {
    _text.setString(_string);
    _font = Resources::get<sf::Font>(f);
    _text.setFont(*_font);

	auto xLength = _string.length() * _charSize;
	_rect = IntRect(p->getPosition().x, p->getPosition().y, xLength, _charSize);
}

void ButtonComponent::SetText(const std::string& str) {
    _string = str;
    _text.setString(_string);
}