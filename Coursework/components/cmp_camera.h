#pragma once
#include "ecm.h"
#include "SFML/Graphics/Sprite.hpp"
#include "system_physics.h"

class CameraComponent : public Component{
public:
	void update(double dt) override;
	void render() override {}
	b2Fixture* getFixture();
	//void SetSprite(sf::Sprite s) {}
	explicit CameraComponent(Entity* p);
	CameraComponent() = delete;
protected:
	b2Body* _body;
	b2Fixture* _fixture;
	sf::Sprite _sprite;
	b2Vec2 _size;
};