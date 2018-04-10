
#include "cmp_sprite.h"
#include "system_renderer.h"
#include <SFML/Graphics.hpp>
using namespace std;

//sprite static
SpriteComponent::SpriteComponent(Entity* p)
	: Component(p), _sprite(make_shared<sf::Sprite>()) {}

void SpriteComponent::update(double dt) {
	_sprite->setPosition(_parent->getPosition());
	_sprite->setRotation(_parent->getRotation());
}

void SpriteComponent::render() { Renderer::queue(_sprite.get(), _parent->isDynamic()); }


//shape
void ShapeComponent::update(double dt) {
	_shape->setPosition(_parent->getPosition());
	_shape->setRotation(_parent->getRotation());

}

void ShapeComponent::render() {

	Renderer::queue(_shape.get(), _parent->isDynamic());
}

sf::Shape& ShapeComponent::getShape() const { return *_shape; }

ShapeComponent::ShapeComponent(Entity* p)
	: Component(p), _shape(make_shared<sf::CircleShape>()) {}

sf::Sprite& SpriteComponent::getSprite() const { return *_sprite; }

//sprite animated

SpriteComponentAnimated::SpriteComponentAnimated(Entity * p)
	: Component(p), _sprite(make_shared<AnimatedSprite>()) {}

void SpriteComponentAnimated::update(double dt)
{
	sf::Time frameTime = sf::seconds(dt);
	_sprite->setPosition(_parent->getPosition());
	_sprite->setRotation(_parent->getRotation());

	if (state != _parent->getState()) {//using state var instead of checking with the <map>.find() for faster check

		if (_animations.find(_parent->getState()) == _animations.end())
		{
			cout << "state in the parent does not exists in the animations map" << endl;
			return;
		}
		state = _parent->getState();
		_currentAnimation = &_animations.at(state);
		_sprite->setAnimation(*_currentAnimation);
	}

	_sprite->play(*_currentAnimation);

	_sprite->update(frameTime);
}

void SpriteComponentAnimated::render()
{
	Renderer::queue(_sprite.get(), _parent->isDynamic());
}

AnimatedSprite & SpriteComponentAnimated::getSprite() const
{
	return *_sprite;
}

//atm works on a frameset which starts on a new line -> x=0 and it is square TODO:modify to work on starting different positions
void SpriteComponentAnimated::addFrames(Animation& a,int frames, int rowlength, float width, float height, float initHeight) {
	
	for (int i = 0; i < frames; i++) {
		int x = i % rowlength;
		int y = (int)i / rowlength;
		a.addFrame(sf::IntRect(x * width, y * height + initHeight, width, height));
	}
	
}

void SpriteComponentAnimated::addAnimation(std::string key, Animation animation)
{
	std::pair<std::map<std::string, Animation>::iterator, bool> ret;
	ret = _animations.insert({ key, animation });
	if (ret.second == false) {
		cout << "element " + key + " already existed" << endl;
	}
}
