#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
//#include <ecm.h>
#include "../lib_ecm/ecm.h"
#include <future>
#include <maths.h>
#include <mutex>
#include <string>

class Scene {
public:
  Scene() = default;
  virtual ~Scene();
  virtual void Load() = 0;
  virtual void LoadAsync();
  virtual void UnLoad();
  virtual void Update(const double& dt);
  virtual void Render();
  std::string GetCurrentScene();
  std::string GetPreviousScene();
  virtual void SetScenes(std::string s);
  bool isLoaded() const;
  std::shared_ptr<Entity> makeEntity();

  template <class T>
  std::shared_ptr<T> makeEntityChild() {
      static_assert(std::is_base_of<Entity, T>::value, "T != component");
      std::shared_ptr<T> e = std::make_shared<T>(this);
      ents.list.push_back(e);
      return std::move(e);
  }

  EntityManager ents;

protected:
  void setLoaded(bool);
  std::string currentScene;
  std::string previousScene;
private:
  mutable bool _loaded;
  mutable std::future<void> _loaded_future;
  mutable std::mutex _loaded_mtx;
};

class Engine {
public:
  Engine() = delete;
  static void Start(unsigned int width, unsigned int height,
                    const std::string& gameName, Scene* scn);
  static void ChangeScene(Scene*);
  static sf::RenderWindow& GetWindow();
  static sf::Vector2u getWindowSize();
  static void SetWindow(sf::View view, float x, float h);
  static void setVsync(bool b);

private:
  static Scene* _activeScene;
  static std::string _gameName;
  static void Update();
  static void Render(sf::RenderWindow& window);
};

namespace timing {
// Return time since Epoc
long long now();
// Return time since last() was last called.
long long last();
} // namespace timing