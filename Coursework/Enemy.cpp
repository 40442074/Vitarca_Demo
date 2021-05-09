#include "Enemy.h"
#include "ecm.h"
#include "components/cmp_sprite.h"
#include "components/cmp_enemy_physics.h"

using namespace std;
using namespace sf;

void Enemy::load() {
    addTag("enemy");

    auto s = addComponent<SpriteComponent>();
    _texture.get()->loadFromFile("res/img/player_spritesheet.png");
    s->setTexture(_texture);
    s->getSprite().setTextureRect(IntRect(0, 0, 27, 48));
    s->getSprite().setOrigin(13.5f, 24.f);

    auto pp = addComponent<EnemyPhysicsComponent>(Vector2f(27.f, 48.f));
}

Enemy::Enemy(Scene* s) : Entity(s) {
    _texture = make_shared<Texture>(Texture());
}