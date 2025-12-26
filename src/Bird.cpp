#include "Bird.hpp"
#include "Config.hpp"

#include <iostream>
#include <string>

Bird::Bird(float x, float y)
{
  textures.resize(3);

  if (!textures[0].loadFromFile(std::string(Config::ASSETS_PATH) + "sprites/birdupflap.png"))
    std::cerr << "Error cargando birdupflap.png\n";
  if (!textures[1].loadFromFile(std::string(Config::ASSETS_PATH) + "sprites/birdmidflap.png"))
    std::cerr << "Error cargando birdmidflap.png\n";
  if (!textures[2].loadFromFile(std::string(Config::ASSETS_PATH) + "sprites/birddownflap.png"))
    std::cerr << "Error cargando birddownflap.png\n";

  sprite = new sf::Sprite(textures[0]);
  sprite->setOrigin(
      {textures[0].getSize().x / 2.f,
       textures[0].getSize().y / 2.f});
  sprite->setPosition({x, y});
  sprite->setScale({Config::BIRD_SCALE, Config::BIRD_SCALE});

  animationTimer = Config::BIRD_ANIMATION_DELAY;
}

void Bird::update()
{
  if (!alive)
  {
    if (sprite->getPosition().y < Config::WINDOW_HEIGHT - Config::GROUND_HEIGHT)
    {
      sprite->move({0.f, Config::BIRD_MAX_FALL_SPEED});

      sf::Angle rotation = sprite->getRotation() + sf::degrees(Config::BIRD_DEAD_ROTATION);
      if (rotation > sf::degrees(90.f))
        rotation = sf::degrees(90.f);
      sprite->setRotation(rotation);
    }
    return;
  }

  animate();

  if (!initiated)
    return;

  sprite->move({0.f, velocity});
  velocity += Config::BIRD_GRAVITY;
  if (velocity > Config::BIRD_MAX_FALL_SPEED)
    velocity = Config::BIRD_MAX_FALL_SPEED;

  sf::Angle rot = sprite->getRotation() + sf::degrees(Config::BIRD_ROTATION_SPEED);
  if (rot > sf::degrees(25.f))
    rot = sf::degrees(25.f);
  sprite->setRotation(rot);
}

void Bird::animate()
{
  if (--animationTimer > 0)
    return;

  const int next = (static_cast<int>(state) + 1) % static_cast<int>(textures.size());
  state = static_cast<AnimationState>(next);

  sprite->setTexture(textures[next]);
  animationTimer = Config::BIRD_ANIMATION_DELAY;
}

void Bird::jump()
{
  if (!alive || !initiated)
    return;

  velocity = Config::BIRD_JUMP_FORCE;
  sprite->setRotation(sf::degrees(Config::BIRD_JUMP_ROTATION));
}

void Bird::die() { alive = false; }
void Bird::initiate() { initiated = true; }
bool Bird::isAlive() const { return alive; }
sf::Vector2f Bird::getPosition() const { return sprite->getPosition(); }

void Bird::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
  target.draw(*sprite, states);
}

void Bird::reset(float x, float y)
{
  initiated = false;
  alive = true;
  velocity = 0.f;
  state = AnimationState::Up;
  animationTimer = Config::BIRD_ANIMATION_DELAY;

  sprite->setTexture(textures[0]);
  sprite->setRotation(sf::degrees(0.f));
  sprite->setPosition({x, y});
}