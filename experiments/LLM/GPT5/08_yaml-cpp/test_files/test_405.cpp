// TEST_ID: 405
#include <gtest/gtest.h>

#include <climits>

#include "contrib/dragonbox.h"

namespace {

using Impl = YAML::jkj::dragonbox::detail::impl;

// Compile-time checks (the function is constexpr in the provided interface).
static_assert(Impl::max(1, 2) == 2, "max should return the larger value");
static_assert(Impl::max(2, 1) == 2, "max should return the larger value");
static_assert(Impl::max(5, 5) == 5, "max should return the value when equal");
static_assert(Impl::max(-1, -2) == -1, "max should work with negative values");

class DragonboxImplMaxTest_405 : public ::testing::Test {};

TEST_F(DragonboxImplMaxTest_405, ReturnsFirstWhenFirstIsGreater_405) {
  EXPECT_EQ(Impl::max(10, 3), 10);
}

TEST_F(DragonboxImplMaxTest_405, ReturnsSecondWhenSecondIsGreater_405) {
  EXPECT_EQ(Impl::max(3, 10), 10);
}

TEST_F(DragonboxImplMaxTest_405, ReturnsValueWhenEqual_405) {
  EXPECT_EQ(Impl::max(7, 7), 7);
  EXPECT_EQ(Impl::max(0, 0), 0);
  EXPECT_EQ(Impl::max(-5, -5), -5);
}

TEST_F(DragonboxImplMaxTest_405, HandlesNegativeValues_405) {
  EXPECT_EQ(Impl::max(-1, -2), -1);
  EXPECT_EQ(Impl::max(-10, -3), -3);
  EXPECT_EQ(Impl::max(-3, 4), 4);
  EXPECT_EQ(Impl::max(4, -3), 4);
}

TEST_F(DragonboxImplMaxTest_405, HandlesIntegerLimits_405) {
  EXPECT_EQ(Impl::max(INT_MAX, INT_MIN), INT_MAX);
  EXPECT_EQ(Impl::max(INT_MIN, INT_MAX), INT_MAX);
  EXPECT_EQ(Impl::max(INT_MIN, INT_MIN), INT_MIN);
  EXPECT_EQ(Impl::max(INT_MAX, INT_MAX), INT_MAX);
}

}  // namespace