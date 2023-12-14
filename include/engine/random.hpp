#pragma once

#include <random>

template <class T, class Engine = std::default_random_engine> class Random {
public:
  static inline T get(T min, T max) {
    if (!instance_) {
      instance_ = new Random();
    }
    std::uniform_real_distribution<T> dist(min, max);
    return dist(instance_->engine_);
  }

private:
  static inline Random *instance_ = nullptr;
  std::random_device device_;
  Engine engine_;

  Random() : engine_(device_()) {}
};
