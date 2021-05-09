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

	if (yHeight > 760)
		multiplier = 1.0f;
	else if (yHeight > 600 && yHeight < 800)
		multiplier = 0.67f;
	else if (yHeight < 600)
		multiplier = 0.45f;

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