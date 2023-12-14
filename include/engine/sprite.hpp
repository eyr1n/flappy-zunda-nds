#pragma once

#include <deque>
#include <numeric>

#include <nds.h>

#include "object.hpp"

class Sprite : public Object {
public:
  OamState *oam;
  int palette_alpha;
  SpriteSize size;
  SpriteColorFormat format;
  void *gfx_offset;

  int priority = 0;
  int affine_index = -1;
  bool size_double = false;
  bool hide = false;
  bool hflip = false;
  bool vflip = false;
  bool mosaic = false;

  Sprite(OamState *oam, int pallete_alpha, SpriteSize size,
         SpriteColorFormat format, void *gfx_offset)
      : oam(oam), palette_alpha(pallete_alpha), size(size), format(format),
        gfx_offset(gfx_offset) {
    id_ = IdManager::get_instance()->borrow_id();

    switch (size) {
    case SpriteSize_8x8:
      width = 8;
      height = 8;
      break;
    case SpriteSize_16x16:
      width = 16;
      height = 16;
      break;
    case SpriteSize_32x32:
      width = 32;
      height = 32;
      break;
    case SpriteSize_64x64:
      width = 64;
      height = 64;
      break;

    case SpriteSize_16x8:
      width = 16;
      height = 8;
      break;
    case SpriteSize_32x8:
      width = 32;
      height = 8;
      break;
    case SpriteSize_32x16:
      width = 32;
      height = 16;
      break;
    case SpriteSize_64x32:
      width = 64;
      height = 32;
      break;

    case SpriteSize_8x16:
      width = 8;
      height = 16;
      break;
    case SpriteSize_8x32:
      width = 8;
      height = 32;
      break;
    case SpriteSize_16x32:
      width = 16;
      height = 32;
      break;
    case SpriteSize_32x64:
      width = 32;
      height = 64;
      break;
    }
  }

  virtual ~Sprite() {
    oamClearSprite(oam, id_);
    IdManager::get_instance()->return_id(id_);
  }

  virtual void update() override {
    Object::update();
    oamSet(oam, id_, x, y, priority, palette_alpha, size, format, gfx_offset,
           affine_index, size_double, hide, hflip, vflip, mosaic);
  }

private:
  int id_;

  class IdManager {
  public:
    static inline IdManager *get_instance() {
      if (!instance_) {
        instance_ = new IdManager();
      }
      return instance_;
    }

    int borrow_id() {
      int id = ids_.front();
      ids_.pop_front();
      return id;
    }

    void return_id(int id) { ids_.push_back(id); }

  private:
    static inline IdManager *instance_ = nullptr;
    std::deque<int> ids_;

    IdManager() {
      ids_.resize(128);
      std::iota(ids_.begin(), ids_.end(), 0);
    }
  };
};
