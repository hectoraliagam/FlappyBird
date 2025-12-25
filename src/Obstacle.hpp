#pragma once

#include <SFML/Graphics.hpp>

class Obstacle : public sf::Drawable
{
public:
  Obstacle(const sf::Texture &texture, float x, float gapY);

  void update();
  bool collision(const sf::IntRect &rect) const;

  sf::Vector2f getPosition() const;

private:
  void draw(sf::RenderTarget &target,
            sf::RenderStates states) const override;

private:
  sf::Sprite topPipe;
  sf::Sprite bottomPipe;
};