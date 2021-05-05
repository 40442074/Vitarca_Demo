#include "ecm.h"
class Scene {
public:
	Scene() = default;
	virtual ~Scene() = default;
	virtual void update(double dt);
	virtual void render();
	virtual void load() = 0;
	//std::vector<std::shared_ptr<Entity>>& getEnts();	//public getter to the entity list

protected:
	EntityManager _ents;	//internal entity manager
};