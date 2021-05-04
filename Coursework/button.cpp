#include "button.h"
#include "GameManager.h"
#include "SystemRenderer.h"

using namespace sf;
using namespace std;

bool mousethis, mouselast;

void Button::load(Color c, int cs, string s, Vector2f p, Font f) {
	_color = c;
	_charSize = cs;
	_string = s;
	_position = p;
	_font = f;

	auto xLength = _string.length() * _charSize;
	_rect = IntRect(_position.x, _position.y, xLength, _charSize);
}

void Button::update(double dt, RenderWindow& window) {
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		mousethis = true;
	}
	else
	{
		mousethis = false;
	}

	if (mousethis && !mouselast
		&& _rect.contains(static_cast<sf::Vector2i>(sf::Mouse::getPosition(window))))
	{
		std::cout << "mouse click";
	}
	mouselast = mousethis;
}

void Button::render() {
	Text rendertext;
	rendertext.setColor(_color);
	rendertext.setCharacterSize(_charSize);
	rendertext.setString(_string);
	rendertext.setPosition(_position);
	rendertext.setFont(_font);
	Renderer::getWindow().draw(rendertext);
}
