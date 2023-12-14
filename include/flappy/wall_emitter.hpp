#pragma once

#include <deque>
#include <memory>

#include "engine/object.hpp"

#include "state.hpp"
#include "wall.hpp"

class WallEmitter : public Object {
public:
  WallEmitter(void *gfx1, void *gfx2, const std::shared_ptr<Object> &player)
      : gfx1_(gfx1), gfx2_(gfx2), player_(player) {}

  void on_update() override {
    if (state != State::FINISHED) {
      // 100フレーム経ったらWallを生成
      if (t_ > 100) {
        auto wall = std::make_shared<Wall>(gfx1_, gfx2_, player_);
        walls_.push_back(wall);
        add_child(wall);
        t_ = 0;
      }

      // 画面外に出たWallを削除
      if (!walls_.empty()) {
        auto wall = walls_.front();
        if (wall->x < -wall->width) {
          remove_child(wall);
          walls_.pop_front();
        }
      }

      t_++;
    }
  }

private:
  void *gfx1_;
  void *gfx2_;
  std::shared_ptr<Object> player_;

  int t_ = 0;
  std::deque<std::shared_ptr<Wall>> walls_;
};
