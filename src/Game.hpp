#pragma once

#include <SFML/Graphics.hpp>
#include <optional>

class Game
{
public:
  Game();
  void run();

private:
  void processEvents();
  void render();

private:
  sf::RenderWindow window;
};