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

  // ===== Bird Physics =====
  inline constexpr float BIRD_GRAVITY = 0.5f;
  inline constexpr float BIRD_JUMP_FORCE = -8.f;
  inline constexpr float BIRD_MAX_FALL_SPEED = 12.f;

  // ===== Bird Animation =====
  inline constexpr int BIRD_ANIMATION_DELAY = 10;

  // ===== Bird Visual =====
  inline constexpr float BIRD_SCALE = 2.f;
  inline constexpr float BIRD_ROTATION_SPEED = 4.f;
  inline constexpr float BIRD_JUMP_ROTATION = -15.f;
  inline constexpr float BIRD_DEAD_ROTATION = 10.f;

  // ===== Ground =====
  inline constexpr int GROUND_HEIGHT = 136;

  // ===== Parallax =====
  inline constexpr float BASE_SPEED = 2.5f;
  inline constexpr float BASE_SCALE = 1.5f;
  inline constexpr float BASE_WIDTH = 336.f;
  inline constexpr float GROUND_Y = WINDOW_HEIGHT - 112.f;

  // ===== Pipes =====
  inline constexpr float PIPE_SPACING = 350.f;
  inline constexpr float PIPE_START_X_1 = 500.f;
  inline constexpr float PIPE_START_X_2 = 850.f;
  inline constexpr float PIPE_DESPAWN_X = -100.f;
  inline constexpr float PIPE_SCORE_X = 100.f;

  inline constexpr int PIPE_MIN_Y = 100;
  inline constexpr int PIPE_RANDOM_RANGE = 250;

  // ===== Pipes (visual & gameplay) =====
  inline constexpr float PIPE_GAP = 150.f;

  // ===== Pipes (collision) =====
  inline constexpr int PIPE_COLLISION_WIDTH = 70;
  inline constexpr int PIPE_COLLISION_HEIGHT = 480;
  inline constexpr int PIPE_COLLISION_X_OFFSET = 4;
}