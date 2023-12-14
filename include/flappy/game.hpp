#pragma once

#include <cstdio>
#include <memory>

#include <nds.h>

#include "engine/object.hpp"

#include "player.hpp"
#include "state.hpp"
#include "wall_emitter.hpp"

class Game : public Object {
public:
  Game(void *player_gfx, void *wall_gfx1, void *wall_gfx2)
      : player_gfx_(player_gfx), wall_gfx1_(wall_gfx1), wall_gfx2_(wall_gfx2) {}

  void on_update() override {
    if (state == State::NOT_STARTED) {
      if (!player_) {
        player_ = std::make_shared<Player>(player_gfx_);
        add_child(player_);
      }

      if (get_key_down(KEY_START)) {
        wall_emitter_ =
            std::make_shared<WallEmitter>(wall_gfx1_, wall_gfx2_, player_);
        add_child(wall_emitter_);
        state = State::IN_PROGRESS;
      }
    }

    if (state == State::FINISHED) {
      if (get_key_down(KEY_START)) {
        remove_child(player_);
        remove_child(wall_emitter_);
        player_.reset();
        wall_emitter_.reset();
        state = State::NOT_STARTED;
        score = 0;
      }
    }

    iprintf("Score: %d\n\nA    : Jump\nSTART: Start / Reset\n", score);
  }

private:
  void *player_gfx_;
  void *wall_gfx1_;
  void *wall_gfx2_;

  std::shared_ptr<Player> player_;
  std::shared_ptr<WallEmitter> wall_emitter_;
};
