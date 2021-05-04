//#pragma once    //used code from PACMAN, whole thing
//#include "maths.h"
//#include <algorithm>
//#include <memory>
//#include <typeindex>
//#include <vector>
//#include <SFML/Graphics.hpp>
//
//class Component; //forward declare
//
//class Entity {
//
//protected:
//	std::vector<std::shared_ptr<Component>> _components;
//	sf::Vector2f _position;
//	float _rotation;
//	bool _alive;       // should be updated
//	bool _visible;     // should be rendered
//	bool _fordeletion; // should be deleted
//public:
//	Entity();
//	virtual ~Entity();
//	virtual void Update(double dt);
//	virtual void Render();
//
//	//const std::vector<std::shared_ptr<Component>> Entity::getComponent() {          /////
//	//	return _components[0];
//	//}
//	const sf::Vector2f& getPosition() const;
//	void setPosition(const sf::Vector2f& _position);
//	bool is_fordeletion() const { return _fordeletion; }
//	float getRotation() const { return _rotation; }
//	void setRotation(float rotation) { _rotation = rotation; }
//	bool isAlive() const { return _alive; }
//	void setAlive(bool alive) { _alive = alive; }
//	void setForDelete() { _fordeletion = true; }
//	bool isVisible() const { return _visible; }
//	void setVisible(bool visible) { _visible = visible; }
//
//	//create components
//	template <typename T, typename... Targs>
//	std::shared_ptr<T> addComponent(Targs... params) {
//		static_assert(std::is_base_of<Component, T>::value, "T != component");
//		std::shared_ptr<T> sp(std::make_shared<T>(this, params...));
//		_components.push_back(sp);
//		return sp;
//	}
//
//	//get components
//	template <typename T>
//	const std::vector<std::shared_ptr<T>> get_components() const {
//		static_assert(std::is_base_of<Component, T>::value, "T != component");
//		std::vector<std::shared_ptr<T>> ret;
//		for (const auto c : _components) {
//			if (typeid(*c) == typeid(T)) {
//				ret.push_back(std::dynamic_pointer_cast<T>(c));
//			}
//		}
//		return std::move(ret);
//	}
//
//	//gets compatible components
//	// Will return a T component, or anything derived from a T component.
//	template <typename T>
//	const std::vector<std::shared_ptr<T>> GetCompatibleComponent() {
//		static_assert(std::is_base_of<Component, T>::value, "T != component");
//		std::vector<std::shared_ptr<T>> ret;
//		for (auto c : _components) {
//			auto dd = dynamic_cast<T*>(&(*c));
//			if (dd) {
//				ret.push_back(std::dynamic_pointer_cast<T>(c));
//			}
//		}
//		return ret;
//	}
//};
//
//class Component {
//protected:
//	Entity* const _parent;
//	bool _fordeletion; // should be removed
//	explicit Component(Entity* const p);
//
//public:
//	Component() = delete;
//	bool is_fordeletion() const { return _fordeletion; }
//	virtual void update(double dt) = 0;
//	virtual void render() = 0;
//	virtual ~Component();
//};
//
//struct EntityManager {
//	std::vector<std::shared_ptr<Entity>> list;
//	void update(double dt);
//	void render(/*sf::RenderWindow& window*/);
//};