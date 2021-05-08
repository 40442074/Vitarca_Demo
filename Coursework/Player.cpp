#include "Player.h"
#include "ecm.h"
#include "components/cmp_sprite.h"
#include "components/cmp_player_physics.h"

using namespace std;
using namespace sf;

void Player::load() {
    addTag("player");

    auto s = addComponent<SpriteComponent>();
    _texture.get()->loadFromFile("res/img/player_spritesheet.png");
    s->setTexture(_texture);
    s->getSprite().setTextureRect(IntRect(0, 0, 27, 48));
    s->getSprite().setOrigin(13.5f, 24.f);

    auto pp = addComponent<PlayerPhysicsComponent>(Vector2f(27.f, 48.f));
    _canFixture = pp.get()->getFixture();
    _body = _canFixture->GetBody();
}

Player::Player(Scene* s) : Entity(s) {
    _texture = make_shared<Texture>(Texture());
}