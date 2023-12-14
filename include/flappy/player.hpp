#pragma once

#include <nds.h>

#include "engine/sprite.hpp"

#include "state.hpp"

class Player : public Sprite {
public:
  Player(void *gfx)
      : Sprite(&oamMain, 0, SpriteSize_16x16, SpriteColorFormat_256Color, gfx) {
    x = 100;
  }

  void on_update() override {
    y = (G_ * t_ * t_) / 2 - V0_ * t_ + y0_;

    if (state != State::NOT_STARTED) {
      t_++;

      // 天井にぶつかったとき
      if (y < 0) {
        t_ = V0_ / G_;
        y0_ = V0_ * V0_ / (2 * G_);
      }

      // 床にぶつかったとき
      if (y > SCREEN_HEIGHT - height) {
        y = SCREEN_HEIGHT - height;
        state = State::FINISHED;
      }
    }

    if (state == State::IN_PROGRESS) {
      // ジャンプ処理
      if (get_key_down(KEY_A)) {
        t_ = 0;
        y0_ = y;
      }
    }
  }

private:
  static constexpr float V0_ = 4;
  static constexpr float G_ = 0.25;

  int t_ = 0;
  float y0_ = SCREEN_HEIGHT / 2;
};
