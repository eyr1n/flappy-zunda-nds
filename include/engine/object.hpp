#pragma once

#include <memory>
#include <unordered_set>

#include <nds.h>

class Object {
public:
  float x = 0;
  float y = 0;
  float width = 0;
  float height = 0;

  virtual ~Object() {}

  void add_child(const std::shared_ptr<Object> &child) {
    children_.insert(child);
  }

  void remove_child(const std::shared_ptr<Object> &child) {
    children_.erase(child);
  }

  bool get_key(KEYPAD_BITS key) { return keysCurrent() & key; }

  bool get_key_down(KEYPAD_BITS key) { return keysDown() & key; }

  bool get_key_up(KEYPAD_BITS key) { return keysUp() & key; }

  bool is_colliding(const std::shared_ptr<Object> &other) {
    return other->x < x + width && x < other->x + other->width &&
           other->y < y + height && y < other->y + other->height;
  }

  virtual void update() {
    on_update();
    for (const std::shared_ptr<Object> &child : children_) {
      child->update();
    }
  }

protected:
  virtual void on_update() {}

private:
  std::unordered_set<std::shared_ptr<Object>> children_;
};
