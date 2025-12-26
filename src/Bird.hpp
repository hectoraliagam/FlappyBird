#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

class Bird : public sf::Drawable
{
public:
  Bird(float x, float y);

  void update();
  void jump();
  void die();
  void initiate();
  void reset(float x, float y);

  bool isAlive() const;
  sf::Vector2f getPosition() const;

private:
  void animate();
  void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

private:
  enum class AnimationState
  {
    Up = 0,
    Mid = 1,
    Down = 2
  };

  bool initiated = false;
  bool alive = true;

  AnimationState state = AnimationState::Up;
  int animationTimer = 0;
  float velocity = 0.f;

  std::vector<sf::Texture> textures;
  sf::Sprite *sprite;
};