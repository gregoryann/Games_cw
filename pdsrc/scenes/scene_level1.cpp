#include "scene_level1.h"
#include "../components/cmp_player_physics.h"
#include "../components/cmp_sprite.h"
#include "../game.h"
#include <LevelSystem.h>
#include <iostream>
#include <thread>
#include <SFML\Graphics\View.hpp>
#include "system_renderer.h"

using namespace std;
using namespace sf;

static shared_ptr<Entity> player;
static shared_ptr<Entity> coin;
void Level1Scene::Load() {
  cout << " Scene 1 Load" << endl;
  ls::loadLevelFileJson("res/levels/untitled100.json");

  auto ho = Engine::getWindowSize().y - (ls::getHeight() * 40.f);
  ls::setOffset(Vector2f(0, 0));//TODO:check how to use offset (before was set to ho)
 
  // Create player
  {
    player = makeEntity();
    player->setPosition(ls::getTilePosition(ls::findTiles(ls::START)[0]));
    auto s = player->addComponent<ShapeComponent>();
    s->setShape<sf::RectangleShape>(Vector2f(20.f, 30.f));
    s->getShape().setFillColor(Color::Magenta);
    s->getShape().setOrigin(10.f, 15.f);
	

    player->addComponent<PlayerPhysicsComponent>(Vector2f(20.f, 30.f));
	
	//set view to center on player
	Renderer::view.reset(sf::FloatRect(player->getPosition().x, player->getPosition().y, 1280.0f, 800.f));
	
  }

  // Add coins
  {
	  Texture p;
	  p.loadFromFile("res/images/TileSet1.png");
	  textures->push_back(p);
	  Animation a;
	  a.setSpriteSheet(textures->at(0));
	  auto coins = ls::findTiles(ls::COIN);
	  for (auto c : coins) {
		  Vector2f pos = ls::getTilePosition(c);
		  pos += Vector2f(8.0f, 8.0f);
		  coin = makeEntity();
		  coin->setPosition(pos);
		  auto s = coin->addComponent<SpriteComponentAnimated>();
		  
		  s->addFrames(a, 5, 5, 16.0f, 16.0f, 0.0f);
		  AnimatedSprite b(sf::seconds(0.05f), true, true);
		  s->setSprite(b);
		  s->getSprite().setOrigin(8.0f, 8.0f);//needs to set origin because physics create box usign center origin
		 
		  s->addAnimation("idle", a);
		  coin->addComponent<PhysicsComponent>(false, Vector2f(16.0f,16.0f));
	  }
  }

  // Add physics colliders to level tiles.
  {
    auto walls = ls::findTiles(ls::WALL);
    for (auto w : walls) {
      auto pos = ls::getTilePosition(w);
      pos += Vector2f(20.f, 20.f); //offset to center
      auto e = makeEntity();
      e->setPosition(pos);
      e->addComponent<PhysicsComponent>(false, Vector2f(40.f, 40.f));
    }
  }

  //Simulate long loading times
  //std::this_thread::sleep_for(std::chrono::milliseconds(3000));
  cout << " Scene 1 Load Done" << endl;

  setLoaded(true);
}

void Level1Scene::UnLoad() {
  cout << "Scene 1 Unload" << endl;
  player.reset();
  ls::unload();
  Scene::UnLoad();
}

void Level1Scene::Update(const double& dt) {
	
  if (ls::getTileAt(player->getPosition()) == ls::END) {
	 
//    Engine::ChangeScene((Scene*)&level2);
  }
 /* if (coin->get_components<PhysicsComponent>()[0]->isTouching(*player->get_components<PlayerPhysicsComponent>()[0])) {
	  cout << "yes they are !" << endl;
  }*/
  //cout << getView().getCenter() << endl;
  Renderer::view.setCenter(Vector2f(player->getPosition().x, player->getPosition().y));
  cout << &Renderer::view << " lv1"<< endl;
  cout << Renderer::view.getCenter() << " lv1" << endl;
  Scene::Update(dt);
}

void Level1Scene::Render() {
  ls::render(Engine::GetWindow());
  Scene::Render();
}
