#pragma once
#include <SFML/Graphics.hpp>
#include "ecm.h"

class Button : Entity {
private:
	//sf::Text _text;
	sf::Color _color;
	std::string _string;
	int _charSize;
	//sf::Vector2f _position = sf::Vector2f(0,0);
	sf::IntRect _rect;
	sf::Font _font;
public:
	Button() = default;
	void update(double dt) override;
	void render();
	static sf::Text getText();
	//static void Render(sf::RenderWindow& window);
	void setPos(sf::Vector2f pos) { _position = pos; };
	void setText(sf::Text t); //{ t = _text; };
	//void setFont(sf::Font f);
	void load(sf::Color c, int cs, std::string s, sf::Vector2f p, sf::Font f);
};
