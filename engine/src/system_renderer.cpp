#include "system_renderer.h"
#include <queue>

#include <LevelSystem.h>
#include <iostream>


using namespace std;
using namespace sf;

static queue<const Drawable*> sprites;
static RenderWindow* rw;


void Renderer::initialise(sf::RenderWindow& r) { 
	rw = &r; 
	view = rw->getDefaultView();
}

void Renderer::shutdown() {
  while (!sprites.empty())
    sprites.pop();
}

void Renderer::update(const double&) {}

void Renderer::render() {
	
	rw->setView(view);
	
  if (rw == nullptr) {
    throw("No render window set! ");
  }
  while (!sprites.empty()) {
    rw->draw(*sprites.front());
    sprites.pop();
  }
}

void Renderer::queue(const sf::Drawable* s) { 
	sprites.push(s); }