#include "SystemRenderer.h"
#include <queue>

using namespace std;
using namespace sf;

static queue<const Drawable*> mySprites;
static RenderWindow* rw;

void Renderer::initialise(sf::RenderWindow& r) { rw = &r; }

sf::RenderWindow& Renderer::getWindow() { return *rw; }

void Renderer::shutdown() {
    while (!mySprites.empty())
        mySprites.pop();
}

void Renderer::update(const double&) {}

void Renderer::render() {
    if (rw == nullptr) {
        throw("No render window set! ");
    }
    while (!mySprites.empty()) {
        rw->draw(*mySprites.front());
        mySprites.pop();
    }
}

void Renderer::queue(const sf::Drawable* s) { mySprites.push(s); }