#include "Bird.hpp"
#include <iostream>

Bird::Bird(float x, float y) : textures(3), sprite(textures[0])
{
  if (!textures[0].loadFromFile("../resources/sprites/birdupflap.png"))
    std::cerr << "Error cargando birdupflap.png\n";

  if (!textures[1].loadFromFile("../resources/sprites/birdmidflap.png"))
    std::cerr << "Error cargando birdmidflap.png\n";

  if (!textures[2].loadFromFile("../resources/sprites/birddownflap.png"))
    std::cerr << "Error cargando birddownflap.png\n";

  sprite.setOrigin({sprite.getTexture().getSize().x / 2.f, sprite.getTexture().getSize().y / 2.f});

  sprite.setPosition({x, y});
  sprite.setScale({2.f, 2.f});
}

void Bird::update()
{
  if (!alive)
  {
    sprite.move({0.f, 12.f});
    sprite.rotate(sf::degrees(10.f));
    return;
  }

  animate();

  if (!initiated)
    return;

  sprite.move({0.f, velocity});
  velocity += Gravity;

  if (velocity > 8.f)
    sprite.rotate(sf::degrees(RotationSpeed));
}

void Bird::animate()
{
  animationTimer--;

  if (animationTimer <= 0)
  {
    int next = (static_cast<int>(state) + 1) % textures.size();
    state = static_cast<AnimationState>(next);

    sprite.setTexture(textures[next]);

    sprite.setOrigin({sprite.getTexture().getSize().x / 2.f, sprite.getTexture().getSize().y / 2.f});

    animationTimer = 10;
  }
}

void Bird::jump()
{
  velocity = JumpForce;
  sprite.setRotation(sf::degrees(-15.f));
}

void Bird::die()
{
  alive = false;
}

void Bird::initiate()
{
  initiated = true;
}

bool Bird::isAlive() const
{
  return alive;
}

sf::Vector2f Bird::getPosition() const
{
  return sprite.getPosition();
}

void Bird::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
  target.draw(sprite, states);
}
