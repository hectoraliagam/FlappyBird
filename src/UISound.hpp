#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class UISound : public sf::Drawable
{
public:
  UISound();

  void setScore(int value);
  void initiate(bool state);
  void gameOver();
  void wing();

private:
  void draw(sf::RenderTarget &target,
            sf::RenderStates states) const override;

  void centerText(sf::Text &text);
  void loadMaxScore();
  void saveMaxScore();

private:
  // ===== Audio =====
  sf::SoundBuffer pointBuffer;
  sf::SoundBuffer wingBuffer;
  sf::SoundBuffer hitBuffer;

  sf::Sound pointSound;
  sf::Sound wingSound;
  sf::Sound hitSound;

  sf::Music music;

  // ===== UI =====
  sf::Font font;
  sf::Text scoreText;
  sf::Text maxScoreText;

  sf::Texture gameOverTexture;
  sf::Sprite gameOverSprite{gameOverTexture};

  sf::Texture initTexture;
  sf::Sprite initSprite{initTexture};

  // ===== State =====
  int score = 0;
  int maxScore = 0;
  bool initiated = false;
  bool isGameOver = false;
};