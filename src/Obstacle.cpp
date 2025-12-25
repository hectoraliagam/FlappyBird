#include "Obstacle.hpp"
#include "Config.hpp"

Obstacle::Obstacle(const sf::Texture &texture, float x, float gapY)
{
  topPipe.setTexture(texture);
  bottomPipe.setTexture(texture);

  // Pipe superior (invertido)
  topPipe.setOrigin({texture.getSize().x, 0.f});
  topPipe.setRotation(sf::degrees(180.f));

  topPipe.setPosition({x, gapY});
  bottomPipe.setPosition({x, gapY + Config::PIPE_GAP});

  topPipe.setScale({Config::BASE_SCALE, Config::BASE_SCALE});
  bottomPipe.setScale({Config::BASE_SCALE, Config::BASE_SCALE});
}

void Obstacle::update()
{
  topPipe.move({-Config::BASE_SPEED, 0.f});
  bottomPipe.move({-Config::BASE_SPEED, 0.f});
}

bool Obstacle::collision(const sf::IntRect &rect) const
{
  sf::IntRect topRect(
      static_cast<int>(topPipe.getPosition().x + Config::PIPE_COLLISION_X_OFFSET),
      static_cast<int>(topPipe.getPosition().y - Config::PIPE_COLLISION_HEIGHT),
      Config::PIPE_COLLISION_WIDTH,
      Config::PIPE_COLLISION_HEIGHT);

  sf::IntRect bottomRect(
      static_cast<int>(bottomPipe.getPosition().x + Config::PIPE_COLLISION_X_OFFSET),
      static_cast<int>(bottomPipe.getPosition().y),
      Config::PIPE_COLLISION_WIDTH,
      Config::PIPE_COLLISION_HEIGHT);

  return topRect.intersects(rect) || bottomRect.intersects(rect);
}

sf::Vector2f Obstacle::getPosition() const
{
  return topPipe.getPosition();
}

void Obstacle::draw(sf::RenderTarget &target,
                    sf::RenderStates states) const
{
  target.draw(topPipe, states);
  target.draw(bottomPipe, states);
}