#include "Parallax.hpp"
#include "Config.hpp"

#include <iostream>
#include <string>
#include <cstdlib>

Parallax::Parallax()
{
  if (!obstacleTexture.loadFromFile(
          std::string(Config::ASSETS_PATH) + "sprites/pipe.png"))
    std::cerr << "Error cargando pipe.png\n";

  if (!baseTexture.loadFromFile(
          std::string(Config::ASSETS_PATH) + "sprites/base.png"))
    std::cerr << "Error cargando base.png\n";

  // ===== Bases =====
  sf::Sprite base(baseTexture);
  base.setScale({Config::BASE_SCALE, Config::BASE_SCALE});
  base.setPosition({0.f, Config::GROUND_Y});
  bases.push_back(base);

  base.setPosition({Config::BASE_WIDTH * Config::BASE_SCALE,
                    Config::GROUND_Y});
  bases.push_back(base);

  // ===== Obstáculos iniciales =====
  obstacles.emplace_back(
      obstacleTexture,
      Config::PIPE_START_X_1,
      randomPipeHeight());

  obstacles.emplace_back(
      obstacleTexture,
      Config::PIPE_START_X_2,
      randomPipeHeight());
}

void Parallax::update()
{
  updateBases();

  if (!initiated)
    return;

  updateObstacles();
}

void Parallax::updateBases()
{
  for (auto &base : bases)
    base.move({-Config::BASE_SPEED, 0.f});

  if (bases.front().getPosition().x <
      -(Config::BASE_WIDTH * Config::BASE_SCALE))
  {
    sf::Sprite newBase = bases.back();
    newBase.setPosition(
        {newBase.getPosition().x +
             Config::BASE_WIDTH * Config::BASE_SCALE,
         Config::GROUND_Y});

    bases.push_back(newBase);
    bases.erase(bases.begin());
  }
}

void Parallax::updateObstacles()
{
  for (auto &obstacle : obstacles)
    obstacle.update();

  // ===== Score =====
  for (std::size_t i = 0; i < obstacles.size(); ++i)
  {
    if (obstacles[i].getPosition().x<Config::PIPE_SCORE_X &&static_cast<int>(i)> lastPassedIndex)
    {
      lastPassedIndex = static_cast<int>(i);
      ++score;
    }
  }

  // ===== Reciclado =====
  if (!obstacles.empty() &&
      obstacles.front().getPosition().x <= Config::PIPE_DESPAWN_X)
  {
    obstacles.erase(obstacles.begin());
    --lastPassedIndex;

    const float newX =
        obstacles.back().getPosition().x +
        Config::PIPE_SPACING;

    obstacles.emplace_back(
        obstacleTexture,
        newX,
        randomPipeHeight());
  }
}

bool Parallax::checkCollision(const sf::IntRect &rect) const
{
  for (const auto &obstacle : obstacles)
  {
    if (obstacle.collision(rect))
      return true;
  }
  return false;
}

void Parallax::initiate()
{
  initiated = true;
}

int Parallax::getScore() const
{
  return score;
}

int Parallax::randomPipeHeight() const
{
  return Config::PIPE_MIN_Y +
         std::rand() % Config::PIPE_RANDOM_RANGE;
}

void Parallax::draw(sf::RenderTarget &target,
                    sf::RenderStates states) const
{
  for (const auto &obstacle : obstacles)
    target.draw(obstacle, states);

  for (const auto &base : bases)
    target.draw(base, states);
}