#pragma once

#include <SFML/Graphics/Text.hpp>
#include <ecm.h>

struct MyKeys
{
	sf::Keyboard::Key KeyCode;
	sf::Mouse::Button MouseButton;
};

class ButtonComponent : public Component {
public:
	ButtonComponent() = delete;
	explicit ButtonComponent(Entity* p, const std::string fpath, const int charSize, const sf::Color c, const sf::Vector2f pos, std::string tag, const std::string& str = "");

	void update(double dt) override;

	void render() override;

	~ButtonComponent() override = default;

	void SetText(const std::string& str);

	std::string GetButtonType();

	void SetButtonType(std::string s);

	bool GetIsClicked();
	void SetIsClicked(bool b);
	void SetParentKeys();
	std::map<std::string, MyKeys> GetKeys();
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
	bool isClicked = false;
	std::string _parentKeys[4];
	std::string _parentKey;

	std::map<std::string, MyKeys> Keys;
	MyKeys key;

	Event eventT;
};
