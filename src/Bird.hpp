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

  bool isAlive() const;
  sf::Vector2f getPosition() const;

protected:
  void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

private:
  void animate();

private:
  enum class AnimationState
  {
    Up,
    Mid,
    Down
  };

  bool initiated{false};
  bool alive{true};

  AnimationState state{AnimationState::Up};
  int animationTimer{10};

  std::vector<sf::Texture> textures;
  sf::Sprite sprite;

  float velocity{0.f};

  static constexpr float Gravity = 0.5f;
  static constexpr float JumpForce = -8.f;
  static constexpr float RotationSpeed = 4.f;
};