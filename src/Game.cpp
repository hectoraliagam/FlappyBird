#include "Game.hpp"

#ifdef DEBUG
#include <iostream>
#endif

Game::Game() : window(sf::VideoMode{{400, 700}}, "Flappy Bird")
{
#ifdef DEBUG
  std::cout << "Modo DEBUG\n";
#endif

  window.setFramerateLimit(60);
}

void Game::run()
{
  while (window.isOpen())
  {
    processEvents();
    render();
  }
}

void Game::processEvents()
{
  while (const std::optional<sf::Event> event = window.pollEvent())
  {
    if (event->is<sf::Event::Closed>())
    {
      window.close();
    }
  }
}

void Game::render()
{
  window.clear();
  window.display();
}