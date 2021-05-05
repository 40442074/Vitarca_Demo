#pragma once

#include <SFML/Graphics/Text.hpp>
#include <ecm.h>

class ButtonComponent : public Component {
public:
	ButtonComponent() = delete;
	explicit ButtonComponent(Entity* p, const std::string fpath, const int charSize, const sf::Color c, const sf::Vector2f pos, std::string tag, const std::string& str = "");

	void update(double dt) override;

	void render() override;

	~ButtonComponent() override = default;

	void SetText(const std::string& str);

protected:
	std::shared_ptr<sf::Font> _font;
	std::string _string;
	sf::Text _text;
	sf::IntRect _rect;
	bool mousethis, mouselast;
	int _charSize;
	sf::Color _colour;
	sf::Vector2f _pos;
	std::string _buttonType;
};
