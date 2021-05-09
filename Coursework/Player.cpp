#include "Player.h"
#include "ecm.h"
#include "components/cmp_sprite.h"
#include "components/cmp_player_physics.h"
#include "scenes/scene_tracker.h"
#include "game.h"

using namespace std;
using namespace sf;

void Player::load() {
    addTag("player");

    auto s = addComponent<SpriteComponent>();
    _texture.get()->loadFromFile("res/img/player_spritesheet.png");
    s->setTexture(_texture);
    s->getSprite().setTextureRect(IntRect(0, 0, 27 * sceneTracker.GetMultiplier(), 48 * sceneTracker.GetMultiplier()));
    s->getSprite().setOrigin(13.5f * sceneTracker.GetMultiplier(), 24.f * sceneTracker.GetMultiplier());

    auto pp = addComponent<PlayerPhysicsComponent>(Vector2f(27.f * sceneTracker.GetMultiplier(), 48.f * sceneTracker.GetMultiplier()));
    _canFixture = pp.get()->getFixture();
    _body = _canFixture->GetBody();
}

Player::Player(Scene* s) : Entity(s) {
    _texture = make_shared<Texture>(Texture());
}