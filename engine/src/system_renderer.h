#pragma once

#include <SFML/Graphics.hpp>
//#include "cmp_sprite.h"

namespace Renderer {
void initialise(sf::RenderWindow&);

void shutdown();

void update(const double&);

void queue(const sf::Drawable* s, const bool dynamic);

void render();

extern sf::View view;
}; // namespace Renderer
