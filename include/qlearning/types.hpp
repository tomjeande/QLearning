#pragma once

namespace qlearning{
    enum class Action {Up, Right, Down, Left}; // Order is important here, do not change
    inline constexpr int kNumActions = 4;
}