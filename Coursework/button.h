#pragma once
#include <SFML/Graphics.hpp>
#include <ecm.h>

class Button : Entity {
private:
	sf::Color _color;
	std::string _string;
	int _charSize;
	sf::IntRect _rect;
	sf::Font _font;
public:
	Button() = default;
	void update(double dt) override;
	void render();
	static sf::Text getText();
	void setPos(sf::Vector2f pos) { _position = pos; };
	void setText(sf::Text t);
	void load(sf::Color c, int cs, std::string s, sf::Vector2f p, sf::Font f);
};
