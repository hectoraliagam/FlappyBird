#include "Game.hpp"
#include "Config.hpp"

#include <iostream>

Game::Game()
    : window(
          sf::VideoMode{
              {Config::WINDOW_WIDTH, Config::WINDOW_HEIGHT}},
          "Flappy Bird"),
      bird(Config::BIRD_START_X, Config::BIRD_START_Y)
{
#ifdef DEBUG
  std::cout << "Modo DEBUG\n";
#endif

  window.setFramerateLimit(Config::FPS_LIMIT);

  if (!backgroundTexture.loadFromFile(
          std::string(Config::ASSETS_PATH) + "sprites/background.png"))
  {
    std::cerr << "Error cargando background\n";
  }
  else
  {
    background.emplace(backgroundTexture);
    background->setPosition(sf::Vector2f{0.f, Config::BG_POS_Y});
    background->setScale(sf::Vector2f{Config::BG_SCALE, Config::BG_SCALE});
  }
}

void Game::run()
{
  while (window.isOpen())
  {
    processEvents();
    update();
    render();
  }
}

void Game::processEvents()
{
  while (const std::optional<sf::Event> event = window.pollEvent())
  {
    if (event->is<sf::Event::Closed>())
      window.close();

    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && !mousePressed)
    {
      mousePressed = true;

      if (state == GameState::Waiting)
      {
        state = GameState::Playing;
        bird.initiate();
        parallax.initiate();
        uiSound.initiate(true);
      }
      else if (state == GameState::Playing)
      {
        bird.jump();
        uiSound.wing();
      }
      else if (state == GameState::GameOver)
      {
        reset();
      }
    }

    if (!sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
      mousePressed = false;
  }
}

void Game::update()
{
  if (state == GameState::Playing)
  {
    bird.update();
    parallax.update();

    sf::IntRect birdRect(
        sf::Vector2i{
            static_cast<int>(bird.getPosition().x) - Config::BIRD_COLLISION_X_OFFSET,
            static_cast<int>(bird.getPosition().y) - Config::BIRD_COLLISION_Y_OFFSET},
        sf::Vector2i{
            Config::BIRD_COLLISION_W,
            Config::BIRD_COLLISION_H});

    if (parallax.checkCollision(birdRect) ||
        bird.getPosition().y < 0.f ||
        bird.getPosition().y > Config::WINDOW_HEIGHT - Config::GROUND_HEIGHT)
    {
      bird.die();
      uiSound.gameOver();
      state = GameState::GameOver;
    }

    uiSound.setScore(parallax.getScore());
  }

  if (state == GameState::GameOver)
    bird.update();
}

void Game::render()
{
  window.clear();

  // Fondo
  if (background)
    window.draw(*background);

  // Mundo
  parallax.drawBases(window, sf::RenderStates::Default);
  parallax.drawObstacles(window, sf::RenderStates::Default);

  // Personaje
  window.draw(bird);

  // UI
  window.draw(uiSound);

  window.display();
}

void Game::reset()
{
  bird.reset(Config::BIRD_START_X, Config::BIRD_START_Y);
  parallax.reset();
  uiSound.initiate(false);
  state = GameState::Waiting;
}