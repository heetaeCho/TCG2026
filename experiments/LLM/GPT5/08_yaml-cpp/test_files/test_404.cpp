// TEST_ID: 404
#include <gtest/gtest.h>

#include <limits>
#include <type_traits>

#include "TestProjects/yaml-cpp/src/contrib/dragonbox.h"

namespace {

using MinImpl404 = YAML::jkj::dragonbox::detail::impl;

TEST(DragonboxImplMinTest_404, ReturnsSmallerWhenXLessThanY_404) {
  EXPECT_EQ(MinImpl404::min(1, 2), 1);
  EXPECT_EQ(MinImpl404::min(-5, 3), -5);
  EXPECT_EQ(MinImpl404::min(0, 7), 0);
}

TEST(DragonboxImplMinTest_404, ReturnsYWhenYLessThanX_404) {
  EXPECT_EQ(MinImpl404::min(2, 1), 1);
  EXPECT_EQ(MinImpl404::min(10, -10), -10);
  EXPECT_EQ(MinImpl404::min(7, 0), 0);
}

TEST(DragonboxImplMinTest_404, ReturnsYWhenEqual_404) {
  // Interface uses: (x < y) ? x : y
  // So when equal, it should return y.
  EXPECT_EQ(MinImpl404::min(5, 5), 5);
  EXPECT_EQ(MinImpl404::min(0, 0), 0);
  EXPECT_EQ(MinImpl404::min(-3, -3), -3);
}

TEST(DragonboxImplMinTest_404, HandlesIntBoundaryValues_404) {
  const int kMin = std::numeric_limits<int>::min();
  const int kMax = std::numeric_limits<int>::max();

  EXPECT_EQ(MinImpl404::min(kMin, kMax), kMin);
  EXPECT_EQ(MinImpl404::min(kMax, kMin), kMin);

  EXPECT_EQ(MinImpl404::min(kMin, kMin), kMin);
  EXPECT_EQ(MinImpl404::min(kMax, kMax), kMax);
}

TEST(DragonboxImplMinTest_404, IsNoexcept_404) {
  EXPECT_TRUE(noexcept(MinImpl404::min(1, 2)));
  EXPECT_TRUE(noexcept(MinImpl404::min(std::numeric_limits<int>::min(),
                                       std::numeric_limits<int>::max())));
}

TEST(DragonboxImplMinTest_404, WorksInConstexprContext_404) {
  constexpr int a = MinImpl404::min(3, 9);
  constexpr int b = MinImpl404::min(-7, -2);
  constexpr int c = MinImpl404::min(42, 42);

  EXPECT_EQ(a, 3);
  EXPECT_EQ(b, -7);
  EXPECT_EQ(c, 42);
}

}  // namespace