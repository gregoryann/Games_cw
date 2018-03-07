#pragma once

#include "engine.h"

class MenuScene : public Scene {
private:
	sf::Vector2f posMenuItems[3];
public:
  MenuScene() = default;
  ~MenuScene() override = default;

  void Load() override;

  void Update(const double& dt) override;
};
