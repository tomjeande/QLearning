#include <gtest/gtest.h>
#include "qlearning/types.hpp"

TEST(Types, NumActionsIsFour) {
    EXPECT_EQ(4, qlearning::kNumActions) << "Only 4 actions must be possible.";
}

TEST(Types, ActionValuesMatchQTableColumns) {
    EXPECT_EQ(0, static_cast<int>(qlearning::Action::Up)) << "'Up' action must have index 0.";
    EXPECT_EQ(1, static_cast<int>(qlearning::Action::Right)) << "'Right' action must have index 1.";
    EXPECT_EQ(2, static_cast<int>(qlearning::Action::Down)) << "'Down' action must have index 2.";
    EXPECT_EQ(3, static_cast<int>(qlearning::Action::Left)) << "'Left' action must have index 3.";
}
