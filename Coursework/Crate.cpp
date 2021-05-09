#include "Crate.h"
#include "ecm.h"
#include "components/cmp_sprite.h"
#include "components/cmp_crate_physics.h"
//#include "scenes/scene_tracker.h"
#include "game.h"

using namespace std;
using namespace sf;

void Crate::load(b2Body *pb) {
    addTag("crate");

    auto s = addComponent<SpriteComponent>();
    _texture.get()->loadFromFile("res/img/crate.png");
    s->setTexture(_texture);
    s->getSprite().setScale(Vector2f(sceneTracker.GetMultiplier(), sceneTracker.GetMultiplier()));
    s->getSprite().setTextureRect(IntRect(0, 0, 60, 60));
    s->getSprite().setOrigin(30.f * sceneTracker.GetMultiplier(), 30.f * sceneTracker.GetMultiplier());

    addComponent<CratePhysicsComponent>(Vector2f(60.0f, 60.0f), pb);
}

Crate::Crate(Scene* s) : Entity(s) {
    _texture = make_shared<Texture>(Texture());
}