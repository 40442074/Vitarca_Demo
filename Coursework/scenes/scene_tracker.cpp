#include "scene_tracker.h"
#include "../game.h"

using namespace std;
using namespace sf;

void SceneTracker::Load() {

}

void SceneTracker::Update(const double& dt) {
	//Scene::Update(dt);
}

float SceneTracker::GetWidth()
{
	return xWidth;
}

float SceneTracker::GetHeight()
{
	return yHeight;
}

void SceneTracker::SetWidthHeight(int width, int height)
{
	xWidth = width;
	yHeight = height;

	multiplier = (float)height / 1080.0f;

	SetWindowView();
}

void SceneTracker::SetWindowView() {
	auto width = GetWidth();
	auto height = GetHeight();
	sf::View view(sf::FloatRect(0, 0, width, height));
	Engine::SetWindow(view, width, height);
}

float SceneTracker::GetMultiplier() {
	return multiplier;
}

float SceneTracker::GetPhysics() {
	return _physicsScale;
}

void SceneTracker::SetPhysics(float f)
{
	_physicsScale = f;
}