#pragma once

#include <map>
#include "ecm.h"
#include <SFML/Graphics/Shape.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include "../AnimatedSprite.hpp"

class SpriteComponentAnimated : public Component {
protected:
	Animation* _currentAnimation;
	std::map<std::string, Animation> _animations;
	std::shared_ptr<AnimatedSprite> _sprite;
	std::string state;
public:

	SpriteComponentAnimated() = delete;

	explicit SpriteComponentAnimated(Entity* p);
	void update(double dt) override;
	void render() override;

	AnimatedSprite& getSprite() const;
	void addAnimation(std::string key, Animation animation);
	void addFrames(Animation& a, int frames, int rowlength, float width, float height, float initHeight);
	template <typename... Targs> void setSprite(Targs... params) {
		_sprite.reset(new AnimatedSprite(params...));
	}
};

class SpriteComponent : public Component {
protected:
  std::shared_ptr<sf::Sprite> _sprite;
  std::shared_ptr<sf::Texture> _texture;

public:
  SpriteComponent() = delete;

  explicit SpriteComponent(Entity* p);
  void update(double dt) override;
  void render() override;

  sf::Sprite& getSprite() const;
  
  template <typename... Targs> void setSprite(Targs... params) {
    _sprite.reset(new sf::Sprite(params...));
  }
};

class ShapeComponent : public Component {
protected:
  std::shared_ptr<sf::Shape> _shape;
  // sf::Shape _shape;

public:
  ShapeComponent() = delete;

  explicit ShapeComponent(Entity* p);

  void update(double dt) override;
  void render() override;
  sf::Shape& getShape() const;
  template <typename T, typename... Targs> void setShape(Targs... params) {
    _shape.reset(new T(params...));
  }
};