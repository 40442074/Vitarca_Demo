#pragma once
#include "ecm.h"
#include "SFML/Graphics/Sprite.hpp"
#include "system_physics.h"

class CameraComponent : public Component{
public:
	void update(double dt) override;
	//void Update(double dt, sf::Sprite *s);
	void render() override {}
	b2Fixture* getFixture();
	void SetColour(sf::Color c);
	sf::Color GetColour();
	explicit CameraComponent(Entity* p, b2Fixture *pb, std::string tag);
	CameraComponent() = delete;
protected:
	b2Body *_body;
	b2Fixture *_fixture, *_playerBodyFixture;
	//sf::Sprite _sprite;
	sf::Color _colour;
	b2Vec2 _size;
	std::string _tag;
};