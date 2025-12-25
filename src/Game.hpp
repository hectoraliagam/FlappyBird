#pragma once

#include <SFML/Graphics.hpp>
#include <optional>

#include "Bird.hpp"
#include "Parallax.hpp"
#include "UISound.hpp"

enum class GameState
{
  Waiting,
  Playing,
  GameOver
};

class Game
{
public:
  Game();
  void run();

private:
  void processEvents();
  void update();
  void render();
  void reset();

private:
  sf::RenderWindow window;

  // ===== Recursos =====
  sf::Texture backgroundTexture;
  std::optional<sf::Sprite> background;

  // ===== Objetos del juego =====
  Bird bird;
  Parallax parallax;
  UISound uiSound;

  // ===== Estado =====
  GameState state = GameState::Waiting;
  bool mousePressed = false;
};