#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include "Obstacle.hpp"

class Parallax
{
public:
  Parallax();

  void update();
  bool checkCollision(const sf::IntRect &rect) const;
  void initiate();
  void reset();

  int getScore() const;

  void drawObstacles(sf::RenderTarget &target, sf::RenderStates states) const;
  void drawBases(sf::RenderTarget &target, sf::RenderStates states) const;

private:
  void updateBases();
  void updateObstacles();
  int randomPipeHeight() const;

private:
  bool initiated = false;
  int score = 0;
  int lastPassedIndex = -1;

  sf::Texture obstacleTexture;
  sf::Texture baseTexture;

  std::vector<sf::Sprite> bases;
  std::vector<Obstacle> obstacles;
};