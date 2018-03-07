#include "scene_menu.h"
#include "../components/cmp_text.h"
#include "../game.h"
#include "../components/cmp_sprite.h"
#include "../components/cmp_blinking.h"
#include "SFML/Graphics.hpp"
#include <SFML/Window/Keyboard.hpp>
#include <iostream>

using namespace std;
using namespace sf;


void MenuScene::Load() {
  cout << "Menu Load \n";
  {
	
    auto title = makeEntity();
    auto t = title->addComponent<TextComponent>(
        "Potato's Destiny\nPress Space to Start");
	auto newGame = makeEntity();
	t = newGame->addComponent<TextComponent>(
		"New Game");
	auto shop = makeEntity();
	t = shop->addComponent<TextComponent>(
		"Shop");
	auto exit = makeEntity();
	t = exit->addComponent<TextComponent>(
		"Exit");
	
	newGame->setPosition(Vector2f(200.f, 200.f));
	shop->setPosition(Vector2f(200.f, 300.f));
	exit->setPosition(Vector2f(200.f, 400.f));
	
	auto pointer = makeEntity();
	pointer->addTag("pointer");
	pointer->addComponent<BlinkComponent>(0.5f);
	auto s = pointer->addComponent<ShapeComponent>();
	//float fontsize = t->GetFontSize();
	//hardcoding fontsize atm, because it cannot be accessed from thr Update
	pointer->setPosition(newGame->getPosition() - Vector2f(20.f, - (20.f))); //Vector2f(20.f, - (fontsize + fontsize / 3) / 2) the box around the text is bigger around 1/3 of fontsize. This will set blinking element central
	s->setShape<sf::RectangleShape>(Vector2f(10.f, 10.f));
	s->getShape().setFillColor(Color::Magenta);
	s->getShape().setOrigin(5.f, 5.f);

	posMenuItems[0] = newGame->getPosition();
	posMenuItems[1] = shop->getPosition();
	posMenuItems[2] = exit->getPosition();
	for (int i = 0; i < 3; i++) {
		cout << posMenuItems[i] << endl;
	}
  }
  setLoaded(true);
}

void MenuScene::Update(const double& dt) {
  // cout << "Menu Update "<<dt<<"\n";
	static int posPoint = 0;
	static float countdown = 0.0f;
	countdown -= dt;
	
  if (sf::Keyboard::isKeyPressed(Keyboard::Space)) {
    Engine::ChangeScene(&level1);
  }
  if (sf::Keyboard::isKeyPressed(Keyboard::Down)) {
	  if (posPoint < 2 && countdown <= 0){
	  countdown = 0.2f;//using countdown to give time the player to press again (or will get in this if too many times, pc is fast!)
	  posPoint++;
	  cout << posPoint << endl;
	  cout << posMenuItems[posPoint] << endl;
	  ents.find("pointer")[0]->setPosition(posMenuItems[posPoint] - Vector2f(20.f, -20.f));
	  }
  }
  if (sf::Keyboard::isKeyPressed(Keyboard::Up)) {
	  if (posPoint > 0 && countdown <= 0) {
		  countdown = 0.2f;
		  posPoint--;
		  ents.find("pointer")[0]->setPosition(posMenuItems[posPoint] - Vector2f(20.f, -20.f));
		  
	  }
  }


  Scene::Update(dt);
}
