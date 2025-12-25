#pragma once

namespace Config
{
  // ===== Path =====
  inline constexpr const char *ASSETS_PATH = "resources/";

  // ===== Window =====
  inline constexpr int WINDOW_WIDTH = 400;
  inline constexpr int WINDOW_HEIGHT = 700;
  inline constexpr int FPS_LIMIT = 60;

  // ===== Background =====
  inline constexpr float BG_POS_Y = -15.f;
  inline constexpr float BG_SCALE = 1.5f;

  // ===== Bird =====
  inline constexpr float BIRD_START_X = 210.f;
  inline constexpr float BIRD_START_Y = 350.f;

  inline constexpr int BIRD_COLLISION_W = 44;
  inline constexpr int BIRD_COLLISION_H = 40;
  inline constexpr int BIRD_COLLISION_X_OFFSET = 23;
  inline constexpr int BIRD_COLLISION_Y_OFFSET = 21;

  // ===== Ground =====
  inline constexpr int GROUND_HEIGHT = 136;
}