#include "UISound.hpp"
#include "Config.hpp"

#include <fstream>
#include <iostream>
#include <string>

void UISound::centerText(sf::Text &text)
{
  auto bounds = text.getLocalBounds();
  text.setOrigin(
      {bounds.position.x + bounds.size.x / 2.f,
       bounds.position.y + bounds.size.y / 2.f});
}

UISound::UISound()
    : scoreText(font),
      maxScoreText(font),
      pointSound(pointBuffer),
      wingSound(wingBuffer),
      hitSound(hitBuffer)
{
  // ===== Font =====
  if (!font.openFromFile(std::string(Config::ASSETS_PATH) + "font/font.ttf"))
    std::cerr << "Error cargando font.ttf\n";

  // ===== Score Text =====
  scoreText.setCharacterSize(Config::SCORE_FONT_SIZE);
  scoreText.setString("0");
  scoreText.setPosition({Config::UI_CENTER_X, Config::SCORE_Y});
  centerText(scoreText);

  // ===== Max Score Text =====
  maxScoreText.setCharacterSize(Config::MAX_SCORE_FONT_SIZE);
  maxScoreText.setPosition({Config::UI_CENTER_X, Config::MAX_SCORE_Y});
  loadMaxScore();

  // ===== Textures y Sprites =====
  if (!gameOverTexture.loadFromFile(std::string(Config::ASSETS_PATH) + "sprites/gameover.png"))
    std::cerr << "Error cargando gameover.png\n";
  else
    gameOverSprite.emplace(gameOverTexture);

  if (!initTexture.loadFromFile(std::string(Config::ASSETS_PATH) + "sprites/message.png"))
    std::cerr << "Error cargando message.png\n";
  else
    initSprite.emplace(initTexture);

  if (gameOverSprite)
  {
    gameOverSprite->setScale({Config::GAME_OVER_SCALE, Config::GAME_OVER_SCALE});
    gameOverSprite->setOrigin(
        {gameOverTexture.getSize().x / 2.f,
         gameOverTexture.getSize().y / 2.f});
    gameOverSprite->setPosition({Config::UI_CENTER_X, Config::GAME_OVER_Y});
  }

  if (initSprite)
  {
    initSprite->setScale({Config::INIT_MESSAGE_SCALE, Config::INIT_MESSAGE_SCALE});
    initSprite->setOrigin(
        {initTexture.getSize().x / 2.f,
         initTexture.getSize().y / 2.f});
    initSprite->setPosition({Config::UI_CENTER_X, Config::INIT_MESSAGE_Y});
  }

  // ===== Sounds =====
  if (!pointBuffer.loadFromFile(std::string(Config::ASSETS_PATH) + "sounds/point.ogg"))
    std::cerr << "Error cargando point.ogg\n";

  if (!wingBuffer.loadFromFile(std::string(Config::ASSETS_PATH) + "sounds/wing.ogg"))
    std::cerr << "Error cargando wing.ogg\n";

  if (!hitBuffer.loadFromFile(std::string(Config::ASSETS_PATH) + "sounds/hit.ogg"))
    std::cerr << "Error cargando hit.ogg\n";

  // ===== Music =====
  if (music.openFromFile(std::string(Config::ASSETS_PATH) + "sounds/music.ogg"))
  {
    music.setLooping(true);
    music.play();
  }
}

void UISound::loadMaxScore()
{
  std::ifstream in(Config::SCORE_FILE);
  if (!(in >> maxScore))
    maxScore = 0;

  maxScoreText.setString(std::to_string(maxScore));
  centerText(maxScoreText);
}

void UISound::saveMaxScore()
{
  std::ofstream out(Config::SCORE_FILE);
  out << maxScore;
}

void UISound::setScore(int value)
{
  if (score != value)
    pointSound.play();

  score = value;
  scoreText.setString(std::to_string(score));
  centerText(scoreText);
}

void UISound::initiate(bool state)
{
  initiated = state;
  isGameOver = false;
  score = 0;

  scoreText.setString("0");
  centerText(scoreText);

  loadMaxScore();
}

void UISound::wing()
{
  wingSound.play();
}

void UISound::gameOver()
{
  if (!isGameOver)
    hitSound.play();

  if (score > maxScore)
  {
    maxScore = score;
    saveMaxScore();
    maxScoreText.setString(std::to_string(maxScore));
    centerText(maxScoreText);
  }

  isGameOver = true;
}

void UISound::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
  if (!initiated)
  {
    if (initSprite)
      target.draw(*initSprite, states);
    return;
  }

  target.draw(scoreText, states);

  if (isGameOver)
  {
    if (gameOverSprite)
      target.draw(*gameOverSprite, states);
    target.draw(maxScoreText, states);
  }
}