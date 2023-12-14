#pragma once

#include <memory>

#include <nds.h>

#include "engine/object.hpp"
#include "engine/sprite.hpp"

class TopWall : public Object {
public:
  TopWall(void *gfx1, void *gfx2) {
    sprite1_ = std::make_shared<Sprite>(&oamMain, 1, SpriteSize_32x64,
                                        SpriteColorFormat_256Color, gfx2);
    sprite2_ = std::make_shared<Sprite>(&oamMain, 1, SpriteSize_32x64,
                                        SpriteColorFormat_256Color, gfx1);

    sprite1_->priority = 1;
    sprite1_->vflip = true;
    sprite2_->priority = 1;
    sprite2_->vflip = true;

    add_child(sprite1_);
    add_child(sprite2_);

    width = sprite1_->width;
    height = sprite1_->height + sprite2_->height;
  }

  void on_update() override {
    // 子オブジェクトの座標を同期
    sprite1_->x = x;
    sprite1_->y = y;
    sprite2_->x = x;
    sprite2_->y = y + sprite1_->height;
  }

private:
  std::shared_ptr<Sprite> sprite1_;
  std::shared_ptr<Sprite> sprite2_;
};
