#pragma once

enum class State {
  NOT_STARTED,
  IN_PROGRESS,
  FINISHED,
};

inline State state = State::NOT_STARTED;
inline int score = 0;
