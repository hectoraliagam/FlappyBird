#include "UISound.hpp"
#include "Config.hpp"

#include <fstream>
#include <iostream>

void UISound::centerText(sf::Text &text)
{
  auto bounds = text.getLocalBounds();
  text.setOrigin({bounds.size.x / 2.f, bounds.size.y / 2.f});
}

UISound::UISound()
{
  // ===== Font =====
  if (!font.openFromFile(std::string(Config::ASSETS_PATH) + "font/font.ttf"))
    std::cerr << "Error cargando font.ttf\n";

  // ===== Text =====
  scoreText.setFont(font);
  scoreText.setCharacterSize(Config::SCORE_FONT_SIZE);
  scoreText.setPosition({Config::UI_CENTER_X, Config::SCORE_Y});
  scoreText.setString("0");
  centerText(scoreText);

  maxScoreText.setFont(font);
  maxScoreText.setCharacterSize(Config::MAX_SCORE_FONT_SIZE);
  maxScoreText.setPosition({Config::UI_CENTER_X, Config::MAX_SCORE_Y});

  loadMaxScore();

  // ===== Textures =====
  gameOverTexture.loadFromFile(
      std::string(Config::ASSETS_PATH) + "sprites/gameover.png");
  initTexture.loadFromFile(
      std::string(Config::ASSETS_PATH) + "sprites/message.png");

  gameOverSprite.setTexture(gameOverTexture);
  gameOverSprite.setScale({Config::GAME_OVER_SCALE, Config::GAME_OVER_SCALE});
  gameOverSprite.setPosition({Config::UI_CENTER_X, Config::GAME_OVER_Y});
  gameOverSprite.setOrigin({gameOverTexture.getSize().x / 2.f,
                            gameOverTexture.getSize().y / 2.f});

  initSprite.setTexture(initTexture);
  initSprite.setScale({Config::INIT_MESSAGE_SCALE, Config::INIT_MESSAGE_SCALE});
  initSprite.setPosition({Config::UI_CENTER_X, Config::INIT_MESSAGE_Y});
  initSprite.setOrigin({initTexture.getSize().x / 2.f,
                        initTexture.getSize().y / 2.f});

  // ===== Sounds =====
  pointBuffer.loadFromFile(
      std::string(Config::ASSETS_PATH) + "sounds/point.ogg");
  wingBuffer.loadFromFile(
      std::string(Config::ASSETS_PATH) + "sounds/wing.ogg");
  hitBuffer.loadFromFile(
      std::string(Config::ASSETS_PATH) + "sounds/hit.ogg");

  pointSound.setBuffer(pointBuffer);
  wingSound.setBuffer(wingBuffer);
  hitSound.setBuffer(hitBuffer);

  music.openFromFile(
      std::string(Config::ASSETS_PATH) + "sounds/music.ogg");
  music.setLoop(true);
  music.play();
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

void UISound::draw(sf::RenderTarget &target,
                   sf::RenderStates states) const
{
  if (!initiated)
  {
    target.draw(initSprite, states);
    return;
  }

  target.draw(scoreText, states);
  target.draw(maxScoreText, states);

  if (isGameOver)
    target.draw(gameOverSprite, states);
}