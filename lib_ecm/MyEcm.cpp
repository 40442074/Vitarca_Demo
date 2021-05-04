//#include "ecm.h"  //used code from PACMAN, whole thing
//using namespace std;
//using namespace sf;
//
//
//const Vector2f& Entity::getPosition() const { return _position; }
//
//void Entity::setPosition(const Vector2f& pos) { _position = pos; }
//
//void Entity::Update(double dt) {
//	if (_alive)
//	{
//		for (shared_ptr<Component> c : _components)
//		{
//			c->update(dt);
//		}
//	}
//}
//
//void Entity::Render() {
//	if (_visible)
//	{
//		for (shared_ptr<Component> c : _components)
//		{
//			c->render();
//		}
//	}
//}
//
//Entity::Entity() {};
//
//Entity::~Entity() {};
//
//Component::Component(Entity* const p) : _parent(p) {};
//
//Component::~Component() {};
//
//void EntityManager::update(double dt) {
//
//};
//
//
//void EntityManager::render(/*sf::RenderWindow& window*/) {
//	/*   for (int i = 0; i < list.size(); i++) {
//		   list[i]->Render(window);
//	   }*/
//	   //window.draw(*_shape);
//};