#pragma once

#include "Box2D/Box2D.h"
#include <sfml/System/Vector2.hpp>
#include "engine.h"

namespace Physics {
void initialise();
void shutdown();
void update(const double&);

std::shared_ptr<b2World> GetWorld();

const float physics_scale = 30.0f;
const float physics_scale_inv = 1.0f / physics_scale;

const sf::Vector2f bv2_to_sv2(const b2Vec2& in, bool scale = true);
const b2Vec2 sv2_to_bv2(const sf::Vector2f& in, bool scale = true);
const sf::Vector2f invert_height(const sf::Vector2f& in);
} // namespace Physics



class my_contact_listener : public b2ContactListener {
	// Called when two fixtures begin to touch
	virtual void BeginContact(b2Contact* contact);

	// Called when two fixtures cease to touch
	virtual void EndContact(b2Contact* contact);
};

