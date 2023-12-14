#pragma once

#include <memory>

#include <nds.h>

#include "engine/object.hpp"
#include "engine/random.hpp"

#include "bottom_wall.hpp"
#include "state.hpp"
#include "top_wall.hpp"

class Wall : public Object {
public:
  Wall(void *gfx1, void *gfx2, const std::shared_ptr<Object> &player)
      : player_(player) {
    top_wall_ = std::make_shared<TopWall>(gfx1, gfx2);
    bottom_wall_ = std::make_shared<BottomWall>(gfx1, gfx2);

    add_child(top_wall_);
    add_child(bottom_wall_);

    x = SCREEN_WIDTH;
    y = Random<float>::get(0, SCREEN_HEIGHT - 64);
    width = top_wall_->width;
  }

  void on_update() override {
    if (state != State::FINISHED) {
      // Wallを通過したら得点加算
      if (!passed_ && player_->x > x + width) {
        passed_ = true;
        score++;
      }

      // Wallとの衝突判定
      if (top_wall_->is_colliding(player_) ||
          bottom_wall_->is_colliding(player_)) {
        state = State::FINISHED;
      }

      x -= 1.5;
    }

    // 子オブジェクトの座標を同期
    top_wall_->x = x;
    top_wall_->y = y - top_wall_->height;
    bottom_wall_->x = x;
    bottom_wall_->y = y + 64;
  }

private:
  std::shared_ptr<Object> player_;
  std::shared_ptr<TopWall> top_wall_;
  std::shared_ptr<BottomWall> bottom_wall_;

  bool passed_ = false;
};
