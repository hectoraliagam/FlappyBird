#include "Obstacle.hpp"
#include "Config.hpp"

Obstacle::Obstacle(const sf::Texture &texture, float x, float gapY)
    : topPipe(texture),
      bottomPipe(texture)
{
  // ===== Pipe superior (invertido) =====
  topPipe.setOrigin({static_cast<float>(texture.getSize().x),
                     0.f});
  topPipe.setRotation(sf::degrees(180.f));

  // ===== Posiciones =====
  topPipe.setPosition({x, gapY});
  bottomPipe.setPosition({x, gapY + Config::PIPE_GAP});

  // ===== Escala =====
  topPipe.setScale({Config::BASE_SCALE, Config::BASE_SCALE});
  bottomPipe.setScale({Config::BASE_SCALE, Config::BASE_SCALE});
}

void Obstacle::update()
{
  const sf::Vector2f movement{-Config::BASE_SPEED, 0.f};
  topPipe.move(movement);
  bottomPipe.move(movement);
}

bool Obstacle::collision(const sf::IntRect &rect) const
{
  sf::IntRect topRect(
      {static_cast<int>(topPipe.getPosition().x + Config::PIPE_COLLISION_X_OFFSET),
       static_cast<int>(topPipe.getPosition().y - Config::PIPE_COLLISION_HEIGHT)},
      {Config::PIPE_COLLISION_WIDTH,
       Config::PIPE_COLLISION_HEIGHT});

  sf::IntRect bottomRect(
      {static_cast<int>(bottomPipe.getPosition().x + Config::PIPE_COLLISION_X_OFFSET),
       static_cast<int>(bottomPipe.getPosition().y)},
      {Config::PIPE_COLLISION_WIDTH,
       Config::PIPE_COLLISION_HEIGHT});

  return topRect.findIntersection(rect).has_value() ||
         bottomRect.findIntersection(rect).has_value();
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